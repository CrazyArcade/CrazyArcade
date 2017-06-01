#ifndef __SCENE_UI_CHAT__
#define __SCENE_UI_CHAT__

#include "cocos2d.h"
#include "Settings.h"
#include "cocos2d/cocos/ui/UIRichText.h"

class ChatBox :public cocos2d::Layer {
public:
    void InputStart(cocos2d::TextFieldTTF* sender);
    void InputFinish(cocos2d::TextFieldTTF* sender);
    void updateHistory();


    virtual bool init();
    CREATE_FUNC(ChatBox);
private:
    cocos2d::ui::RichText *boxHistory;
    cocos2d::TextFieldDelegate *boxInputDel = nullptr;
};

#endif