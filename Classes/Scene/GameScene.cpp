#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "api_generated.h"

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
    initEventListen();

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

    _client = Client::create();
    addChild(_client);

    //_bubbleController = BubbleController::create();
    //addChild(_bubbleController, -1, "bubble_controller");

    scheduleUpdate();
    
    return true;
}

void GameScene::onExit()
{
    _client->ws->close();
}

void GameScene::update(float dt)
{
    // update player pos
    auto localPlayer = _playerController->getLocalPlayer();
    if (localPlayer)
    {
        using namespace API;
        flatbuffers::FlatBufferBuilder builder;
        auto localPlayer = _playerController->getLocalPlayer();
        auto id = builder.CreateString(localPlayer->getID());
        auto dir = static_cast<Direction>(localPlayer->getDirection());
        auto pos = localPlayer->getPosition();
        auto data = CreatePlayerPosChange(builder, id, dir, pos.x, pos.y);
        auto msg = CreateMsg(builder, MsgType_PlayerPosChange, data.Union());
        builder.Finish(msg);

        _client->ws->send(builder.GetBufferPointer(), builder.GetSize());
    }
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

void GameScene::initEventListen()
{
    using namespace API;
    auto dispatcher = this->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("on_local_player_init", [=](EventCustom* event)
    {
        auto data = static_cast<API::PlayerJoin*>(event->getUserData());
        auto player = _playerController->createLocalPlayer(data->id()->str());
        auto pos = Vec2(data->x(), data->y());
        player->setPosition(pos);
        _map->addChild(player, 1);
    }), this);

    dispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("on_other_player_move", [=](EventCustom* event)
    {
        auto data = static_cast<API::PlayerPosChange*>(event->getUserData());
        auto player = _playerController->getPlayer(data->id()->str());
        if (player != _playerController->getLocalPlayer() && player != nullptr)
        {
            auto pos = Vec2(data->x(), data->y());
            auto dir = static_cast<Player::Direction>(data->direction());
            player->setPosition(pos);
            player->setDirection(dir);
        }

    }), this);
}
