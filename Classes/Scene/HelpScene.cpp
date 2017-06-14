#include "HelpScene.h"
#include "Settings.h"
#include "Scene/StartScene.h"

USING_NS_CC;

Scene* HelpScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelpScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    addChild(createText());

    return true;
}

cocos2d::Menu* HelpScene::createText() {                                
    const auto buttons = Menu::create();

    const auto backButton=MenuItemLabel::create(
        Label::createWithTTF("Back", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(HelpScene::menuBackCallback, this));

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    backButton->setPosition(backButton->getContentSize().width / 2 + 30, baseY + 30);

    buttons->addChild(backButton, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

void HelpScene::menuBackCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}
