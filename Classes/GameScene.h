#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Settings.h"

class GameScene : public cocos2d::Layer
{
private:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void keyPressedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
