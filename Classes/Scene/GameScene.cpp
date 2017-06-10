#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "api_generated.h"
#include "Controller/GameController.h"
#include "Scene/UI/ResultBox.h"

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

    auto map = GameMap::create();
    map->setMap("town_10");
    addChild(map, -1);

    auto gameController = GameController::create();
    gameController->setMap(map);

    addChild(gameController, -1);
  
    auto _chatBox = ChatBox::create();
    addChild(_chatBox, 0);

    auto _resultBox = ResultBox::create();
    addChild(_resultBox, 1);
    _resultBox->setResult(ResultBox::Result::VICTORY);
  
    return true;
}