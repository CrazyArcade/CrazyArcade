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
    attr.damage = 4;
    attr.currentBubble = attr.maxBubble = 3;
    direction = Direction::NONE;
    size = this->getContentSize();
    // set right anchor point.
    this->setAnchorPoint(Vec2(0.5, (Settings::Map::TileSize::height / 2 ) / size.height));
    return true;
}

bool Player::initWithRole(const std::string& role)
{
    auto file = Settings::Player::path + role + "/default.png";
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
	constexpr float delay = 0.1f;
	loadAnimation("player2_left", delay, 6);
	loadAnimation("player2_right", delay, 6);
	loadAnimation("player2_up", delay, 6);
	loadAnimation("player2_down", delay, 6);
	
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

void Player::setMaxBubble(uint8_t maxBubble)
{
    attr.maxBubble = maxBubble;
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
            runAnimation("player2_left", this);
        }
        else if (this->direction == Direction::RIGHT)
        {
            runAnimation("player2_right", this);
        }
        else if (this->direction == Direction::UP)
        {
            runAnimation("player2_up", this);
        }
        else if (this->direction == Direction::DOWN)
        {
            runAnimation("player2_down", this);
        }
    }
    else if (_status == Status::FREEZE)
    {

    }
}
