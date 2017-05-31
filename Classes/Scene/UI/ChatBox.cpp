#include "Scene/UI/ChatBox.h"

USING_NS_CC;

bool ChatBox::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    boxInput = cocos2d::TextFieldTTF::textFieldWithPlaceHolder("Chat Here",
        Settings::Font::Type::base, Settings::Font::Size::chat);
    boxInput->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height*0.2));
    boxInput->setDelegate(this);
    
    addChild(boxInput);
    return true;
}