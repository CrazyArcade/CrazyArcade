#ifndef __SCENE_HELPSCENE_H__
#define __SCENE_HELPSCENE_H__

#include "cocos2d.h"
#include "Settings.h"
#include "StartScene.h"

class HelpScene : public cocos2d::Layer
{
private:
    void menuBackCallback(cocos2d::Ref* pSender);
    cocos2d::Menu* createText();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelpScene);
};

#endif // __HELP_SCENE_H__