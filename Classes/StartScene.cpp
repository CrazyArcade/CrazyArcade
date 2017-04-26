#include "StartScene.h"

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
    auto musicButton = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(StartScene::musicPP, this),
        MenuItemLabel::create(Label::createWithTTF("Music on", Settings::Font::Type::base, Settings::Font::Size::light)),
        MenuItemLabel::create(Label::createWithTTF("Music off", Settings::Font::Type::base, Settings::Font::Size::light)),
        nullptr
        );
        
        //MenuItemLabel::create(
        //Label::createWithTTF("Music on", Settings::Font::Type::base, Settings::Font::Size::light),
        //this, menu_selector(StartScene::musicPP));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    musicButton->setPosition(visibleSize.width * 0.95f, visibleSize.height * 0.95f);
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
    
    auto title = MenuItemLabel::create(
        Label::createWithTTF("Crazy Arcade", Settings::Font::Type::title, Settings::Font::Size::title));
    auto label1 = MenuItemLabel::create(
        Label::createWithTTF("Play", Settings::Font::Type::base, Settings::Font::Size::label));
    auto label2 = MenuItemLabel::create(
        Label::createWithTTF("Settings", Settings::Font::Type::base, Settings::Font::Size::label));
    auto label3 = MenuItemLabel::create(
        Label::createWithTTF("Help", Settings::Font::Type::base, Settings::Font::Size::label));
    auto closeItem = MenuItemLabel::create(
        Label::createWithTTF("Exit", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(StartScene::menuCloseCallback, this));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto baseY = visibleSize.height * 0.85f;

    title->setPosition(title->getContentSize().width / 2 + 60, baseY);										//left-aligned
    label1->setPosition(label1->getContentSize().width / 2 + 60, baseY - 200);
    label2->setPosition(label2->getContentSize().width / 2 + 60, baseY - 260);
    label3->setPosition(label3->getContentSize().width / 2 + 60, baseY - 320);
    closeItem->setPosition(closeItem->getContentSize().width / 2 + 60, baseY - 380);

    buttons->addChild(title, 1);
    buttons->addChild(label1, 1);
    buttons->addChild(label2, 1);
    buttons->addChild(label3, 1);
    buttons->addChild(closeItem, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

