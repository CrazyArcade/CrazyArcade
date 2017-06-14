#include "UserBox.h"
#include "Settings.h"

bool UserBox::init()
{
    this->initWithFile("RoomScene/roomcase_01.png");
    initNameArea();
    return true;
}

void UserBox::setRole(RoleBox::roleChoice role)
{
    if (isInit) {
        isInit = false;
        rolePic = cocos2d::Sprite::create(
            Settings::Player::path + std::string(Settings::Player::roleName[this->_role]) + "/face.png");
        rolePic->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
        addChild(rolePic);
        _role = role;
    }
    else {
        if (role != _role) {
            _role = role;
            rolePic->setTexture(cocos2d::Sprite::create(
                Settings::Player::path + std::string(Settings::Player::roleName[this->_role]) + "/face.png")
            ->getTexture());
        }
    }
}

std::string UserBox::getName()
{
    return name;
}

void UserBox::initNameArea()
{
    nameArea = cocos2d::ui::TextField::create("Username Here",
        Settings::Font::Type::base, Settings::Font::Size::chat);
    nameArea->setCursorEnabled(true);
    nameArea->setCursorChar('|');
    nameArea->setTextHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    nameArea->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height*0.2));
    addChild(nameArea);
}
