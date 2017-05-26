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

        /*
        scheduleOnce(CC_SCHEDULE_SELECTOR(BubbleController::boom), 3);
        */

        return bubble;
    }
    return nullptr;
}

Bubble * BubbleController::getBubble(const std::string & id)
{
    return _bubbleList.at(id);
}

void BubbleController::boom(float dt, const std::string & id)
{
    auto bubble = getBubble(id);
    auto damage = bubble->getDamage();
    auto map = GameMap::getCurrentMap();
    if (map == nullptr) return;

    auto pos = map->positionToTileCoord(bubble->getPosition());


    for (uint8_t i = 1; i <= damage; i++) {     //right
        Vec2 Pos(pos.x + i, pos.y);
        if (map->isBoomable(map->tileCoordToPosition(Pos))) {
            map->removeBox(Pos);
            break;
        }
        else {
            //TODO player death judge
        }
    }
    for (uint8_t i = 1; i <= damage; i++) {     //left
        Vec2 Pos(pos.x - i, pos.y);
        if (map->isBoomable(map->tileCoordToPosition(Pos))) {
            map->removeBox(Pos);
            break;
        }
        else {
            //TODO player death judge
        }
    }
    for (uint8_t i = 1; i <= damage; i++) {     //up
        Vec2 Pos(pos.x, pos.y - i);
        if (map->isBoomable(map->tileCoordToPosition(Pos))) {
            map->removeBox(Pos);
            break;
        }
        else {
            //TODO player death judge
        }
    }
    for (uint8_t i = 1; i <= damage; i++) {     //down
        Vec2 Pos(pos.x, pos.y + i);
        if (map->isBoomable(map->tileCoordToPosition(Pos))) {
            map->removeBox(Pos);
            break;
        }
        else {
            //TODO player death judge
        }
    }

}