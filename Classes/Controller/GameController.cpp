#include "GameController.h"
#include "api_generated.h"
#include "Model/User.h"

USING_NS_CC;
using namespace API;

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
    CLIENT_ON(MsgType_GameInit, GameController::onGameInit);
    CLIENT_ON(MsgType_GameStatusChange, GameController::onGameStatusChange);

    CLIENT_ON(MsgType_PlayerPosChange, GameController::onPlayerPositionChange);
    CLIENT_ON(MsgType_PlayerAttrChange, GameController::onPlayerAttrChange);
    CLIENT_ON(MsgType_PlayerStatusChange, GameController::onPlayerStatusChange);

    CLIENT_ON(MsgType_BubbleSet, GameController::onBubbleSet);
    CLIENT_ON(MsgType_BubbleBoom, GameController::onBubbleBoom);

    CLIENT_ON(MsgType_PropSet, GameController::onPropSet);
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

void GameController::onGameInit(const void * msg)
{
    auto data = static_cast<const GameInit*>(msg);
    auto playerVector = data->players();
    for (auto it = playerVector->begin(); it != playerVector->end(); ++it)
    {
        auto id = it->id()->str();
        auto x = it->x(), y = it->y();
        auto role = it->role();
        Player * player;
        if (User::getInstance()->getUID() == id)
        {
            player = playerManager->createLocalPlayer(id, role);
        }
        else
        {
            player = playerManager->createPlayer(id, role);
        }
        player->setPosition(x, y);
        map->addPlayer(player);
    }

    {
        // send load done msg.
        flatbuffers::FlatBufferBuilder builder;
        auto orc = CreateUserChangeStats(builder, 2);
        auto msg = CreateMsg(builder, MsgType_UserChangeStats, orc.Union());
        builder.Finish(msg);
    }
    // todo send done msg
}

void GameController::onGameStatusChange(const void * msg)
{
    auto data = static_cast<const GameStatusChange*>(msg);
    auto status = data->status();
    if (status == GameStatus::GameStatus_START)
    {
        toStart();
    }
    else if (status == GameStatus::GameStatus_OVER)
    {
        toOver();
    }
}

void GameController::toStart()
{
    // game start, init keyboard listener
    initListener();
}

void GameController::toOver()
{
    // todo
}

void GameController::onPlayerJoin(const void* msg)
{
    /*
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
    */
}

void GameController::onPlayerPositionChange(const void* msg)
{
    auto data = static_cast<const API::PlayerPosChange*>(msg);
    auto player = playerManager->getPlayer(data->id()->str());
    if (!player->isLocal() && player != nullptr)
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
        //localPlayer->setBubble();
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

    auto player = playerManager->getPlayer(playerID);
    if (player->isLocal()) player->setBubble();

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
