#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "SettingsScene.h"
#include "RoomScene.h"

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

    addChild(createBGImage());
    addChild(createText());
    musicInit();

    return true;
}

void StartScene::musicPP(cocos2d::Ref * pSender) {
    if (musicOn)
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    else
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    musicOn = !musicOn;
    UserDefault::getInstance()->setBoolForKey("musicOn", musicOn);
}

void StartScene::musicInit() {
    const auto music = Menu::create();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/roomScene.mp3",true);
	musicOn = UserDefault::getInstance()->getBoolForKey("musicOn", true);
	//musicOn = CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	//UserDefault::getInstance()->setBoolForKey("musicOn", musicOn);
    if (!musicOn)
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); 
    /*auto labelDef = Label::createWithTTF(musicOn ? "Music on" : "Music off", Settings::Font::Type::base, Settings::Font::Size::light);
    auto labelSwi = Label::createWithTTF(musicOn ? "Music off" : "music on", Settings::Font::Type::base, Settings::Font::Size::light);
    labelDef->setColor(cocos2d::Color3B::BLACK);
    labelSwi->setColor(cocos2d::Color3B::BLACK);
    const auto musicButton = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(StartScene::musicPP, this),
        MenuItemLabel::create(labelDef),
        MenuItemLabel::create(labelSwi),
        nullptr);

    const auto visibleSize = Director::getInstance()->getVisibleSize();

    musicButton->setPosition(visibleSize.width * 0.95f, visibleSize.height * 0.95f);
    music->addChild(musicButton);
    music->setPosition(0, 0);
	return music;*/
}

void StartScene::menuPlayCallback(cocos2d::Ref * pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1, RoomScene::createScene()));
}

void StartScene::menuSettingsCallback(cocos2d::Ref * pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1, SettingsScene::createScene()));
}

void StartScene::menuHelpCallback(cocos2d::Ref * pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1, HelpScene::createScene()));
}

void StartScene::menuExitCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

cocos2d::Menu* StartScene::createText() {                                //create all text units: title, menu label
    const auto buttons = Menu::create();

    const auto title = MenuItemLabel::create(
        Label::createWithTTF("Crazy Arcade", Settings::Font::Type::title, Settings::Font::Size::title));
    //title->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
    const auto label1 = MenuItemLabel::create(
        Label::createWithTTF("Play", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(StartScene::menuPlayCallback, this));
    const auto label2 = MenuItemLabel::create(
        Label::createWithTTF("Settings", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(StartScene::menuSettingsCallback, this));
    const auto label3 = MenuItemLabel::create(
        Label::createWithTTF("Help", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(StartScene::menuHelpCallback, this));
    const auto closeItem = MenuItemLabel::create(
        Label::createWithTTF("Exit", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(StartScene::menuExitCallback, this));

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    title->setPosition(title->getContentSize().width / 2 + 60, baseY);										//left-aligned
    label1->setPosition(label1->getContentSize().width / 2 + 60, baseY - 200);
    label2->setPosition(label2->getContentSize().width / 2 + 60, baseY - 260);
    label3->setPosition(label3->getContentSize().width / 2 + 60, baseY - 320);
    closeItem->setPosition(closeItem->getContentSize().width / 2 + 60, baseY - 380);

    title->setColor(cocos2d::Color3B::BLACK);
    label1->setColor(cocos2d::Color3B::BLACK);
    label2->setColor(cocos2d::Color3B::BLACK);
    label3->setColor(cocos2d::Color3B::BLACK);
    closeItem->setColor(cocos2d::Color3B::BLACK);

    buttons->addChild(title, 1);
    buttons->addChild(label1, 1);
    buttons->addChild(label2, 1);
    buttons->addChild(label3, 1);
    buttons->addChild(closeItem, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

cocos2d::Sprite* StartScene::createBGImage() {
    auto size = Director::getInstance()->getVisibleSize();
    auto bgImage = Sprite::create("Scene/backgroundimage.jpg");
    bgImage->setScale(1.25);
    bgImage->setZOrder(-1);
    bgImage->setPosition(size.width / 2, size.height / 2);
    return bgImage;
}