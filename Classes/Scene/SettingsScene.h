#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"

class SettingsScene : public cocos2d::Layer
{
private:
    void menuBackCallback(cocos2d::Ref* pSender);
	void menuSoundToggleCallback(cocos2d::Ref *pSender);
	void menuMusicToggleCallback(cocos2d::Ref *pSender);
	void menuOkCallback(cocos2d::Ref *pSender);

    cocos2d::Menu* createText();
	void createBackground();
	void createMenu();

	bool okOn = true;
	bool musicOn = true;

    void musicPP(cocos2d::Ref * pSender);
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SettingsScene);
};

#endif // _SETTINGS_SCENE_H__