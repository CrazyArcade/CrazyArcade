#ifndef __OPERATOR_KEYBOARD_H__
#define __OPERATOR_KEYBOARD_H__

#include "cocos2d.h"
#include "Operator.h"

class KeyBoard : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(KeyBoard);

    Operator::HandleFunc handle;

    void start();

    void stop();
private:
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif