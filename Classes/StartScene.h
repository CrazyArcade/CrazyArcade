#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "SettingsScene.h"

class StartScene : public cocos2d::Layer
{
private:
    bool musicOn = false;
    cocos2d::Menu* createText();
    void menuExitCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuHelpCallback(cocos2d::Ref * pSender);
    void menuSettingsCallback(cocos2d::Ref * pSender);
    cocos2d::Menu* musicInit();
    void musicPP(cocos2d::Ref* pSender);    //play or pause the music
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    StartScene();
    CREATE_FUNC(StartScene);                
};

#endif // __START_SCENE_H__

