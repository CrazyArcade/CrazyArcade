#include "Rocker.h"
#include <set>

USING_NS_CC;

constexpr float PI = 3.1415926f;

bool Rocker::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    leftPos = Vec2(size.width * 0.1f, size.height * 0.2f);
    rightPos = Vec2(size.width * 0.9f, size.height * 0.2f);

    rockerBGL = createRockerBG(leftPos);
    addChild(rockerBGL, -1);

    rockerDotL = createRockerDot(leftPos);
    addChild(rockerDotL, 99);

    rockerBGR = createRockerBG(rightPos);
    addChild(rockerBGR, -1);
    rockerDotR = createRockerDot(rightPos, 2.0f);
    addChild(rockerDotR, 99);

    return true;
}

void Rocker::start()
{
    rockerBGL->setVisible(true);
    rockerDotL->setVisible(true);
    rockerBGR->setVisible(true);
    rockerDotR->setVisible(true);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    touchListener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Rocker::stop()
{
    rockerBGL->setVisible(false);
    rockerDotL->setVisible(false);
    rockerBGR->setVisible(false);
    rockerDotR->setVisible(false);

    _eventDispatcher->removeEventListenersForTarget(this);
}

cocos2d::Sprite * Rocker::createRockerBG(const Vec2 & pos)
{
    auto s = Sprite::create("Rocker/bg.png");
    //s->setOpacity(200);
    s->setPosition(pos);
    s->setVisible(false);
    return s;
}

cocos2d::Sprite * Rocker::createRockerDot(const cocos2d::Vec2 & pos, float scale)
{
    auto s = Sprite::create("Rocker/dot.png");
    s->setScale(scale);
    s->setPosition(pos);
    s->setVisible(false);
    return s;
}

bool Rocker::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
    auto point = touch->getLocation();
    if (rockerDotL->getBoundingBox().containsPoint(point))
    {
        isCanMove = true;
        log("touch");
    }
    return true;
}

void Rocker::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
    if (!isCanMove) return;

    auto point = touch->getLocation();
    auto dotLPos = rockerDotL->getPosition();
    auto r = rockerDotL->getContentSize().height / 2;

    auto angle = getRad(point, dotLPos);
    log("%d %d", point.x, point.y);
    if (sqrt(pow((dotLPos.x - point.x), 2) + pow((dotLPos.y - point.y), 2)) >= r)
    {
        auto p = Point(r * cos(angle), r * sin(angle)) + Point(dotLPos.x, dotLPos.y);
        rockerDotL->setPosition(p);
        log("%d %d", p.x, p.y);
    }
    else
    {
        rockerDotL->setPosition(point);
    }
    if (!handle) return;
    std::set<Operator::OpCode> opcodes = { Operator::OpCode::LEFT, Operator::OpCode::RIGHT, Operator::OpCode::UP, Operator::OpCode::DOWN};

    if (angle >= -PI / 4 && angle < PI / 4)
    {
        opcodes.erase(Operator::OpCode::RIGHT);
        handle(Operator::OpCode::RIGHT, Operator::OpType::PRESS);
    }
    else if (angle >= PI / 4 && angle < 3 * PI / 4)
    {
        opcodes.erase(Operator::OpCode::UP);
        handle(Operator::OpCode::UP, Operator::OpType::PRESS);
    }
    else if ((angle >= 3 * PI / 4 && angle <= PI) || (angle >= -PI && angle < -3 * PI / 4))
    {
        opcodes.erase(Operator::OpCode::LEFT);
        handle(Operator::OpCode::LEFT, Operator::OpType::PRESS);
    }
    else if (angle >= -3 * PI / 4 && angle < -PI / 4)
    {
        opcodes.erase(Operator::OpCode::DOWN);
        handle(Operator::OpCode::DOWN, Operator::OpType::PRESS);
    }

    for (auto &code : opcodes)
    {
        handle(code, Operator::OpType::RELEASE);
    }
}

void Rocker::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
    auto point = touch->getLocation();
    if (rockerDotR->getBoundingBox().containsPoint(point))
    {
        handle(Operator::OpCode::SPACE, Operator::OpType::RELEASE);
    }
    else
    {
        if (!isCanMove) return;
        rockerDotL->stopAllActions();
        rockerDotL->runAction(MoveTo::create(0.08f, leftPos));
        isCanMove = false;
    }
}

float Rocker::getRad(Point pos1, Point pos2)
{
    float px1 = pos1.x;
    float py1 = pos1.y;
    float px2 = pos2.x;
    float py2 = pos2.y;

    float x = px2 - px1;
    float y = py2 - py1;

    float hypo = sqrt(pow(x, 2) + pow(y, 2));
    float cosAngle = x / hypo;
    float rad = acos(cosAngle);

    if (py2 < py1)
        rad = -rad;

    return rad;
}
