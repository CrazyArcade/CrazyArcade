#ifndef __SCENE_UI_RESULT__
#define __SCENE_UI_RESULT__

#include <cocos2d.h>
#include "Settings.h"

USING_NS_CC;

class ResultBox : public cocos2d::Layer {
public:
    enum Result {
        VICTORY,
        DEFEAT
    };

    virtual bool init();

    CREATE_FUNC(ResultBox);

    void setResult(Result result);
private:
    cocos2d::Label* label;

    cocos2d::Sprite* pad;
};

#endif