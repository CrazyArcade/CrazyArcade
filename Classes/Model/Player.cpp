#include "Player.h"
#include "Settings.h"
#include "Scene/UI/GameMap.h"
#include <ctime>

USING_NS_CC;

Player * Player::create(const std::string& id, const std::string& role)
{
    auto player = new (std::nothrow) Player();
    if (player && player->initWithRole(role))
    {
        player->_id = id;
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

bool Player::init()
{
    _status = Status::FREE;
    attr.speed = 3;
    attr.power = 1;
    attr.bubble = 1;
    size = this->getContentSize();
    // set right anchor point.
    this->setAnchorPoint(Vec2(0.5, (Settings::Map::TileSize::height / 2 ) / size.height));
    return true;
}

bool Player::initWithRole(const std::string& role)
{
    auto file = Settings::Player::path + role + ".png";
    if (this->initWithFile(file) && this->init())
    {
        // do something here
        // ...
        return true;
    }
    return false;
}

void Player::setStatus(Player::Status status)
{
    this->_status = status;
}

const Player::Status Player::getStatus() const
{
    return this->_status;
}

void Player::setDirection(Direction direction)
{
    directions[static_cast<int>(direction)] = time(nullptr);
}

void Player::removeDirection(Direction direction)
{
    directions[static_cast<int>(direction)] = 0;
}

Player::Direction Player::getDirection()
{
    Direction direction = Direction::NONE;
    time_t max = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (directions[i] > max)
        {
            max = directions[i];
            direction = static_cast<Direction>(i);
        }
    }
    return direction;
}

void Player::move()
{
    if (_status == Status::FREE && getDirection() != Direction::NONE)
    {
        auto map = dynamic_cast<GameMap*>(Director::getInstance()->getRunningScene()->getChildByName("root")->getChildByName("map"));
        if (!map) return;
        auto pair = getNextPos();
        // next center point
        auto nextPos = pair.first;
        // next edge point
        auto logicPos = pair.second;

        if (map->isCanAccess(logicPos))
        {
            setPosition(nextPos);
        }
        else
        {
            // TODO update UE
        }
    }
}

std::pair<cocos2d::Vec2, cocos2d::Vec2> Player::getNextPos()
{
    auto pos = getPosition();
    Vec2 nextPos(pos.x, pos.y), logicPos(pos.x, pos.y);

    switch (getDirection())
    {
    case Direction::LEFT:
        nextPos.x -= attr.speed;
        logicPos.x = nextPos.x - size.width / 2;
        break;
    case Direction::RIGHT:
        nextPos.x += attr.speed;
        logicPos.x = nextPos.x + size.width / 2;
        break;
    case Direction::UP:
        nextPos.y += attr.speed;
        logicPos.y = nextPos.y + size.height / 2;
        break;
    case Direction::DOWN:
        nextPos.y -= attr.speed;
        logicPos.y = nextPos.y - size.height / 2;
        break;
    default:
        break;
    }
    return std::make_pair(nextPos, logicPos);
}
