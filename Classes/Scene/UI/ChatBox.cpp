#include "Scene/UI/ChatBox.h"

USING_NS_CC;

bool ChatBox::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto boxInput = cocos2d::TextFieldTTF::textFieldWithPlaceHolder("Chat Here",
        Settings::Font::Type::base, Settings::Font::Size::chat);
    boxInput->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height*0.2));
    boxInput->setDelegate(boxInputDel);

    boxHistory = cocos2d::ui::RichText::create();
    boxHistory->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height*0.3));
    boxHistory->setSize(Size(300,500));

    // Test text
    auto chatHistory1 = cocos2d::ui::RichElementText::create(1, cocos2d::Color3B::YELLOW, 255, "这是白色的文字。 ", 
        Settings::Font::Type::base, Settings::Font::Size::chat); 
    auto chatHistory2 = cocos2d::ui::RichElementText::create(2, cocos2d::Color3B::YELLOW, 255, "这是白色的文字。 ",
        Settings::Font::Type::base, Settings::Font::Size::chat); 
    auto chatHistory3 = cocos2d::ui::RichElementText::create(3, cocos2d::Color3B::YELLOW, 255, "这是白色的文字。 ",
        Settings::Font::Type::base, Settings::Font::Size::chat);
    boxHistory->pushBackElement(chatHistory1);
    boxHistory->pushBackElement(chatHistory2);
    boxHistory->pushBackElement(chatHistory3);

    addChild(boxInput);
    addChild(boxHistory);
    return true;
}