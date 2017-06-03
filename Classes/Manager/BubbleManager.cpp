#include "BubbleManager.h"
#include "Scene/UI/GameMap.h"
#include "api_generated.h"

USING_NS_CC;

Bubble * BubbleManager::createBubble(const std::string & id, const std::string& playerID, const cocos2d::Vec2 & pos, uint8_t damage)
{
    auto bubble = Bubble::create(id, playerID, damage);
    if (bubble)
    {
        bubble->setPosition(pos);
        _bubbleList.insert(id, bubble);

        return bubble;
    }
    return nullptr;
}

Bubble * BubbleManager::getBubble(const std::string & id)
{
    return _bubbleList.at(id);
}

void BubbleManager::boom(float dt, const std::string & id)
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

bool BubbleManager::init()
{
    if (!Layer::init())
    {
        return false;
    }

    return true;
}

void BubbleManager::addCustomEvent()
{
    auto dispatcher = this->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("bubble_set", [=](EventCustom * event)
    {
        auto data = static_cast<API::BubbleSet*>(event->getUserData());
    }), this);
}
