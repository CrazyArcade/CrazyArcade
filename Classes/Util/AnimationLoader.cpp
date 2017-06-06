#include "AnimationLoader.h"
#include <functional>

USING_NS_CC;

AnimationLoader::AnimationLoader()
{
    animationCache = AnimationCache::getInstance();
}

void AnimationLoader::runAnimation(const std::string& animationName, cocos2d::Sprite * sprite)
{
    //CCASSERT(dynamic_cast<Sprite*>(this) != nullptr, "this must be sprite!");
    auto animation = getAnimation(animationName);
    if (animation != nullptr)
    {
        auto animate = Animate::create(animation);
        auto repeat = RepeatForever::create(animate);
        
        auto flag = getFlag(animationName);
        repeat->setFlags(flag);

        sprite->runAction(repeat);
    }
}

void AnimationLoader::stopAnimation(cocos2d::Sprite * sprite)
{
    sprite->stopAllActions();
}

void AnimationLoader::stopAnimation(const std::string & animationName, cocos2d::Sprite * sprite)
{
    auto flag = getFlag(animationName);
    sprite->stopActionsByFlags(flag);
}

cocos2d::Animation * AnimationLoader::getAnimation(const std::string & animationName)
{
    return animationCache->getAnimation(animationName);
}

void AnimationLoader::loadAnimation(const std::string & animationName, float delay, int num)
{
    if (getAnimation(animationName) != nullptr) return;

    auto animation = Animation::create();
    for (int i = 1; i <= num; ++i)
    {
        std::string name = animationName;
        name.append(StringUtils::format("_%02d", i)).append(".png");
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
    }
    animation->setDelayPerUnit(delay);
    animation->setRestoreOriginalFrame(true);

    animationCache->addAnimation(animation, animationName);
}

unsigned int AnimationLoader::getFlag(const std::string & animationName)
{
    return std::hash<std::string>()(animationName);
}