#include "Scene/LoadingScene.h"
#include "Scene/LoginScene.h"
#include "Settings.h"
#include "SimpleAudioEngine.h"

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
    const auto transition = TransitionFade::create(1, LoginScene::createScene());
    Director::getInstance()->replaceScene(transition);
}

void LoadingScene::loadSound()
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    //audio->preloadEffect("GameAudio/bubble1.wav");
    //audio->preloadEffect("GameAudio/bubble2.wav");
	audio->preloadEffect("Sound/lobbysound.ogg");
}

void LoadingScene::loadImage() {
    //undefined
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

}

void LoadingScene::loadSpriteFrame()
{
    auto cache = SpriteFrameCache::getInstance();
    
    cache->addSpriteFramesWithFile(Settings::Bubble::alive);
    cache->addSpriteFramesWithFile(Settings::Bubble::explosion);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameItem/Player/Player1/animation.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameItem/Player/Player2/animation.plist");

	return;
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
	loadCarton();
	createText();
    scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::endLoading), 0.5);
    return true;
}

cocos2d::ui::LoadingBar* LoadingScene::createLoadingBar(){
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.3f;

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/lobbySound.ogg");

    auto loadingBar = ui::LoadingBar::create("SettingsScene/loadingbar4.png");
    loadingBar->setPosition(Vec2(visibleSize.width / 2, baseY));
    loadingBar->setScale(0.8);
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPercent(10);

    loadSpriteFrame();
    loadingBar->setPercent(40);
    
    loadImage();
    loadingBar->setPercent(70);

    loadSound();
    loadingBar->setPercent(100);

	//auto loadBg = Sprite::create("SettingsScene/loadingbar401.png");
	//loadBg->setPosition(Vec2(visibleSize.width / 3, baseY + 50));
	//this->addChild(loadBg);

	auto loadProgress = ProgressTimer::create(Sprite::create("SettingsScene/loadingbar402.png"));
	loadProgress->setPosition(Vec2(visibleSize.width / 2, baseY + 50));
	loadProgress->setType(ProgressTimer::Type::BAR);
	loadProgress->setMidpoint(Point(0,1));
	this->addChild(loadProgress);

	CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(1);
   
    return loadingBar;
}
void LoadingScene::loadCarton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("SettingsScene/load01.png");
	auto sprite2 = Sprite::create("SettingsScene/load04.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x - sprite->getContentSize().width, visibleSize.height / 2 + origin.y * 2));
	auto animation = Animation::create();
	char str[50] = { 0 };
	for (int i = 1;i < 5;++i) 
	{
		sprintf(str, "SettingsScene/load0%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}
	animation->setDelayPerUnit(0.1f/3);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	sprite->runAction(action);

	this->addChild(sprite);

	/*//scene2
	ActionInterval* move = MoveBy::create(0.5f, Point(sprite->getContentSize().width * 4,0));
	auto fadeIn = FadeIn::create(0.5);
	auto fadeOut = FadeOut::create(0.5);
	auto seq = Sequence::create(fadeIn,move, fadeOut, NULL);
	//sprite->runAction(seq);
	auto repeat = cocos2d::RepeatForever::create(seq);
	sprite->runAction(repeat);
	this->addChild(sprite);*/
}
void LoadingScene::createText()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto centerSize = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height *0.4f);
	//loading label
	auto label = Label::createWithTTF("Loading...", "fonts/Quicksand-Bold.ttf", 32);
	label->setPosition(centerSize);
	label->enableGlow(Color4B::GREEN);
	this->addChild(label);
}