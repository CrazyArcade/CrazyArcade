#ifndef __SCENE_HELPSCENE_H__
#define __SCENE_HELPSCENE_H__

#include "cocos2d.h"
#include"ui/UIButton.h"

class HelpScene : public cocos2d::Layer
{
private:
	void menuBackCallback(cocos2d::Ref* pSender);
	//void menuCloseCallback(cocos2d::Ref* pSender);
	void menuHelp01Callback(cocos2d::Ref* pSender);
	void menuHelp02Callback(cocos2d::Ref* pSender);
	void bg01Init();
	void bg02Init();
	void bg03Init();
	cocos2d::Menu* createText();
	void createCloseButton();
	void createItem();
	int  helpOn;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelpScene);
};

#endif // __HELP_SCENE_H__