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
	
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuReadyCallback(cocos2d::Ref* pSender);
	void createUI();
	cocos2d::Sprite * createBackground();
	cocos2d::Menu * createReadyButton();
	cocos2d::Label * createTitle();
	cocos2d::Menu *createText();
	void initRoleBox();
	void initUserBox();
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(RoomScene);
}; 
#endif // !__ROOMSCENE_SCENE_H__

