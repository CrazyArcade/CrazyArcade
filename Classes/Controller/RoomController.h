#ifndef __ROOM_CONTROLLER_H__
#define __ROOM_CONTROLLER_H__

#include "cocos2d.h"
#include "Client.h"

class RoomController : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(RoomController);

    void onUserChangeRole(/*TODO*/);

    void onUserChangeStats(bool isReady);

private:
    Client * client;

    void onEnter();
    void onExit();

    void onWelcome(const void* msg);

    void onRoomInfoUpdate(const void* msg);

};

#endif