#include "PropManager.h"
#include "Scene/UI/GameMap.h"
#include "SimpleAudioEngine.h"

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

bool PropManager::checkEat(const cocos2d::Vec2 & pos)
{
    auto map = GameMap::getCurrentMap();
    if (!map) return false;
    // check and remove prop
    for (auto it = _propList.begin(); it != _propList.end(); ++it)
    {
        auto prop = it->second;
        if (map->isInSameTile(prop->getPosition(), pos))
        {
            _propList.erase(it);
            map->removeEntity(pos);
            prop->removeFromParent();
            return true;
        }
    }
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/eatProp.mp3", false, 1.0f, 1.0f, 1.0f);
    return false;
}

void PropManager::addCustomEvent()
{
    auto dispatcher = this->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("prop_eat", [=](EventCustom * event)
    {
        auto data = static_cast<int*>(event->getUserData());
        auto pos = Vec2(data[0], data[1]);

        if (checkEat(pos))
        {
            // local player eat prop
        }
    }), this);
}
