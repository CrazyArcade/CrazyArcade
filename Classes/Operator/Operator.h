#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "cocos2d.h"

class Operator : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(Operator);

    enum class OpCode
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        SPACE
    };

    enum class OpType
    {
        PRESS,
        RELEASE
    };
    using HandleFunc = std::function<void(OpCode, OpType)>;

    void addHandle(HandleFunc handle);

    void start();

    void stop();
    
};

#endif // !__OPERATOR_H__




