#include "LoginScene.h"
#include "Settings.h"
#include "SettingsScene.h"
#include "StartScene.h"
#include "Scene/UI/CheckBox.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* LoginScene::createScene()
{
    auto scene = Scene::create();

    auto layer = LoginScene::create();

    scene->addChild(layer);

    return scene;
}

bool LoginScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->addChild(createBackground());
    this->addChild(createLoginItem());

    initUserBox();
    initcheckBox();

    return true;
}

cocos2d::Sprite* LoginScene::createBackground()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite * bg = Sprite::create("Scene/bg03.jpg");
    bg->setScale(2.4);
    //set transparent
    bg->setOpacity(255);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));

    return bg;
}

cocos2d::Sprite* LoginScene::createLoginBox()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite * loginBox = Sprite::create("RoomScene/loginform02.png");
    loginBox->setScale(1.5);
    loginBox->setOpacity(255);
    loginBox->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));

    return loginBox;
}

cocos2d::Menu* LoginScene::createLoginItem()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //login menu
    auto loginOnItem = cocos2d::MenuItemImage::create(
        "RoomScene/login03.png",
        "RoomScene/login03.png");
    auto loginOffItem = loginOnItem;
    auto loginToggleItem = cocos2d::MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(LoginScene::menuLoginCallback, this),
        loginOnItem,
        loginOffItem,
        NULL);
    loginOnItem->setScale(1.5);
    loginOffItem->setScale(1.5);
    loginToggleItem->setPosition(Director::getInstance()->convertToGL(Vec2(visibleSize.width / 3, visibleSize.height * 0.76f)));
    //loginItem->setAnchorPoint(Vec2(1, 0));
    Menu * mn = Menu::create(loginToggleItem, NULL);
    mn->setPosition(Vec2::ZERO);
    return mn;
}

void LoginScene::initUserBox()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    usernameBG = Sprite::create("RoomScene/input_normal.png");
    auto usernameInput = ui::TextField::create("Username:", Settings::Font::Type::title, Settings::Font::Size::normal);

    usernameInput->setColor(Color3B::BLACK);
    usernameInput->setCursorChar('|');
    usernameInput->setCursorEnabled(true);
    usernameInput->setMaxLength(15);
    usernameInput->setMaxLengthEnabled(true);
    usernameInput->setPosition(usernameBG->getContentSize() / 2);
    usernameInput->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));

    usernameBG->addChild(usernameInput);

    usernameBG->setScale(1.5);
    usernameBG->setPosition(Vec2(visibleSize.width / 3 + origin.x,
        visibleSize.height / 2 + origin.y + usernameBG->getContentSize().height * 2));

    addChild(usernameBG);

}

void LoginScene::initcheckBox()
{
    auto _checkBox = CheckBox::create();
    this->addChild(_checkBox, 0);
}

void LoginScene::menuLoginCallback(cocos2d::Ref* pSender)
{
    auto scene = StartScene::createScene();
    Director::getInstance()->pushScene(scene);
}

void LoginScene::textFieldEvent(Ref* sender, ui::TextField::EventType event)
{
    switch (event) {
    case ui::TextField::EventType::ATTACH_WITH_IME:
        usernameBG->setTexture(Sprite::create("RoomScene/input_active.png")->getTexture());
        break;
    case ui::TextField::EventType::DETACH_WITH_IME:
        usernameBG->setTexture(Sprite::create("RoomScene/input_normal.png")->getTexture());
        break;
    }
}

void LoginScene::checkboxSelectedEvent(cocos2d::Ref* pSender)
{

}

void LoginScene::menuBackCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}