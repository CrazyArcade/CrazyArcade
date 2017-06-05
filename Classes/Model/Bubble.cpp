#include "Bubble.h"
#include "Settings.h"

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
        // TODO animation
    }
}

void Bubble::initAnimation()
{
    constexpr float stayDelay = 0.3f;
    constexpr float explodeDelay = 0.02f;
    loadAnimation("alive", stayDelay, 3);
    loadAnimation("ExplosionHorizontal", explodeDelay, 14);
    loadAnimation("ExplosionVerticalLeft", explodeDelay, 14);
    loadAnimation("ExplosionVerticalRight", explodeDelay, 14);
}
