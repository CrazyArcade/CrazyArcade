#include "UserBox.h"
#include "Settings.h"

USING_NS_CC;

bool UserBox::init()
{
    this->initWithFile("RoomScene/roomcase_01.png");
    return true;
}

void UserBox::setRole(int role)
{
    _role = role;
    if (!rolePic)
    {
        rolePic = Sprite::create();
        rolePic->setPosition(cocos2d::Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.6f));
        rolePic->setScale(1.2f);
        addChild(rolePic, 1);
    } 
    rolePic->setTexture(Settings::Player::path + std::string(Settings::Player::roleName[role]) + "/default.png");
}

void UserBox::setUserName(const std::string & name)
{
    this->name = name;
    if (!nameArea)
    {
        nameArea = ui::Text::create(name, Settings::Font::Type::base, Settings::Font::Size::name);
        nameArea->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.08f));
        nameArea->setColor(Color3B::BLACK);
        nameArea->enableGlow(Color4B::BLACK);
        addChild(nameArea, 100);
    }
    else
    {
        nameArea->setString(name);
    }
}