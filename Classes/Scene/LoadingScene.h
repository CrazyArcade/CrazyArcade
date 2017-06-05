#ifndef __SCENE_LOADINGSCENE_H__
#define __SCENE_LOADINGSCENE_H__

#include "cocos2d.h"
#include "Scene/StartScene.h"
#include "ui/CocosGUI.h"

class LoadingScene : public cocos2d::Layer
{
private:
    CocosDenshion::SimpleAudioEngine* audio;
	cocos2d::Sprite *_player2;
	cocos2d::Action *_walkAction;
	cocos2d::Action *_moveAction;
	bool _moving;
    void endLoading(float dt);
    void loadSound();
    void loadImage();
    void loadSpriteFrame();
    cocos2d::ui::LoadingBar* createLoadingBar();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);
};

#endif // __SCENE_LOADINGSCENE_H__