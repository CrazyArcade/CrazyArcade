#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"
#include "Settings.h"
#include "StartScene.h"

class SettingsScene : public cocos2d::Layer
{
private:
    void menuBackCallback(cocos2d::Ref* pSender);
    cocos2d::Menu* createText();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SettingsScene);
};

#endif // _SETTINGS_SCENE_H__