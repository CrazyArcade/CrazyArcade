#ifndef __SCENE_UI_ROLEBOX__
#define __SCENE_UI_ROLEBOX__

#include "cocos2d.h"

class RoleBox : public cocos2d::Sprite
{
public:

    enum roleChoice {
        Player1,
        Player2,
        Player3
    };

    virtual bool init();
    static RoleBox* create(roleChoice role);

    void setChosen(bool choice);
    roleChoice getRole();

private:
    bool isChosen = false;
    roleChoice _role;
};

#endif