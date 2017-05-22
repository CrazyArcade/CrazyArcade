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

void LoadingScene::endLoading(float dt) {
    const auto transition = TransitionFade::create(1,StartScene::createScene());
    Director::getInstance()->replaceScene(transition);
}

bool LoadingScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.35f;

    addChild(createLoadingBar());
    
    scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::endLoading), 0.5);
    return true;
}


cocos2d::ui::LoadingBar* LoadingScene::createLoadingBar(){
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.35f;
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    auto loadingBar = ui::LoadingBar::create("StartScene/loading bar.jpg");
    loadingBar->setPosition(Vec2(visibleSize.width / 2, baseY));
    loadingBar->setScale(0.5);
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);

    loadingBar->setPercent(50);

    //load effects
    audio->preloadEffect("GameAudio/bubble1.wav");
    audio->preloadEffect("GameAudio/bubble2.wav");

    loadingBar->setPercent(100);
   
    return loadingBar;
}
