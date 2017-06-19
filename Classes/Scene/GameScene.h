#ifndef __SCENE_GAMESCENE_H__
#define __SCENE_GAMESCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
private:
	void onEnter();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
