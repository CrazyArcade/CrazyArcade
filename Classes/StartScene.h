#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene :
    public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    cocos2d::Menu* createTitle();
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __START_SCENE_H__

