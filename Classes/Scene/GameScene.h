#ifndef __SCENE_GAMESCENE_H__
#define __SCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "Settings.h"

class GameScene : public cocos2d::Layer
{
private:
    void keyPressedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void menuBackCallback(cocos2d::Ref* pSender);
    cocos2d::Menu* createText();

    cocos2d::TMXTiledMap *_tileMap;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
