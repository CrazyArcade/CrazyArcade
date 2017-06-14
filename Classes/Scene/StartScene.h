#ifndef __SCENE_STARTSCENE_H__
#define __SCENE_STARTSCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
private:
    bool musicOn = true; 
    cocos2d::Menu* createText();
    cocos2d::Sprite* createBGImage();
    void menuExitCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuHelpCallback(cocos2d::Ref * pSender);
    void menuSettingsCallback(cocos2d::Ref * pSender);
    void musicInit();
    void musicPP(cocos2d::Ref* pSender);    //play or pause the music
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);                
};

#endif // __START_SCENE_H__

