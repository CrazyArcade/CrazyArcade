#ifndef  _LOGINSCENE_SCENE_H__
#define  _LOGINSCENE_SCENE_H__

#include"cocos2d.h"
#include"cocos2d/cocos/ui/CocosGUI.h"
#include"cocos2d/extensions/cocos-ext.h"


class LoginScene :public cocos2d::Layer
{
private:

    cocos2d::Sprite* usernameBG = nullptr;

    cocos2d::Sprite* createBackground();
    cocos2d::Sprite* createLoginBox();
    cocos2d::Menu* createLoginItem();

    void initUserBox();
    void initcheckBox();

    void menuBackCallback(cocos2d::Ref* pSender);
    void menuLoginCallback(cocos2d::Ref* pSender);
    void checkboxSelectedEvent(cocos2d::Ref* pSender);
    void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType event);

public:

    static cocos2d::Scene * createScene();
    virtual bool init();
    CREATE_FUNC(LoginScene);

};
#endif // ! _LOGINSCENE_SCENE_H__
