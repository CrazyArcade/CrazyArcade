#ifndef __UTIL_ANIMATIONLOADER_H__
#define __UTIL_ANIMATIONLOADER_H__

#include "cocos2d.h"

class AnimationLoader
{
public:
    /**
     * @param animationName
     * @param sprite normally just pass `this`
     */
    void runAnimation(const std::string& animationName, cocos2d::Sprite * sprite);

    void stopAnimation(cocos2d::Sprite * sprite);
    
    /**
     * get animation by name, you must load it first.
     * @return animation point if found, nullptr else
     */
    cocos2d::Animation * getAnimation(const std::string& animationName);
protected:
    
    /**
     * @param animationName the name must be equal to file prefix (e.g. alive_01.png, then you must pass "alive")
     * @param delay time per frame play
     * @num num of animations (e.g. bubble alive has 3 files)
     */
    void loadAnimation(const std::string& animationName, float delay, int num);
private:
    // store animation
    cocos2d::Map<std::string, cocos2d::Animation *> animationList;

    // get animation index in map
    int getAnimationTag(const std::string& animationName);
};

#endif