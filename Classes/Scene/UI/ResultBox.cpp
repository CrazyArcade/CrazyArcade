#include "Scene/UI/ResultBox.h"
#include "Scene/UI/GameMap.h"

bool ResultBox::init()
{
    return true;
}

void ResultBox::setResult(Result result)
{
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


