#include "RoleBox.h"
#include "Settings.h"

bool RoleBox::initWithRole(std::string role, int8_t Rank)
{
    rank = Rank;
    setRole(role);
    return true;
}

RoleBox* RoleBox::create(std::string role, int8_t Rank)
{
    auto roleBox = new (std::nothrow) RoleBox();
    if (roleBox && roleBox->initWithRole(role, Rank))
    {
        return roleBox;
    }
    CC_SAFE_DELETE(roleBox);
    return nullptr;
}

void RoleBox::setRole(const std::string & Role)
{
    role = Role;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto roleWindow = cocos2d::Sprite::create("RoomScene/roleWindow.png");
    auto name = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithTTF
    (Role, Settings::Font::Type::base, Settings::Font::Size::light));
    auto icon = cocos2d::Sprite::create("GameItem/Player/" + Role + "/default.png");

    icon->setScale(1.1);

    cocos2d::Vec2 relPosName(roleWindow->getContentSize().width*0.5,
        roleWindow->getContentSize().height*0.85);
    name->setPosition(relPosName);

    cocos2d::Vec2 relPosRole(roleWindow->getContentSize().width*0.5,
        roleWindow->getContentSize().height*0.35);
    icon->setPosition(relPosRole);

    roleWindow->addChild(name);

    roleWindow->addChild(icon);

    roleWindow->setPosition(visibleSize.width*0.6,
        visibleSize.height*0.7 - (rank - 1)*roleWindow->getContentSize().height);

    addChild(roleWindow);

    // TODO 
}

std::string RoleBox::getRole()
{
    return role;
}
