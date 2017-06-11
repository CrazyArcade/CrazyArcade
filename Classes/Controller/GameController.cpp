#include "GameController.h"
#include "api_generated.h"

USING_NS_CC;
using namespace API;

//#define NETWORK
#define CLIENT_ON(__code__, __func__) client->bind(__code__, CC_CALLBACK_1(GameController::__func__, this));

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

#ifdef NETWORK
    CLIENT_ON(MsgType_PlayerJoin, onPlayerJoin);
    CLIENT_ON(MsgType_PlayerPosChange, onPlayerPositionChange);
    CLIENT_ON(MsgType_PlayerAttrChange, onPlayerAttrChange);
    CLIENT_ON(MsgType_PlayerStatusChange, onPlayerStatusChange);

    CLIENT_ON(MsgType_BubbleSet, onBubbleSet);
    CLIENT_ON(MsgType_BubbleBoom, onBubbleBoom);

    CLIENT_ON(MsgType_PropSet, onPropSet);
#endif // NETWORK
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
        onLocalPlayerSetBubble();
        break;
    }
    default: break;
    }
}

void GameController::onEnter()
{
    Layer::onEnter();
#ifdef NETWORK
    client = Client::getInstance();
    if (!client->isConnected()) client->connect();

    float dur = 1 / 30;
    schedule(schedule_selector(GameController::syncLocalPlayerPosition), dur);
#else
    auto player = playerManager->createLocalPlayer("local");
    auto pos = map->tileCoordToPosition(Vec2(0, 0));
    player->setPosition(pos);
    map->addPlayer(player);

    auto pos1 = map->tileCoordToPosition(Vec2(0, 1));
    auto prop = propManager->createProp("bubble", Prop::Type::BUBBLE, pos1);
    map->addProp(prop, prop->getType());
#endif // NETWORK
    initListener();
}

void GameController::onExit()
{
    Layer::onExit();
#ifdef NETWORK
    client->clear();
    client->close();
    client = nullptr;
#endif // NETWORK
}

void GameController::syncLocalPlayerPosition(float dt)
{
    auto localPlayer = playerManager->getLocalPlayer();
    if (localPlayer != nullptr && localPlayer->getStatus() == Player::Status::FREE)
    {
        using namespace API;
        flatbuffers::FlatBufferBuilder builder;
        auto id = builder.CreateString(localPlayer->getID());
        auto dir = static_cast<Direction>(localPlayer->getDirection());
        auto pos = localPlayer->getPosition();
        auto data = CreatePlayerPosChange(builder, id, dir, pos.x, pos.y);
        auto msg = CreateMsg(builder, MsgType_PlayerPosChange, data.Union());
        builder.Finish(msg);

        client->send(builder.GetBufferPointer(), builder.GetSize());
    }
}

void GameController::onPlayerJoin(const void* msg)
{
    auto data = static_cast<const API::PlayerJoin*>(msg);
    Player * player;
    if (data->is_local())
    {
        player = playerManager->createLocalPlayer(data->id()->str());
    } else {
        player = playerManager->createPlayer(data->id()->str());
    }
    auto pos = Vec2(data->x(), data->y());
    player->setPosition(pos);

    map->addPlayer(player);
}

void GameController::onPlayerPositionChange(const void* msg)
{
    auto data = static_cast<const API::PlayerPosChange*>(msg);
    auto player = playerManager->getPlayer(data->id()->str());
    if (player != playerManager->getLocalPlayer() && player != nullptr)
    {
        auto pos = Vec2(data->x(), data->y());
        auto dir = static_cast<Player::Direction>(data->direction());
        player->setPosition(pos);
        player->setDirection(dir);
    }
}

void GameController::onPlayerAttrChange(const void * msg)
{
    auto data = static_cast<const API::PlayerAttrChange*>(msg);
    auto player = playerManager->getPlayer(data->id()->str());
    if (player->isLocal())
    {
        player->setSpeed(data->speed());
        player->setDamage(data->damage());
        player->setMaxBubble(data->maxBubble(), data->currentBubble());
    }
}

void GameController::onPlayerStatusChange(const void * msg)
{
    auto data = static_cast<const API::PlayerStatusChange*>(msg);
    auto player = playerManager->getPlayer(data->id()->str());

    if (player)
    {
        player->setStatus(static_cast<Player::Status>(data->status()));
    }
}

void GameController::onLocalPlayerSetBubble()
{
    auto localPlayer = playerManager->getLocalPlayer();
    if (localPlayer->isCanSetBubble() && map->at(map->positionToTileCoord(localPlayer->getPosition())) != map->TILE_BUBBLE)
    {
        localPlayer->setBubble();
#ifdef NETWORK
        using namespace API;
        flatbuffers::FlatBufferBuilder builder;
        auto data = CreatePlayerSetBubble(builder);
        auto orc = CreateMsg(builder, MsgType_PlayerSetBubble, data.Union());
        builder.Finish(orc);
        client->send(builder.GetBufferPointer(), builder.GetSize());
#else
        auto pos = map->centrePos(localPlayer->getPosition());
        std::string id = "bubble_test" + std::to_string(time(0));
        auto bubble = bubbleManager->createBubble(id, localPlayer->getID(), pos, localPlayer->getDamage());
        if (bubble)
        {
            map->addBubble(bubble);
            scheduleOnce([=](float dt)
            {
                bubbleManager->boom(id);
                playerManager->getLocalPlayer()->boomBubble();
            }, 3.0f, id);
        }
#endif // NETWORK
    }
}

void GameController::onBubbleSet(const void* msg)
{
    auto data = static_cast<const API::BubbleSet*>(msg);
    auto id = data->id()->str();
    auto playerID = data->player_id()->str();
    auto x = data->x(), y = data->y();
    auto damage = data->damage();
    
    auto bubble = bubbleManager->createBubble(id, playerID, Vec2(x, y), damage);
    if (bubble)
    {
        map->addBubble(bubble);
    }
}

void GameController::onBubbleBoom(const void* msg)
{
    auto data = static_cast<const API::BubbleBoom*>(msg);
    auto id = data->id()->str();
    auto playerID = bubbleManager->getBubble(id)->getPlayerID();

    auto player = playerManager->getPlayer(playerID);

    if (player && player->isLocal())
    {
        player->boomBubble();
    }

    bubbleManager->boom(id);
}

void GameController::onPropSet(const void* msg)
{
    auto data = static_cast<const API::PropSet*>(msg);
    auto id = data->id()->str();
    auto type = static_cast<Prop::Type>(data->type());
    auto pos = Vec2(data->x(), data->y());
    auto prop = propManager->createProp(id, type, pos);

    map->addProp(prop, prop->getType());
}
