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
    if (role < 0)
    {
        rolePic->setVisible(false);
    }
    else
    {
        rolePic->setVisible(true);
        rolePic->setTexture(Settings::Player::path + std::string(Settings::Player::roleName[role]) + "/default.png");
    }
    
}

void UserBox::setUserName(const std::string & name)
{
    this->name = name;
    if (!nameArea)
    {
        nameArea = ui::Text::create(name, Settings::Font::Type::base, Settings::Font::Size::name);
        nameArea->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.1f));
        nameArea->setColor(Color3B::WHITE);
        nameArea->enableGlow(Color4B::BLACK);
        addChild(nameArea, 100);
    }
    else
    {
        nameArea->setString(name);
    }
}

void UserBox::setReadyLabel(bool ready)
{
    if (!readyLabel)
    {
        readyLabel = cocos2d::Label::createWithTTF("Ready!", Settings::Font::Type::base, Settings::Font::Size::normal);
        readyLabel->setColor(cocos2d::Color3B::GREEN);
        readyLabel->setPosition(this->getContentSize().width*0.7, this->getContentSize().height*0.9);
        readyLabel->setRotation(30);
        this->addChild(readyLabel, 2);
    }

    readyLabel->setVisible(ready);
}
