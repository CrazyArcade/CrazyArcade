#include "Scene/UI/ResultBox.h"
#include "Scene/UI/GameMap.h"

USING_NS_CC;


bool ResultBox::init()
{
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    pad = cocos2d::Sprite::create("Scene/PlayingPad.png");
    pad->setPosition(visibleSize.width / 2, visibleSize.height*0.9);
    pad->setScale(0.5);
    auto label = cocos2d::Label::createWithTTF("IN GAME", Settings::Font::Type::base, Settings::Font::Size::title);
    label->setPosition(pad->getContentSize().width / 2, pad->getContentSize().height / 2 - 5);
    pad->addChild(label);
    addChild(pad);
    return true;
}

void ResultBox::setResult(Result result)
{
     
    pad->removeFromParentAndCleanup(true);
    
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    switch (result) {
    case VICTORY:
        pad = cocos2d::Sprite::create("Scene/win.png");
        break;
    case DEFEAT:
        pad = cocos2d::Sprite::create("Scene/lose.png");
        break;
    }
   
    pad->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    //GameMap::getCurrentMap()->setOpacity(0.5);
    addChild(pad);
}


