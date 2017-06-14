#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "Client.h"
#include "Manager/PlayerManager.h"
#include "Manager/BubbleManager.h"
#include "Manager/PropManager.h"
#include "Scene/UI/GameMap.h"

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

    void initListener();
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void onEnter();
    void onExit();

    void syncLocalPlayerPosition(float dt);

    void onGameInit(const void* msg);

    void onPlayerJoin(const void* msg);
    void onPlayerPositionChange(const void* msg);
    void onPlayerAttrChange(const void* msg);
    void onPlayerStatusChange(const void* msg);

    void onLocalPlayerSetBubble();

    void onBubbleSet(const void* msg);
    void onBubbleBoom(const void* msg);

    void onPropSet(const void* msg);

};

#endif // !__GAME_CONTROLLER_H__
