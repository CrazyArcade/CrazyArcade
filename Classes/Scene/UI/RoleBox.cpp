#include "RoleBox.h"
#include "Settings.h"

bool RoleBox::init()
{
    std::string name= Settings::Player::path + std::string(Settings::Player::roleName[this->_role]) + "/faceBW.png";
    if (!this->initWithFile(name))
        return false;
    return true;
}

RoleBox * RoleBox::create(roleChoice role)
{
    auto roleBox = new (std::nothrow) RoleBox();
    if(roleBox){
        roleBox->_role = role;
        roleBox->init();
        roleBox->autorelease();
        return roleBox;
    }
    CC_SAFE_DELETE(roleBox);
    return nullptr;
}

void RoleBox::setChosen(bool choice)
{
    if (choice != isChosen) {
        isChosen = choice;
        auto fileName = isChosen ? "/face.png" : "/faceBW.png";
        this->setTexture(cocos2d::Sprite::create(
            Settings::Player::path + std::string(Settings::Player::roleName[this->_role]) + fileName)
            ->getTexture());
    }
}

RoleBox::roleChoice RoleBox::getRole()
{
    return _role;
}