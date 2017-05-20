#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "cocos2d.h"
#include "Settings.h"
#include "network/WebSocket.h"

class Client : public cocos2d::Layer, public cocos2d::network::WebSocket::Delegate
{
public:
    virtual bool init();
    CREATE_FUNC(Client);

    virtual void onOpen(cocos2d::network::WebSocket* ws);
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    virtual void onClose(cocos2d::network::WebSocket* ws);
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

private:
    cocos2d::network::WebSocket* ws;
};
#endif
