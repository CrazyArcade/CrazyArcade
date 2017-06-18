#include "Operator.h"
#include "KeyBoard.h"
#include "Rocker.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#define GETOPERATOR static_cast<KeyBoard*>(this->getChildByTag(1))
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define GETOPERATOR static_cast<Rocker*>(this->getChildByTag(1))
#endif

bool Operator::init()
{
    auto operate =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        KeyBoard::create();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        Rocker::create();
#endif
    operate->setTag(1);
    addChild(operate);

    return true;
}

void Operator::addHandle(HandleFunc handle)
{
    GETOPERATOR->handle = handle;
}

void Operator::start()
{
    GETOPERATOR->start();
}

void Operator::stop()
{
    GETOPERATOR->stop();
}
