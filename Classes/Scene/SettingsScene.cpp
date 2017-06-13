#include "SettingsScene.h"
#include "Settings.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SettingsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool SettingsScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite * bg = Sprite::create("SettingsScene/background1.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);
	
	

	//the sound
	auto soundOnMenuItem = MenuItemImage::create(
		"SettingsScene/sound-on.png",
		"SettingsScene/sound-on.png");
	auto soundOffMenuItem = MenuItemImage::create(
		"SettingsScene/sound-off.png",
		"SettingsScene/sound-off.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingsScene::menuSoundToggleCallback, this),
		soundOnMenuItem,
		soundOffMenuItem, NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(visibleSize.width*0.75f, visibleSize.height*0.3f)));

	//the music
	const auto music = Menu::create();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("StartScene/bgmusic.mp3");
	musicOn = UserDefault::getInstance()->getBoolForKey("musicOn", true);

	auto musicOnMenuItem = MenuItemImage::create(
		"SettingsScene/music-on.png",
		"SettingsScene/music-on.png");
	auto musicOffMenuItem = MenuItemImage::create(
		"SettingsScene/music-off.png",
		"SettingsScene/music-off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingsScene::menuMusicToggleCallback, this),
		musicOnMenuItem,
		musicOffMenuItem,
		NULL);
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(visibleSize.width*0.75f, visibleSize.height*0.4f)));


	//OK button
	auto okMenuItem = MenuItemImage::create(
		"SettingsScene/ok.png",
		"SettingsScene/ok.png",
		CC_CALLBACK_1(SettingsScene::menuBackCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(visibleSize.width*0.5f, visibleSize.height*0.5f)));

	Menu * mn = Menu::create(soundToggleMenuItem,
		musicToggleMenuItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

    addChild(createText());
	

    return true;
}

cocos2d::Menu* SettingsScene::createText() {
    const auto buttons = Menu::create();

    const auto backButton = MenuItemLabel::create(
        Label::createWithTTF("Back", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(SettingsScene::menuBackCallback, this));

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    backButton->setPosition(backButton->getContentSize().width / 2 + 30, baseY + 30);

    buttons->addChild(backButton, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

void SettingsScene::musicPP(cocos2d::Ref * pSender) {
	if (musicOn)
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	else
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	musicOn = !musicOn;
	UserDefault::getInstance()->setBoolForKey("musicOn", musicOn);
}

void SettingsScene::menuBackCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}
void SettingsScene::menuSoundToggleCallback(cocos2d::Ref * pSender) 
{
	//const auto scene = HelpScene::createScene();
	//Director::getInstance()->pushScene(scene);
	
}
void SettingsScene::menuMusicToggleCallback(cocos2d::Ref * pSender) 
{
	//const auto scene = HelpScene::createScene();
	//Director::getInstance()->pushScene(scene);
	//auto scene = StartScene::createScene();
	musicPP(pSender);
	
}
void SettingsScene::menuOkCallback(cocos2d::Ref * pSender)
{
	const auto scene = StartScene::createScene();
	Director::getInstance()->pushScene(scene);
}