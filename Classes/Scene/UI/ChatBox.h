#ifndef __SCENE_UI_CHAT__
#define __SCENE_UI_CHAT__

#include "cocos2d.h"
#include "Settings.h"

class ChatBox :public cocos2d::Layer, cocos2d::TextFieldDelegate {
public:
    void onInputStart(cocos2d::TextFieldTTF* sender);                                 
    void onInputFinish(cocos2d::TextFieldTTF* sender);                                

    virtual bool init();
    CREATE_FUNC(ChatBox);

private:
    cocos2d::TextFieldTTF *boxInput = nullptr;
};

#endif