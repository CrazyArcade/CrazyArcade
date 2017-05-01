#pragma once
#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"
#include "Settings.h"
#include "StartScene.h"

class HelpScene : public cocos2d::Layer
{
private:
    cocos2d::Menu* createText();
    void menuBackCallback(cocos2d::Ref* pSender);
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelpScene);
};

#endif // __HELP_SCENE_H__