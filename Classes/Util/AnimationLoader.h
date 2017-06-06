#ifndef __UTIL_ANIMATIONLOADER_H__
#define __UTIL_ANIMATIONLOADER_H__

#include "cocos2d.h"

class AnimationLoader
{
public:
    AnimationLoader();
    /**
     * @param animationName
     * @param sprite normally just pass `this`
     */
    void runAnimation(const std::string& animationName, cocos2d::Sprite * sprite);

    void stopAnimation(cocos2d::Sprite * sprite);

    void stopAnimation(const std::string& animationName, cocos2d::Sprite * sprite);
    
    /**
     * get animation by name
     * @param animationName
     * @return cocos2d::Animation * or nullptr
     */
    cocos2d::Animation * AnimationLoader::getAnimation(const std::string & animationName);
    
protected:

    /**
     * @param animationName the name must be equal to file prefix (e.g. alive_01.png, then you must pass "alive")
     * @param delay time per frame play
     * @num num of animations (e.g. bubble alive has 3 files)
     */
    void loadAnimation(const std::string& animationName, float delay, int num);
private:

    cocos2d::AnimationCache * animationCache;

    /**
     * get animation hash
     */
    unsigned int getFlag(const std::string & animationName);
};

#endif