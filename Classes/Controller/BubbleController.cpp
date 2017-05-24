#include "BubbleController.h"
#include "Scene/UI/GameMap.h"

USING_NS_CC;

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

    auto pos = map->positionToTileCoord(bubble->getPosition());

    for (uint8_t i = 0; i < map->getMapSize().width; i++) {     //horizontal
        Vec2 Pos(i, pos.y);
        if (map->isBoomable(map->tileCoordToPosition(Pos)))
            map->removeBox(Pos);
    }
    for (uint8_t i = 0; i < map->getMapSize().height; i++) {    //vertical
        Vec2 Pos(pos.x, i);
        if (map->isBoomable(map->tileCoordToPosition(Pos)))
            map->removeBox(Pos);
    }
}
