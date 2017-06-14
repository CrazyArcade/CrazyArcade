#ifndef __SCENE_UI_USERBOX__
#define __SCENE_UI_USERBOX__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class UserBox : public cocos2d::Sprite {
public:

    virtual bool init();
    CREATE_FUNC(UserBox);

    void setRole(int role);

    void setUserName(const std::string& name);

private:
    int _role;
    cocos2d::Sprite* rolePic;

    std::string name;
    cocos2d::ui::Text * nameArea;

};

#endif