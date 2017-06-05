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
    _bubbleWave[0] = BubbleWave::create("ExplosionHorizontalLeft",this);
    _bubbleWave[1] = BubbleWave::create("ExplosionHorizontalRight", this);
    _bubbleWave[2] = BubbleWave::create("ExplosionVerticalUp", this);
    _bubbleWave[3] = BubbleWave::create("ExplosionVerticalDown", this);
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
        for (int i = 0; i < 4; i++) {
            _bubbleWave[i]->runAnimation(_bubbleWave[i]->dir, this);
        }
    }
}

void Bubble::initAnimation()
{
    constexpr float stayDelay = 0.3f;
    loadAnimation("alive", stayDelay, 3);
}

bool BubbleWave::init()
{
    if (!this->initWithFile((Settings::Bubble::explosionPath + dir + "/" + dir + ".png").c_str))
    {
        return false;
    }
    initAnimation();
    return true;
}

void BubbleWave::initAnimation()
{
    constexpr float explodeDelay = 0.02f;
    loadAnimation(dir, explodeDelay, 14);
}
