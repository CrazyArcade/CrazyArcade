#ifndef __SCENE_UI_CHAT__
#define __SCENE_UI_CHAT__

#include "cocos2d.h"
#include "Settings.h"
#include "cocos2d/cocos/ui/UIRichText.h"
#include "cocos2d/cocos/ui/UITextField.h"
#include "cocos2d/cocos/ui/UIText.h"
#include "cocos2d/cocos/ui/UIListView.h"

class ChatBox :public cocos2d::Layer {
public:
    virtual bool init();

    void keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

    CREATE_FUNC(ChatBox);
private:
    cocos2d::ui::ListView *boxHistory;
    cocos2d::ui::TextField *boxInput;

    void boxInputInit();
    void boxHistoryInit();
    void InputStart();
    void InputFinish();
    bool isInputing = false;
    void updateHistory(std::string txt);
};

#endif