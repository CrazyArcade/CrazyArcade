#include "GameController.h"
#include "Network/api_generated.h"
#include "Model/User.h"
#include "SimpleAudioEngine.h"



USING_NS_CC;
using namespace API;

bool GameController::init()
{
    if (!Layer::init())
    {
        return false;
    }

    oper = Operator::create();
    oper->addHandle(CC_CALLBACK_2(GameController::opHandle, this));

    playerManager = PlayerManager::create();
    bubbleManager = BubbleManager::create();
    propManager = PropManager::create();

    addChild(oper, -1);
    addChild(playerManager, -1);
    addChild(bubbleManager, -1);
    addChild(propManager, -1);
    
    return true;
}

void GameController::setMap(GameMap * map)
{
    if (map) this->map = map;
}

void GameController::opHandle(Operator::OpCode opcode, Operator::OpType type)
{
    if (opcode == Operator::OpCode::SPACE)
    {
        if (type == Operator::OpType::RELEASE) onLocalPlayerSetBubble();
    }
    else
    {
        auto player = playerManager->getLocalPlayer();
        if (!player) return;
        auto direction = static_cast<Player::Direction>(opcode);
        if (type == Operator::OpType::PRESS)
        {
            player->setDirectionByKey(direction);
        }
        else
        {
            player->removeDirectionByKey(direction);
        }
    }
}


void GameController::onEnter()
{
    Layer::onEnter();
#ifdef NETWORK
    client = Client::getInstance();
    if (!client->isConnected()) client->connect();

    CLIENT_ON(MsgType_GameInit, GameController::onGameInit);
    CLIENT_ON(MsgType_GameStatusChange, GameController::onGameStatusChange);

    CLIENT_ON(MsgType_PlayerPosChange, GameController::onPlayerPositionChange);
    CLIENT_ON(MsgType_PlayerAttrChange, GameController::onPlayerAttrChange);
    CLIENT_ON(MsgType_PlayerStatusChange, GameController::onPlayerStatusChange);

    CLIENT_ON(MsgType_BubbleSet, GameController::onBubbleSet);
    CLIENT_ON(MsgType_BubbleBoom, GameController::onBubbleBoom);

    CLIENT_ON(MsgType_PropSet, GameController::onPropSet);
    
    {
        // send enter scene msg.
        flatbuffers::FlatBufferBuilder builder;
        auto orc = CreateUserChangeStats(builder, 2);
        auto msg = CreateMsg(builder, MsgType_UserChangeStats, orc.Union());
        builder.Finish(msg);
        client->send(builder.GetBufferPointer(), builder.GetSize());
    }

#else
    auto player = playerManager->createLocalPlayer("local", 0);
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
#ifdef NETWORK
    if (gameStatus != 3) // player exit game directly
    {
        client->close();
    }
    client->clear();
    client = nullptr;
#endif // NETWORK
    Layer::onExit();
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
        auto data = CreatePlayerPosChange(builder, id, dir, pos.x * 10, pos.y * 10);
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
        player->setSpeed(it->speed());
        player->setDamage(it->damage());
        player->setMaxBubble(it->bubble(), it->bubble());
        player->setPosition(x, y);
        map->addPlayer(player);
    }
}

void GameController::onGameStatusChange(const void * msg)
{
    auto data = static_cast<const GameStatusChange*>(msg);
    auto status = data->status();
    gameStatus = static_cast<int>(status);

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
    oper->start();
#ifdef NETWORK
    float dur = 1 / 30;
    schedule(schedule_selector(GameController::syncLocalPlayerPosition), dur);
#endif // NETWORK
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/gameStart.mp3", false, 1.0f, 1.0f, 1.0f);
}

void GameController::toOver()
{
    oper->stop();
    unschedule(schedule_selector(GameController::syncLocalPlayerPosition));
    
    auto isWin = new bool;
    *isWin = (playerManager->getLocalPlayer()->getStatus() != Player::Status::DIE);

    Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent("game_over", isWin);

    CC_SAFE_DELETE(isWin);
}

void GameController::onPlayerPositionChange(const void* msg)
{
    auto data = static_cast<const API::PlayerPosChange*>(msg);
    auto player = playerManager->getPlayer(data->id()->str());
    if (player != nullptr && !player->isLocal())
    {
        auto pos = Vec2(data->x() / 10, data->y() / 10);
        auto dir = static_cast<Player::Direction>(data->direction());
        player->setPosition(pos);
        player->setDirection(dir);
        propManager->checkEat(pos);
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
