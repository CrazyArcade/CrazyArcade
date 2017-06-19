#include "StartScene.h"
#include "Settings.h"
#include "HelpScene.h"
#include "SettingsScene.h"
#include "RoomScene.h"
#include "Util/GameAudio.h"

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


    return true;
}

void StartScene::menuPlayCallback(cocos2d::Ref * pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1, RoomScene::createScene()));
}

void StartScene::menuSettingsCallback(cocos2d::Ref * pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1, SettingsScene::createScene()));
}

void StartScene::onEnter()
{
    Layer::onEnter();
    GameAudio::getInstance()->playBgm("Sound/mainScene.mp3");
}

void StartScene::onExit()
{
    //GameAudio::getInstance()->stopBgm();
    Layer::onExit();
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
    Vector<MenuItem *> items = {
        MenuItemLabel::create(
            Label::createWithTTF("Crazy Arcade", Settings::Font::Type::title, Settings::Font::Size::title)),
        MenuItemLabel::create(
            Label::createWithTTF("Play", Settings::Font::Type::base, Settings::Font::Size::label),
            CC_CALLBACK_1(StartScene::menuPlayCallback, this)),
        MenuItemLabel::create(
            Label::createWithTTF("Settings", Settings::Font::Type::base, Settings::Font::Size::label),
            CC_CALLBACK_1(StartScene::menuSettingsCallback, this)),
        MenuItemLabel::create(
            Label::createWithTTF("Help", Settings::Font::Type::base, Settings::Font::Size::label),
            CC_CALLBACK_1(StartScene::menuHelpCallback, this)),
        MenuItemLabel::create(
            Label::createWithTTF("Exit", Settings::Font::Type::base, Settings::Font::Size::label),
            CC_CALLBACK_1(StartScene::menuExitCallback, this))
    };

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;
    constexpr int offset[] = { 0, 160, 220, 280, 340 };

    for (ssize_t i = 0; i < items.size(); ++i)
    {
        auto item = dynamic_cast<MenuItemLabel *>(items.at(i));
        item->setColor(Color3B::WHITE);
        dynamic_cast<Label*>(item->getLabel())->enableShadow(Color4B(0, 0, 0, 255 * 0.2f), Size(2, -2), 8);
        item->setPosition(item->getContentSize().width / 2 + 60, baseY - offset[i]);
    }

    auto menu = Menu::createWithArray(items);
    menu->setPosition(0, 0);

    return menu;
}

cocos2d::Sprite* StartScene::createBGImage() {
    auto size = Director::getInstance()->getVisibleSize();
    auto bgImage = Sprite::create("Scene/backgroundimage.jpg");
    bgImage->setScale(1.25);
    bgImage->setLocalZOrder(-1);
    bgImage->setPosition(size.width / 2, size.height / 2);
    return bgImage;
}