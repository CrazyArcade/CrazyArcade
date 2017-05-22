#include "Bubble.h"
#include "Settings.h"

Bubble * Bubble::createAt(const std::string & id, const cocos2d::Vec2& pos, uint8_t damage)
{
    auto bubble = new (std::nothrow) Bubble();
    if (bubble && bubble->init())
    {
        bubble->_id = id;
        bubble->_damage = damage;
        bubble->setPosition(pos);

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
    return true;
}

void Bubble::setStatus(Status status)
{
    this->_status = status;
}
