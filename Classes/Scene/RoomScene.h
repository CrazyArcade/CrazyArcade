#ifndef __ROOMSCENE_SCENE_H__
#define __ROOMSCENE_SCENE_H__

#include "cocos2d.h"
#include "Scene/UI/RoleBox.h"
#include "Controller/RoomController.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "Scene/UI/UserBox.h"

class RoomScene :public cocos2d::Layer
{
private:
    void createUI();

    RoomController * roomController;

    cocos2d::ui::Button * readyButton;
    void createReadyButton();
    std::function<void(bool isReady)> readyButtonCallBack;

    void onExit();
    
    cocos2d::Menu *createText();
    void menuBackCallback(cocos2d::Ref* pSender);

    cocos2d::Vector<UserBox*> userBox;
    void initUserBox();

    cocos2d::Vector<RoleBox*> roleBox;

public:
    static cocos2d::Scene * createScene();
    virtual bool init();
    CREATE_FUNC(RoomScene);
};
#endif // !__ROOMSCENE_SCENE_H__

