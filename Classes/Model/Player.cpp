#include "Player.h"
#include "Settings.h"
#include <ctime>

USING_NS_CC;

Player * Player::create(const std::string& id, const std::string& Role)
{
    auto player = new (std::nothrow) Player();
    if (player && player->initWithRole(Role))
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
    attr.damage = 1;
    attr.currentBubble = attr.maxBubble = 1;
    direction = Direction::NONE;
    size = this->getContentSize();
    // set right anchor point.
    this->setAnchorPoint(Vec2(0.5, (Settings::Map::TileSize::height / 2) / size.height));
    return true;
}

bool Player::initWithRole(const std::string& Role)
{
    auto file = Settings::Player::path + Role + "/default.png";
    role = Role;
    if (this->initWithFile(file) && this->init())
    {
        // do something here
        initAnimation();
        return true;
    }
    return false;
}

bool Player::initAnimation()
{
    constexpr float moveDelay = 0.1f;
    loadAnimation(role + "_left", moveDelay, 6);
    loadAnimation(role + "_right", moveDelay, 6);
    loadAnimation(role + "_up", moveDelay, 6);
    loadAnimation(role + "_down", moveDelay, 6);

    constexpr float dangerDelay = 0.1f;
    loadAnimation(role + "_danger", dangerDelay, 3);

    constexpr float dieDelay = 0.2f;
    loadAnimation(role + "_die", dieDelay, 3);

    return true;
}

uint8_t Player::getSpeed()
{
    return attr.speed;
}

void Player::setSpeed(uint8_t speed)
{
    this->attr.speed = speed;
}

uint8_t Player::getDamage()
{
    return attr.damage;
}

void Player::setDamage(uint8_t damage)
{
    attr.damage = damage;
}

uint8_t Player::getBubble()
{
    return attr.currentBubble;
}

void Player::setMaxBubble(uint8_t maxBubble, uint8_t currentBubble)
{
    attr.maxBubble = maxBubble;
    attr.currentBubble = currentBubble;
}

bool Player::isCanSetBubble()
{
    return attr.currentBubble > 0;
}

void Player::setBubble()
{
    --attr.currentBubble;
}

void Player::boomBubble()
{
    if (attr.maxBubble > attr.currentBubble) ++attr.currentBubble;
}

void Player::setStatus(Player::Status status)
{
    this->_status = status;
    setAnimation();
}

Player::Status Player::getStatus()
{
    return this->_status;
}

void Player::isLocal(bool a)
{
    this->_isLocal = a;
}

bool Player::isLocal()
{
    return _isLocal;
}

void Player::setDirectionByKey(Direction direction)
{
    directions[static_cast<int>(direction)] = time(nullptr);
    updateDirection();
}

void Player::removeDirectionByKey(Direction direction)
{
    directions[static_cast<int>(direction)] = 0;
    updateDirection();
}

void Player::updateDirection()
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
    setDirection(direction);
}

void Player::setDirection(Direction direction)
{
    this->direction = direction;
    setAnimation();
}

Player::Direction Player::getDirection()
{
    return direction;
}

void Player::setAnimation()
{
    if (_status == Status::FREE)
    {
        stopAnimation(this);

        if (this->direction == Direction::LEFT)
        {
            runAnimation(role + "_left", this);
        }
        else if (this->direction == Direction::RIGHT)
        {
            runAnimation(role + "_right", this);
        }
        else if (this->direction == Direction::UP)
        {
            runAnimation(role + "_up", this);
        }
        else if (this->direction == Direction::DOWN)
        {
            runAnimation(role + "_down", this);
        }
    }
    else if (_status == Status::FREEZE)
    {

    }
}
