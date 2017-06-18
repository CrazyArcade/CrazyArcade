#include "HelpScene.h"
#include "Settings.h"
#include "Scene/StartScene.h"

USING_NS_CC;

Scene* HelpScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelpScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    addChild(createText());

	bg01Init();
	helpOn = UserDefault::getInstance()->getIntegerForKey("helpOn", 0);
	if (helpOn == 0) {
		bg01Init();
		createCloseButton();
	}
	else if (helpOn == 1) {
		bg02Init();
		createItem();
	}
	else {
		bg03Init();
		createItem();
	}
	return true;
}
void HelpScene::bg01Init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  origin = Director::getInstance()->getVisibleOrigin();

	//auto bg = Sprite::create("Scene/help04.png");
	/*auto bg = MenuItemImage::create(
	"Scene/help04.png",
	"Scene/help04.png",
	"Scene/help04.png",
	CC_CALLBACK_1(HelpScene::menuHelp02Callback, this)
	);*/
	auto bgOn = cocos2d::MenuItemImage::create(
		"Scene/help04.png",
		"Scene/help04.png");
	auto bgOff = bgOn;
	auto bg = cocos2d::MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(HelpScene::menuHelp02Callback, this),
		bgOn,
		bgOff,
		NULL);
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScaleZ(1);
	auto mn = Menu::create(bg, NULL);
	mn->setPosition(Vec2::ZERO);

	//this->addChild(bg);
	this->addChild(mn);
}

void HelpScene::bg02Init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("Scene/help01.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScaleZ(2);
	this->addChild(bg);
}

void  HelpScene::bg03Init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("Scene/help02.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScaleZ(3);
	this->addChild(bg);
}
void HelpScene::createItem()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//last item
	auto lastOnItem = MenuItemImage::create(
		"Scene/helpLastOn.png",
		"Scene/helpLastOn.png");
	lastOnItem->setPosition(Vec2(visibleSize.width *0.5f, visibleSize.height * 0.3f));
	auto lastOffItem = MenuItemImage::create(
		"Scene/helpLastOff.png",
		"Scene/helpLastOff.png");
	auto lastToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(HelpScene::menuHelp01Callback, this),
		lastOnItem,
		lastOffItem, NULL);
	lastToggleMenuItem->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.13f));
	//next item 
	auto nextOnItem = MenuItemImage::create(
		"Scene/helpNextOn.png",
		"Scene/helpNextOn.png");
	auto nextOffItem = MenuItemImage::create(
		"Scene/helpNextOff.png",
		"Scene/helpNextOff.png");
	auto nextToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(HelpScene::menuHelp02Callback, this),
		nextOnItem,
		nextOffItem, NULL);
	nextToggleMenuItem->setPosition(Vec2(visibleSize.width * 0.5f + lastToggleMenuItem->getContentSize().width, visibleSize.height * 0.13f));
	//close item
	auto closeItem = MenuItemImage::create(
		"Scene/helpClose02.png",
		"Scene/helpClose02.png",
		"Scene/helpClose02.png",
		CC_CALLBACK_1(HelpScene::menuBackCallback, this));
	closeItem->setPosition(Vec2(visibleSize.width * 0.5f + lastToggleMenuItem->getContentSize().width * 2, visibleSize.height * 0.13f));
	if (helpOn == 1) {
		auto mn = Menu::create(lastOffItem, nextToggleMenuItem, closeItem, NULL);
		mn->setPosition(Vec2::ZERO);
		this->addChild(mn);
	}
	else {
		auto mn = Menu::create(lastToggleMenuItem, nextToggleMenuItem, closeItem, NULL);
		mn->setPosition(Vec2::ZERO);
		this->addChild(mn);
	}
}


cocos2d::Menu* HelpScene::createText() {                                
    const auto buttons = Menu::create();

    const auto backButton=MenuItemLabel::create(
        Label::createWithTTF("Back", Settings::Font::Type::base, Settings::Font::Size::label),
        CC_CALLBACK_1(HelpScene::menuBackCallback, this));

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    backButton->setPosition(backButton->getContentSize().width / 2 + 30, baseY + 30);

    buttons->addChild(backButton, 1);

    buttons->setPosition(0, 0);

    return buttons;
}
void HelpScene::createCloseButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto closeButton = ui::Button::create("Scene/helpClose.png", "Scene/helpClose.png");
	closeButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.15f));
	closeButton->setOpacity(233);

	closeButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED) return;
		Director::getInstance()->popScene();
	});
	this->addChild(closeButton);
}

void HelpScene::menuBackCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
	UserDefault::getInstance()->setIntegerForKey("helpOn", 0);
}
void HelpScene::menuHelp01Callback(Ref* pSender)
{
	helpOn = UserDefault::getInstance()->getIntegerForKey("helpOn", 0);
	UserDefault::getInstance()->setIntegerForKey("helpOn", --helpOn);
	Director::getInstance()->replaceScene(TransitionFade::create(1.2f, HelpScene::createScene()));
}
void HelpScene::menuHelp02Callback(Ref* pSender)
{
	helpOn = UserDefault::getInstance()->getIntegerForKey("helpOn", 0);
	UserDefault::getInstance()->setIntegerForKey("helpOn", ++helpOn);
	Director::getInstance()->replaceScene(TransitionFade::create(1.2f, HelpScene::createScene()));
}