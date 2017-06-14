#ifndef __ROOMSCENE_SCENE_H__
#define __ROOMSCENE_SCENE_H__

#include "cocos2d.h"
#include "Scene/UI/RoleBox.h"
#include "Controller/RoomController.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

class RoomScene :public cocos2d::Layer
{
private:
    void createUI();

    RoomController * roomController;
    
    cocos2d::ui::Button * readyButton;
    cocos2d::Vector<cocos2d::Sprite*> userBoxes;
    cocos2d::Vector<RoleBox*> roleBoxes;
    
    std::function<void(bool)> readyButtonCallBack;
    std::function<void(int)> roleChangeCallback;

    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
    
    void createReadyButton();

    void createTitle();
    
    void initUserBox();

    void initRoleBox();

    void createBackButton();

    void createBackground();

public:
    static cocos2d::Scene * createScene();
    virtual bool init();
    CREATE_FUNC(RoomScene);
};
#endif // !__ROOMSCENE_SCENE_H__

