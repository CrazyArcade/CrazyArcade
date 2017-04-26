#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool StartScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    addChild(createText());
    addChild(musicInit());

    return true;
}

void StartScene::musicPP(cocos2d::Ref * pSender) {
    if (musicOn)
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    else
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    musicOn = !musicOn;
}

cocos2d::Menu* StartScene::musicInit() {
    auto music = Menu::create();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("StartScene/bgmusic.mp3");
    auto musicButton = MenuItemLabel::create(Label::createWithTTF("musicPP", "fonts/Arial.ttf", 20), this, menu_selector(StartScene::musicPP));
    musicButton->setPosition(420, 270);
    music->addChild(musicButton);
    music->setPosition(0, 0);
    return music;
}

void StartScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

cocos2d::Menu* StartScene::createText() {                                                                   //create all text units: title, menu label
    auto buttons = Menu::create();

    auto title = MenuItemLabel::create(Label::createWithTTF("Crazy Arcade", "fonts/Marker Felt.ttf", 30));
    auto label1 = MenuItemLabel::create(Label::createWithTTF("Play", "fonts/Arial.ttf", 20));
    auto label2 = MenuItemLabel::create(Label::createWithTTF("Settings", "fonts/Arial.ttf", 20));
    auto label3 = MenuItemLabel::create(Label::createWithTTF("Help", "fonts/Arial.ttf", 20));
    auto closeItem = MenuItemLabel::create(
        Label::createWithTTF("Exit", "fonts/Arial.ttf", 20),
        CC_CALLBACK_1(StartScene::menuCloseCallback, this));

    title->setPosition(title->getContentSize().width / 2 + 60, 260);										//left-aligned
    label1->setPosition(label1->getContentSize().width / 2 + 60, 200);
    label2->setPosition(label2->getContentSize().width / 2 + 60, 170);
    label3->setPosition(label3->getContentSize().width / 2 + 60, 140);
    closeItem->setPosition(closeItem->getContentSize().width / 2 + 60, 110);

    buttons->addChild(title, 1);
    buttons->addChild(label1, 1);
    buttons->addChild(label2, 1);
    buttons->addChild(label3, 1);
    buttons->addChild(closeItem, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

