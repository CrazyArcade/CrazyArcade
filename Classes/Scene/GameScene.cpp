#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressedAct, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleasedAct, this);

    //addChild(createText());

    map = GameMap::create();
    map->setMap("town_10");
    addChild(map, -1);

    playerController = PlayerController::create();
    addChild(playerController, -1, "player_controller");

    auto player1 = playerController->createPlayer();
    map->addChild(player1, 1);
    player1->setPosition(map->tileCoordToPosition(Vec2(0, 0)));

    return true;
}

cocos2d::Menu* GameScene::createText() {
    const auto buttons = Menu::create();

    const auto backButton = MenuItemLabel::create(
        Label::createWithTTF("Back", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(GameScene::menuBackCallback, this));

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    backButton->setPosition(backButton->getContentSize().width / 2 + 30, baseY + 30);

    buttons->addChild(backButton, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

void GameScene::menuBackCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void GameScene::keyPressedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    //undefined
}

void GameScene::keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    //undefined
}


