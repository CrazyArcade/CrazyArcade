#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->setName("root");
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

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    //addChild(createText());

    _map = GameMap::create();
    _map->setMap("town_10");
    addChild(_map, -1);

    _playerController = PlayerController::create();
    addChild(_playerController, -1, "player_controller");

    auto player1 = _playerController->createLocalPlayer("test");
    _map->addChild(player1, 1);
    player1->setPosition(_map->tileCoordToPosition(Vec2(0, 0)));

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

void GameScene::keyPressedAct(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
        int direction = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_LEFT_ARROW);
        char * buf = new char[4];
        sprintf(buf, "1 %d", direction);
        EventCustom myEvent("on_local_player_move");
        myEvent.setUserData(buf);
        _playerController->getEventDispatcher()->dispatchEvent(&myEvent);
        CC_SAFE_DELETE_ARRAY(buf);
        break;
    }
    default: break;
    }
}

void GameScene::keyReleasedAct(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
        int direction = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_LEFT_ARROW);
        char * buf = new char[4];
        sprintf(buf, "0 %d", direction);
        EventCustom myEvent("on_local_player_move");
        myEvent.setUserData(buf);
        _playerController->getEventDispatcher()->dispatchEvent(&myEvent);
        CC_SAFE_DELETE_ARRAY(buf);
        break;
    }
    case EventKeyboard::KeyCode::KEY_SPACE: {
        // TODO set bubble
        break;
    }
    default: break;
    }
}


