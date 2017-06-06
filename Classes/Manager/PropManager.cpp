#include "PropManager.h"

bool PropManager::init()
{
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
}
