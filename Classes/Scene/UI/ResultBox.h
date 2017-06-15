#ifndef __SCENE_UI_RESULT__
#define __SCENE_UI_RESULT__

#include <cocos2d.h>
#include "Settings.h"

class ResultBox : public cocos2d::Layer {
public:

    virtual bool init();

    void initCustomEvent();

    CREATE_FUNC(ResultBox);

    void setResult(bool isWin);

private:
    cocos2d::Sprite* pad;
};

#endif