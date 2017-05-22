#include "BubbleController.h"
#include "Scene/UI/GameMap.h"

Bubble * BubbleController::createBubble(const cocos2d::Vec2 & pos, const std::string & id, uint8_t damage)
{
    auto bubble = Bubble::create(id, damage);
    if (bubble)
    {
        bubble->setPosition(pos);
        _bubbleList.insert(id, bubble);
        // TODO here set a schedule, 3sec later boom itself
        return bubble;
    }
    return nullptr;
}

Bubble * BubbleController::getBubble(const std::string & id)
{
    return _bubbleList.at(id);
}

void BubbleController::boom(const std::string & id)
{
    auto bubble = getBubble(id);
    auto damage = bubble->getDamage();
    auto map = GameMap::getCurrentMap();
    if (map == nullptr) return;

    // TODO boom logic here
}
