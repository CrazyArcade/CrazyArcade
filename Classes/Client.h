#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "cocos2d.h"
#include "network/WebSocket.h"
#include "api_generated.h"
#include <unordered_map>

//#define NETWORK
#define CLIENT_ON(__code__, __func__) client->bind(__code__, CC_CALLBACK_1(__func__, this));


class Client : public cocos2d::network::WebSocket::Delegate
{
public:
    using WebSocket = cocos2d::network::WebSocket;
    using Callback = std::function<void(const void*)>;

    Client(Client const &) = delete;
    void operator=(Client const &) = delete;

    static Client * getInstance();

    bool connect(const std::string& addr = "");
    bool isConnected();

    void onOpen(WebSocket* ws);
    void onMessage(WebSocket* ws, const WebSocket::Data& data);
    void onClose(WebSocket* ws);
    void onError(WebSocket* ws, const WebSocket::ErrorCode& error);

    // bind callback function
    void bind(int code, Callback func);
    // remove all callback function
    void clear();

    void close();

    void send(const uint8_t* buf, const size_t len);

    WebSocket* ws();
private:
    Client() {
        // init
        _ws = new WebSocket();
    };
    WebSocket* _ws;

    std::unordered_map<int, Callback> funcList;

    Callback getFunc(int code);
    
};
#endif
