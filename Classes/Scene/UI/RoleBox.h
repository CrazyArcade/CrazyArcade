#ifndef __SCENE_UI_ROLEBOX__
#define __SCENE_UI_ROLEBOX__

#include "cocos2d.h"

class RoleWindow;

class RoleBox : public cocos2d::Layer
{
public:
    virtual bool initWithRole(std::string role,int8_t Rank);
    static RoleBox* create(std::string role, int8_t Rank);

    void setRole(const std::string& Role);
    std::string getRole();

private:
    std::string role;
    int8_t rank;
};

#endif