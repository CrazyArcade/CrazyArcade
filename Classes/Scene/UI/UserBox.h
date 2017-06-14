#ifndef __SCENE_UI_USERBOX__
#define __SCENE_UI_USERBOX__

#include "cocos2d.h"
#include "ui/UITextField.h"
#include "Scene/UI/RoleBox.h"

class UserBox :public cocos2d::Sprite {
public:

    virtual bool init();
    CREATE_FUNC(UserBox);

    void setRole(RoleBox::roleChoice);
    std::string getName();

private:

    RoleBox::roleChoice _role;
    cocos2d::Sprite* rolePic;

    std::string name;
    cocos2d::ui::TextField* nameArea;

    bool isInit = true;

    void initNameArea();

};

#endif