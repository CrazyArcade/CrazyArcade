#include "Prop.h"
#include "Settings.h"
USING_NS_CC;

Prop * Prop::create(const std::string& id, Type type)
{
    auto prop = new (std::nothrow) Prop();
    if (prop && prop->init())
    {
        prop->_id = id;
        prop->type = type;
        prop->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        prop->autorelease();
        return prop;
    }
    CC_SAFE_DELETE(prop);
    return nullptr;
}

bool Prop::init()
{
    std::string path = "GameItem/Prop/";
    path.append(Settings::Prop::name[static_cast<int>(type)]);
    if (!initWithFile(path))
    {
        return false;
    }
    return true;
}
