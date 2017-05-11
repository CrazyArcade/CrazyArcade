#include "StartScene.h"
#include <cstdio>
#include "json/filereadstream.h"
#include "json/filewritestream.h"
#include "json/document.h"
#include <json/writer.h>

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

StartScene::StartScene()
{
    FILE* fp = fopen("StartScene/Settings.json", "rb");
    char Buffer[50];
    rapidjson::FileReadStream is(fp, Buffer, sizeof(Buffer));
    rapidjson::Document d;
    d.ParseStream(is);
    musicOn = d["musicOn"].GetBool();
    fclose(fp);
}

void StartScene::musicPP(cocos2d::Ref * pSender) {
    if (musicOn)
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    else
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    musicOn = !musicOn;

    char Buffer[50];
    rapidjson::Document doc;
    FILE *fp = fopen("StartScene/Settings.json", "rb");
    rapidjson::FileReadStream is(fp, Buffer, sizeof(Buffer));                   //bind file to Buffer
    doc.ParseStream(is);
    fclose(fp);
    doc["musicOn"].SetBool(musicOn);                                            //modify values
    fp = fopen("StartScene/Settings.json", "wb");
    rapidjson::FileWriteStream os(fp, Buffer, sizeof(Buffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer (os);                  //bind buffer to file
    doc.Accept(writer);
    fclose(fp);
}

cocos2d::Menu* StartScene::musicInit() {
    const auto music = Menu::create();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("StartScene/bgmusic.mp3");
    if (!musicOn)
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

    const auto musicButton = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(StartScene::musicPP, this),
        MenuItemLabel::create(Label::createWithTTF(musicOn ? "Music on" : "Music off", Settings::Font::Type::base, Settings::Font::Size::light)),
        MenuItemLabel::create(Label::createWithTTF(musicOn ? "Music off" : "Music on", Settings::Font::Type::base, Settings::Font::Size::light)),
        nullptr);

    const auto visibleSize = Director::getInstance()->getVisibleSize();

    musicButton->setPosition(visibleSize.width * 0.95f, visibleSize.height * 0.95f);
    music->addChild(musicButton);
    music->setPosition(0, 0);
    return music;
}

void StartScene::menuPlayCallback(cocos2d::Ref * pSender) {
    const auto scene = GameScene::createScene();
    Director::getInstance()->pushScene(scene);
}

void StartScene::menuSettingsCallback(cocos2d::Ref * pSender) {
    const auto scene = SettingsScene::createScene();
    Director::getInstance()->pushScene(scene);
}

void StartScene::menuHelpCallback(cocos2d::Ref * pSender) {
    const auto scene = HelpScene::createScene();
    Director::getInstance()->pushScene(scene);
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
    title->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
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

    buttons->addChild(title, 1);
    buttons->addChild(label1, 1);
    buttons->addChild(label2, 1);
    buttons->addChild(label3, 1);
    buttons->addChild(closeItem, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

