#include "Scene/UI/ResultBox.h"

bool ResultBox::init()
{
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    pad = cocos2d::Sprite::create("Scene/PlayingPad.png");
    pad->setPosition(visibleSize.width / 2, visibleSize.height*0.9);
    pad->setScale(0.5);
    label = cocos2d::Label::createWithTTF("IN GAME", Settings::Font::Type::base, Settings::Font::Size::title);
    label->setPosition(pad->getContentSize().width / 2, pad->getContentSize().height / 2 - 5);
    pad->addChild(label);
    addChild(pad);
    return true;
}

void ResultBox::setResult(Result result)
{
     
    label->removeFromParentAndCleanup(true);
    pad->removeFromParentAndCleanup(true);
    
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    switch (result) {
    case VICTORY:
        pad = cocos2d::Sprite::create("Scene/ResultPadVictory.png");
        label= cocos2d::Label::createWithTTF("VICTORY", Settings::Font::Type::base, Settings::Font::Size::result);
        break;
    case DEFEAT:
        pad = cocos2d::Sprite::create("Scene/ResultPadDefeat.png");
        label = cocos2d::Label::createWithTTF("DEFEAT", Settings::Font::Type::base, Settings::Font::Size::result);
        break;
    }
   
    pad->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    label->setPosition(pad->getContentSize().width / 2, pad->getContentSize().height / 2);

    pad->addChild(label);
    addChild(pad);
}


