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

    void onPlayerJoin(cocos2d::EventCustom* event);
    void onPlayerPositionChange(cocos2d::EventCustom* event);

    void onLocalPlayerSetBubble();

    void onBubbleSet(cocos2d::EventCustom* event);
    void onBubbleBoom(cocos2d::EventCustom* event);

};

#endif // !__GAME_CONTROLLER_H__
