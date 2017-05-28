#ifndef __SCENE_GAMESCENE_H__
#define __SCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "Settings.h"
#include "UI/GameMap.h"
#include "Client.h"
#include "Controller/PlayerController.h"
#include "Controller/BubbleController.h"

class GameScene : public cocos2d::Layer
{
private:
    void keyPressedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void menuBackCallback(cocos2d::Ref* pSender);
    cocos2d::Menu* createText();

    cocos2d::TMXTiledMap *_tileMap;

    //Client * _client;
    GameMap * _map;
    PlayerController * _playerController;
    BubbleController* _bubbleController;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
