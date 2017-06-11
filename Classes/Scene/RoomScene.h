#pragma once
#ifndef __ROOMSCENE_SCENE_H__
#define __ROOMSCENE_SCENE_H__

#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Settings.h"
#include"Scene/GameScene.h"
#include"Scene/StartScene.h"
#include"UI/CocosGUI.h"

class RoomScene :public cocos2d::Layer
{
private:
	cocos2d::Menu *createText();
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuReadyCallback(cocos2d::Ref* pSender);

    cocos2d::Vector<cocos2d::Sprite*> userBoxes;
    void initUserBox();

    cocos2d::Vector<cocos2d::Sprite*> roleBoxes;
    void initRoleBox();
    
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(RoomScene);
}; 
#endif // !__ROOMSCENE_SCENE_H__

