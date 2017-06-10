#ifndef __SCENE_GAMESCENE_H__
#define __SCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "Settings.h"
#include "UI/GameMap.h"
#include "Client.h"
#include "UI/ChatBox.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
