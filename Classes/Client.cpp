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
    if (_ws == nullptr) _ws = new WebSocket();
    return _ws->init(*this, Settings::Server::addr);
}

bool Client::isConnected()
{
    return _ws == nullptr ? false : _ws->getReadyState() == WebSocket::State::OPEN;
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
    std::string msg = "Connected error. Error code: " + static_cast<int>(error);
    MessageBox(msg.data(), "Error");
}

void Client::bind(int code, Callback func)
{
    funcList[code] = func;
}

void Client::clear()
{
    funcList.clear();
}

void Client::close()
{
    if (isConnected()) _ws->closeAsync();
}

void Client::send(const uint8_t* buf, const size_t len)
{
    if (isConnected()) _ws->send(buf, len);
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

