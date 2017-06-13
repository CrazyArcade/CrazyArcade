#pragma once
#ifndef  _LOGINSCENE_SCENE_H__
#define  _LOGINSCENE_SCENE_H__

#include<iostream>
#include"cocos2d.h"
#include"Settings.h"
#include"SettingsScene.h"
#include"RoomScene.h"
#include"StartScene.h"
#include"cocos2d/cocos/ui/CocosGUI.h"
#include"cocos2d/extensions/cocos-ext.h"


class LoginScene :public cocos2d::Layer,public cocos2d::ui::EditBoxDelegate
{
protected:
	cocos2d::ui::EditBox* _editUserName;
	cocos2d::ui::EditBox* _editPassword;
	void menuLoginCallback(cocos2d::Ref* pSender);
private:
	cocos2d::Menu* createText();
	void menuBackCallback(cocos2d::Ref* pSender);
public :
	
	static cocos2d::Scene * createScene();
	virtual bool init();
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(
		cocos2d::ui::EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
	CREATE_FUNC(LoginScene);

};
#endif // ! _LOGINSCENE_SCENE_H__
