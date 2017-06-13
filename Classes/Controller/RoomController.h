#ifndef __ROOM_CONTROLLER_H__
#define __ROOM_CONTROLLER_H__

#include "cocos2d.h"
#include "Client.h"

class RoomController : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(RoomController);

private:
    Client * client;

    void onEnter();
    void onExit();

    void onWelcome(const void* msg);

    void onRoomInfoUpdate(const void* msg);

    void onUserChangeRole(/*TODO*/);

    void onUserChangeStats(/*TODO*/);

};

#endif