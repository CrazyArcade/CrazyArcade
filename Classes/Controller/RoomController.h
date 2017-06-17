#ifndef __ROOM_CONTROLLER_H__
#define __ROOM_CONTROLLER_H__

#include "cocos2d.h"
#include "Client.h"
#include "Scene/UI/UserBox.h"

class RoomController : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(RoomController);
    
    cocos2d::Vector<UserBox*> userBoxes;
    
    void onUserChangeRole(int role);

    void onUserChangeStats(bool isReady);

private:
    Client * client;
    int gameStatus;

    void onEnter();
    void onExit();

    void onWelcome(const void* msg);

    void onRoomInfoUpdate(const void* msg);

    void onGameStatusChange(const void* msg);

};

#endif