#ifndef __UTIL_ANIMATIONLOADER_H__
#define __UTIL_ANIMATIONLOADER_H__

#include "cocos2d.h"

class AnimationLoader
{
public:
    void runAnimation(const std::string& animationName, cocos2d::Sprite * sprite);
    cocos2d::Animation * getAnimation(const std::string& animationName);
protected:
    void loadAnimation(const std::string& animationName, float delay, int num);
private:
    cocos2d::Map<std::string, cocos2d::Animation *> animationList;
};

#endif