#include "Bubble.h"
#include "Settings.h"

static Bubble * Bubble::create(const std::string & id, uint8_t damage)
{
    auto bubble = new (std::nothrow) Bubble();
    if (bubble && bubble->init())
    {
        bubble->_id = id;
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
    return true;
}

void Bubble::setStatus(Status status)
{
    this->_status = status;
}
