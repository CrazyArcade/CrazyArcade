#include "GameScene.h"
#include "Controller/GameController.h"
#include "Scene/UI/ResultBox.h"
#include "Scene/UI/GameMap.h"
#include "Settings.h"
#include "Util/GameAudio.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->setName("root");
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
void GameScene::onEnter()
{
	Layer::onEnter();
    GameAudio::getInstance()->playBgm("Sound/inGame.mp3");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto map = GameMap::create();
    map->setMap("town_10");
    map->setPosition(Vec2((visibleSize.width - map->getMapSize().width * 40) * 0.5f, (visibleSize.height - map->getMapSize().height * 40) * 0.48f) + origin);
    addChild(map, -1);

    auto gameController = GameController::create();
    gameController->setMap(map);

    addChild(gameController, -1);
  
    //auto _chatBox = ChatBox::create();
    //addChild(_chatBox, 0);

    auto _resultBox = ResultBox::create();
    addChild(_resultBox, 1);
    //_resultBox->setResult(ResultBox::Result::VICTORY);
  
    return true;
}