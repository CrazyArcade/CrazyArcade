#include "PropManager.h"
#include "Scene/UI/GameMap.h"

USING_NS_CC;

bool PropManager::init()
{
    addCustomEvent();
    return true;
}

Prop * PropManager::createProp(const std::string & id, Prop::Type type, const cocos2d::Vec2 & pos)
{
    auto prop = Prop::create(id, type);
    if (prop)
    {
        prop->setPosition(pos);
        _propList.insert(prop->getID(), prop);
        return prop;
    }
    return nullptr;
}

void PropManager::addCustomEvent()
{
    auto dispatcher = this->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("prop_eat", [=](EventCustom * event)
    {
        auto data = static_cast<int*>(event->getUserData());
        auto pos = Vec2(data[0], data[1]);

        auto map = GameMap::getCurrentMap();
        if (!map) return;
        // check and remove prop
        for (auto it = _propList.begin(); it != _propList.end();)
        {
            auto prop = it->second;
            if (map->isInSameTile(prop->getPosition(), pos))
            {
                _propList.erase(it++);
                map->removeEntity(pos);
                prop->removeFromParent();
            }
            else
            {
                ++it;
            }
        }
    }), this);
}
