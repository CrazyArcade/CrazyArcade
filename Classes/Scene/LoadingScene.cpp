#include "Scene/LoadingScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void LoadingScene::endLoading(cocos2d::Ref* render) {
    const auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool LoadingScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.35f;

    auto loadingBar = ui::LoadingBar::create("StartScene/loading bar.jpg");
    this->addChild(loadingBar);
    loadingBar->setPosition(Vec2(visibleSize.width/2, baseY));
    loadingBar->setScale(0.5);
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    //load some effects
    loadingBar->setPercent(50);
    loadingBar->runAction(RotateBy::create(2.5, 20));
    loadingBar->setPercent(100);

    auto hint = Label::createWithTTF("Press Any Key to Continue", Settings::Font::Type::base, Settings::Font::Size::label);
    hint->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(hint);


    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(LoadingScene::keyReleasedAct, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    return true;
}

void LoadingScene::keyReleasedAct(EventKeyboard::KeyCode keyCode, Event* event)
{
    endLoading(this);
}