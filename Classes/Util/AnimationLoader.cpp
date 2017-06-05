#include "AnimationLoader.h"

USING_NS_CC;

void AnimationLoader::runAnimation(const std::string& animationName, cocos2d::Sprite * sprite)
{
    //CCASSERT(dynamic_cast<Sprite*>(this) != nullptr, "this must be sprite!");
    auto animation = getAnimation(animationName);
    if (animation != nullptr)
    {
        auto animate = Animate::create(animation);
        auto repeat = RepeatForever::create(animate);
        int tag = getAnimationTag(animationName);
        repeat->setTag(tag);
        sprite->runAction(repeat);
    }
}

void AnimationLoader::stopAnimation(cocos2d::Sprite * sprite)
{
    sprite->stopAllActions();
}

cocos2d::Animation * AnimationLoader::getAnimation(const std::string & animationName)
{
    auto res = animationList.find(animationName);
    if (res != animationList.cend()) return res->second;
    else return nullptr;
}

void AnimationLoader::loadAnimation(const std::string & animationName, float delay, int num)
{
    auto animation = Animation::create();
    for (int i = 1; i <= num; ++i)
    {
        std::string name = animationName;
        name.append(StringUtils::format("_%02d", i)).append(".png");
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
    }
    animation->setDelayPerUnit(delay);
    animation->setRestoreOriginalFrame(true);

    animationList.insert(animationName, animation);
}

int AnimationLoader::getAnimationTag(const std::string & animationName)
{
    return animationList.bucket(animationName);
}
