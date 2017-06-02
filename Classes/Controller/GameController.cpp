#include "GameController.h"
#include "api_generated.h"

USING_NS_CC;

bool GameController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    playerManager = PlayerManager::create();
    bubbleManager = BubbleManager::create();
    propManager = PropManager::create();

    addChild(playerManager, -1);
    addChild(bubbleManager, -1);
    addChild(propManager, -1);

    return true;
}

void GameController::setMap(GameMap * map)
{
    if (map) this->map = map;
}

void GameController::initListener()
{
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(GameController::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(GameController::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    auto dispatcher = this->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("player_join", 
        CC_CALLBACK_1(GameController::onPlayerJoin, this)), this);
    dispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("player_position_change", 
        CC_CALLBACK_1(GameController::onPlayerPositionChange, this)), this);


}

void GameController::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
        auto player = playerManager->getLocalPlayer();
        auto direction = static_cast<Player::Direction>(static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_LEFT_ARROW));
        if (player) player->setDirectionByKey(direction);
        break;
    }
    default: break;
    }
}

void GameController::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
        auto player = playerManager->getLocalPlayer();
        auto direction = static_cast<Player::Direction>(static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_LEFT_ARROW));
        if (player) player->removeDirectionByKey(direction);
        break;
    }
    case EventKeyboard::KeyCode::KEY_SPACE: {
        break;
    }
    default: break;
    }
}

void GameController::onEnter()
{
    Layer::onEnter();
#ifdef NETWORK
    client = Client::create();
    addChild(client);
    //initEventListener();
    float dur = 1 / 30;
    schedule(schedule_selector(GameScene::syncPlayerPosition), dur);
#else
    auto player = playerManager->createLocalPlayer("local");
    auto pos = map->tileCoordToPosition(Vec2(0, 0));
    player->setPosition(pos);
    map->addChild(player, 1);
#endif // NETWORK
    initListener();
}

void GameController::onExit()
{
    Layer::onExit();
#ifdef NETWORK
    _client->ws->close();
#endif // NETWORK
}

void GameController::syncLocalPlayerPosition(float dt)
{
    auto localPlayer = playerManager->getLocalPlayer();
    if (localPlayer != nullptr)
    {
        using namespace API;
        flatbuffers::FlatBufferBuilder builder;
        auto id = builder.CreateString(localPlayer->getID());
        auto dir = static_cast<Direction>(localPlayer->getDirection());
        auto pos = localPlayer->getPosition();
        auto data = CreatePlayerPosChange(builder, id, dir, pos.x, pos.y);
        auto msg = CreateMsg(builder, MsgType_PlayerPosChange, data.Union());
        builder.Finish(msg);

        client->ws->send(builder.GetBufferPointer(), builder.GetSize());
    }
}

void GameController::onPlayerJoin(cocos2d::EventCustom * event)
{
    auto data = static_cast<API::PlayerJoin*>(event->getUserData());
    Player * player;
    if (data->is_local())
    {
        player = playerManager->createLocalPlayer(data->id()->str());
    } else {
        player = playerManager->createPlayer(data->id()->str());
    }
    auto pos = Vec2(data->x(), data->y());
    player->setPosition(pos);

    map->addChild(player, 1);
}

void GameController::onPlayerPositionChange(cocos2d::EventCustom * event)
{
    auto data = static_cast<API::PlayerPosChange*>(event->getUserData());
    auto player = playerManager->getPlayer(data->id()->str());
    if (player != playerManager->getLocalPlayer() && player != nullptr)
    {
        auto pos = Vec2(data->x(), data->y());
        auto dir = static_cast<Player::Direction>(data->direction());
        player->setPosition(pos);
        player->setDirection(dir);
    }
}
