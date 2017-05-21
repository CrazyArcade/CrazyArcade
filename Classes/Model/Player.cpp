#include "Player.h"
#include "Settings.h"
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
    attr.speed = 2;
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
