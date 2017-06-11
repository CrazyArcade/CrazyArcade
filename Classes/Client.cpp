#include "Client.h"
#include "Settings.h"

USING_NS_CC;
using namespace API;

Client * Client::getInstance()
{
    static Client INSTANCE;
    return &INSTANCE;
}

bool Client::connect(const std::string & addr)
{
    return _ws->init(*this, Settings::Server::addr);
}

bool Client::isConnected()
{
    return _ws->getReadyState() == WebSocket::State::OPEN;
}

void Client::onOpen(WebSocket * ws)
{
    log("connect");
}

void Client::onMessage(WebSocket * ws, const WebSocket::Data & data)
{
    auto msg = GetMsg(data.bytes);
    auto func = getFunc(msg->data_type());
    if (func) func(msg->data());
}

void Client::onClose(WebSocket * ws)
{
    if (ws == this->_ws)
    {
        this->_ws = nullptr;
    }
    CC_SAFE_DELETE(ws);
    log("close");
}

void Client::onError(WebSocket * ws, const WebSocket::ErrorCode & error)
{
    log("error");
}

void Client::bind(int code, Callback func)
{
    funcList[code] = func;
}

Client::WebSocket * Client::ws()
{
    return _ws;
}

inline Client::Callback Client::getFunc(int code)
{
    auto func = funcList.find(code);
    return func == funcList.cend() ? nullptr : func->second;
}

