#include "BubbleController.h"

Bubble * BubbleController::createBubble(const cocos2d::Vec2 & pos, const std::string & id, uint8_t damage)
{
    auto bubble = Bubble::create(id, damage);
    if (bubble)
    {
        bubble->setPosition(pos);
        _bubbleList.insert(id, bubble);
        return bubble;
    }
    return nullptr;
}

Bubble * BubbleController::getBubble(const std::string & id)
{
    return _bubbleList.at(id);
}
