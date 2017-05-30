#include "Client.h"
#include "api_generated.h"

USING_NS_CC;
using namespace API;

bool Client::init()
{
    // create ws instance
    ws = new network::WebSocket();
    if (!ws->init(*this, Settings::Sever::addr))
    {
        return false;
    }
    //this->

    return true;
}

void Client::onOpen(cocos2d::network::WebSocket * ws)
{
    log("connect");
}

void Client::onMessage(cocos2d::network::WebSocket * ws, const cocos2d::network::WebSocket::Data & data)
{
    auto msg = GetMsg(data.bytes);
    auto res = msg->data();
    std::string event;
    switch (msg->data_type())
    {
    case MsgType_PlayerJoin:
        event = "on_local_player_init";
        break;
    case MsgType_PlayerPosChange:
        event = "on_other_player_move";
        break;
    }
    if (event.size() > 0)
    {
        EventCustom myEvent(event);
        myEvent.setUserData(const_cast<void*>(res));
        Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchEvent(&myEvent);
    }
}

void Client::onClose(cocos2d::network::WebSocket * ws)
{
    if (ws == this->ws)
    {
        this->ws = nullptr;
    }
    CC_SAFE_DELETE(ws);
    log("close");
}

void Client::onError(cocos2d::network::WebSocket * ws, const cocos2d::network::WebSocket::ErrorCode & error)
{
    log("error");
}

