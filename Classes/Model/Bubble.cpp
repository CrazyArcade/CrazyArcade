#include "Bubble.h"
#include "Settings.h"

USING_NS_CC;

Bubble * Bubble::create(const std::string & id, const std::string& playerID, uint8_t damage)
{
    auto bubble = new (std::nothrow) Bubble();
    if (bubble && bubble->init())
    {
        bubble->_id = id;
        bubble->_playerID = playerID;
        bubble->_damage = damage;

        bubble->autorelease();
        return bubble;
    }
    CC_SAFE_DELETE(bubble);
    return nullptr;
}

bool Bubble::init()
{
    if (!this->initWithFile(Settings::Bubble::path))
    {
        return false;
    }
    initAnimation();
    setStatus(Status::ALIVE);
    return true;
}

uint8_t Bubble::getDamage()
{
    return _damage;
}

void Bubble::setStatus(Status status)
{
    if (status == Status::ALIVE)
    {
        runAnimation("alive", this);
    }
    else if (status == Status::BOOM)
    {
        // TODO
    }
}

void Bubble::initAnimation()
{
    constexpr float stayDelay = 0.3f;
    loadAnimation("alive", stayDelay, 3);
}


bool BubbleWave::init(BubbleWave::PosInWave pos, Direction direction)
{
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    getExplosionString(pos, direction);
    initAnimation(pos, direction);

    auto animation = getAnimation(animationName);
    auto frame = animation->getFrames().at(0)->getSpriteFrame();

    initWithSpriteFrame(frame);

    this->runAction(Sequence::create(Animate::create(animation), CallFuncN::create([](Node * node) {
        node->removeFromParent();
    }), NULL));

    return true;
}

BubbleWave * BubbleWave::create(BubbleWave::PosInWave pos, Direction direction)
{
    auto bubbleWave = new (std::nothrow) BubbleWave();
    if (bubbleWave && bubbleWave->init(pos, direction))
    {
        bubbleWave->autorelease();
        return bubbleWave;
    }
    CC_SAFE_DELETE(bubbleWave);
    return nullptr;
}

void BubbleWave::initAnimation(PosInWave pos, Direction direction)
{
    constexpr float explosionDelay = 0.1f;
    loadAnimation(animationName, explosionDelay, 3);
}

void BubbleWave::getExplosionString(PosInWave pos, Direction direction)
{
    std::string explosionParam("Explosion");

    if (pos == CENTER) {
        explosionParam += "Center";
    }
    else {
        if (pos == MIDDLE)
            explosionParam += "Wave";
        switch (direction)
        {
        case LEFT:
            explosionParam += "LEFT";
            break;
        case RIGHT:
            explosionParam += "RIGHT";
            break;
        case UP:
            explosionParam += "UP";
            break;
        case DOWN:
            explosionParam += "DOWN";
        default:
            break;
        }
    }
    animationName = explosionParam;
}
