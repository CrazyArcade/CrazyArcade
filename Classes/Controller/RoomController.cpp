#include "RoomController.h"
#include "api_generated.h"
#include "Model/User.h"
#include "Scene/GameScene.h"

USING_NS_CC;
using namespace API;

bool RoomController::init()
{
    if (!Layer::init())
    {
        return false;
    }

    return true;
}

void RoomController::onEnter()
{
    Layer::onEnter();
#ifdef NETWORK
    client = Client::getInstance();
    if (!client->isConnected())
    {
        client->connect();
    }

    CLIENT_ON(MsgType_Welcome, RoomController::onWelcome);
    CLIENT_ON(MsgType_RoomInfoUpdate, RoomController::onRoomInfoUpdate);
    CLIENT_ON(MsgType_GameStatusChange, RoomController::onGameStatusChange);
#endif // NETWORK
}

void RoomController::onExit()
{
    Layer::onExit();
#ifdef NETWORK
    client->clear();
    client = nullptr;
#endif // NETWORK

}

void RoomController::onWelcome(const void * msg)
{
    auto data = static_cast<const Welcome*>(msg);
    auto user = User::getInstance();
    user->setUID(data->uid()->str());

    {
        // name has been set before
        flatbuffers::FlatBufferBuilder builder;
        auto name = builder.CreateString(user->getName());
        auto orc = CreateGotIt(builder, name);
        auto msg = CreateMsg(builder, MsgType_GotIt, orc.Union());
        builder.Finish(msg);
        client->send(builder.GetBufferPointer(), builder.GetSize());
    }
    {
        // join room
        flatbuffers::FlatBufferBuilder builder;
        auto orc = CreateJoinRoom(builder);
        auto msg = CreateMsg(builder, MsgType_JoinRoom, orc.Union());
        builder.Finish(msg);
        client->send(builder.GetBufferPointer(), builder.GetSize());
    }
}

void RoomController::onRoomInfoUpdate(const void * msg)
{
    auto data = static_cast<const RoomInfoUpdate*>(msg);
    auto userVector = data->users();

    auto it1 = userVector->begin();
    auto it2 = userBoxes.begin();
    for (; it2 != userBoxes.end(); ++it2)
    {
        std::string name = "";
        int role = -1;
        
        if (it1 != userVector->end())
        {
            //auto uid = it1->uid()->str();
            name = it1->name()->str();
            role = it1->role();
            ++it1;
        }

        (*it2)->setName(name);
        (*it2)->setRole(role);
    }
}

void RoomController::onGameStatusChange(const void * msg)
{
    auto data = static_cast<const GameStatusChange*>(msg);
    auto status = data->status();
    if (status == GameStatus::GameStatus_PENDING)
    {
        Director::getInstance()->pushScene(GameScene::createScene());
    }
}

void RoomController::onUserChangeRole(int role)
{
    flatbuffers::FlatBufferBuilder builder;
    auto orc = CreateUserChangeRole(builder, role);
    auto msg = CreateMsg(builder, MsgType_UserChangeRole, orc.Union());
    builder.Finish(msg);
    
    client->send(builder.GetBufferPointer(), builder.GetSize());
}


void RoomController::onUserChangeStats(bool isReady)
{
    auto stats = static_cast<int>(isReady);
    flatbuffers::FlatBufferBuilder builder;
    auto orc = CreateUserChangeStats(builder, stats);
    auto msg = CreateMsg(builder, MsgType_UserChangeStats, orc.Union());
    builder.Finish(msg);

    client->send(builder.GetBufferPointer(), builder.GetSize());
}
