#ifndef __SCENE_UI_ROLEBOX__
#define __SCENE_UI_ROLEBOX__

#include "cocos2d.h"

class RoleBox : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(RoleBox);

    void setRole(const std::string& role);
    std::string getRole();

private:
    std::string role;
};

#endif