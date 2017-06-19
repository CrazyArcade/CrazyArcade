#ifndef __SCENE_UI_CHAT__
#define __SCENE_UI_CHAT__

#include "cocos2d.h"
#include "Settings.h"
#include "ui/UITextField.h"
#include "ui/UIText.h"
#include "ui/UIListView.h"

class ChatBox :public cocos2d::Layer {
public:
    virtual bool init();

    void keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

    CREATE_FUNC(ChatBox);
private:
    cocos2d::ui::ListView *boxHistory;
    cocos2d::ui::TextField *boxInput;
    int tag = 1;

    void boxInputInit();
    void boxHistoryInit();
    void InputStart();
    void InputFinish();
    bool isInputing = false;
    void updateHistory(const std::string& txt);
};

#endif