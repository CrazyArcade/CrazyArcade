#include "Scene/UI/ResultBox.h"
#include "Scene/UI/GameMap.h"

USING_NS_CC;


bool ResultBox::init()
{
    initCustomEvent();
    return true;
}

void ResultBox::initCustomEvent()
{
    _eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("game_over", [=](EventCustom* event) {
        bool isWin = *static_cast<bool*>(event->getUserData());
        setResult(isWin);
        scheduleOnce([](float dt) {
            Director::getInstance()->popScene();
        }, 3, "game_over");
    }), this);
}

void ResultBox::setResult(bool isWin)
{
    if (!pad) { 
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        pad = Sprite::create();
        pad->setPosition(visibleSize.width / 2, visibleSize.height / 2);
        addChild(pad);
    }
    if (isWin)
    {
        pad->setTexture("Scene/win.png");
    }
    else
    {
        pad->setTexture("Scene/lose.png");
    }
}


