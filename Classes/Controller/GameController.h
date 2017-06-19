#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "Network/Client.h"
#include "Manager/PlayerManager.h"
#include "Manager/BubbleManager.h"
#include "Manager/PropManager.h"
#include "Scene/UI/GameMap.h"
#include "Operator/Operator.h"

class GameController : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameController);

    void setMap(GameMap * map);

private:
    PlayerManager * playerManager;
    BubbleManager * bubbleManager;
    PropManager * propManager;
    Client * client;
    GameMap * map;
    int gameStatus;

    Operator * oper;
    void opHandle(Operator::OpCode opcode, Operator::OpType type);

    void onEnter();
    void onExit();

    void syncLocalPlayerPosition(float dt);

    void onGameInit(const void* msg);
    void onGameStatusChange(const void* msg);

    void toStart();
    void toOver();

    void onPlayerPositionChange(const void* msg);
    void onPlayerAttrChange(const void* msg);
    void onPlayerStatusChange(const void* msg);

    void onLocalPlayerSetBubble();

    void onBubbleSet(const void* msg);
    void onBubbleBoom(const void* msg);

    void onPropSet(const void* msg);

};

#endif // !__GAME_CONTROLLER_H__
