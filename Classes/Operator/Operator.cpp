#include "Operator.h"
#include "KeyBoard.h"
#include "Rocker.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#define OPERATOR KeyBoard
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define OPERATOR Rocker
#endif

#define GETOPERATOR static_cast<OPERATOR*>(this->getChildByTag(1))

bool Operator::init()
{
    auto operate = OPERATOR::create();
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
