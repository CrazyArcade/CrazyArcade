#include "Prop.h"
#include "Settings.h"
USING_NS_CC;

Prop * Prop::create(const std::string& id, Type type)
{
    auto prop = new (std::nothrow) Prop();
    if (prop && prop->init(type))
    {
        prop->_id = id;
        prop->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        prop->autorelease();
        return prop;
    }
    CC_SAFE_DELETE(prop);
    return nullptr;
}

bool Prop::init(Type type)
{
    if (type == Type::EMPTY)
    {
        return false;
    }
    this->type = type;
    std::string path = "GameItem/Prop/";
    path += Settings::Prop::name[getType() - 100];
    if (!initWithFile(path))
    {
        return false;
    }
    return true;
}

int Prop::getType()
{
    return static_cast<int>(type);
}
