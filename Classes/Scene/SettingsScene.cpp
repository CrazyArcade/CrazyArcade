#include "SettingsScene.h"

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

	Sprite * bg = Sprite::create("setting-back.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//the sound
	auto soundOnMenuItem = MenuItemImage::create(
		"sound-on.png",
		"sound-on.png");
	auto soundOffMenuItem = MenuItemImage::create(
		"sound-off.png",
		"sound-off.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this),
		soundOnMenuItem,
		soundOffMenuItem, NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 220)));

	//the music
	auto musicOnMenuItem = MenuItemImage::create(
		"music-on.png",
		"music-on.png");
	auto musicOffMenuItem = MenuItemImage::create(
		"music-off.png",
		"music-off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
		musicOnMenuItem,
		musicOffMenuItem,
		NULL);
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 362)));


	//OK button
	auto okMenuItem = MenuItemImage::create(
		"ok-down.png",
		"ok-up.png",
		CC_CALLBACK_1(Setting::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));

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

void SettingsScene::menuBackCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}
void SettingsScene::menuSoundToggleCallback(cocos2d::Ref * pSender) {

}
void SettingsScene::menuMusicToggleCallback(cocos2d::Ref * pSender) {

}