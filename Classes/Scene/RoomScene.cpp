#include"RoomScene.h"
#include"Settings.h"

USING_NS_CC;
/*to do */
/*the back button*/
/*the case of the players*/

Scene* RoomScene::createScene()
{
	//scene is an auto release object 
	auto scene = Scene::create();

	//layer is an auto release object
	auto layer = RoomScene::create();

	//add layer as a child to scene
	scene->addChild(layer);

	//return the scene
	return scene;
}

bool RoomScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//the title
	auto label = Label::createWithTTF("ROOM", "fonts/OpenSans-Regular.ttf", 20);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height - origin.y));
	this->addChild(label);

	//static node
	Sprite * bg = Sprite::create("RoomScene/bg03.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//the room list
	auto label1 = Label::createWithTTF("roomlist", Settings::Font::Type::base, Settings::Font::Size::normal);\
		label->setPosition(Vec2(origin.x, visibleSize.height - label->getContentSize().height * 2));
	label1->enableShadow();
	this->addChild(label1);

	Vector<Sprite*> roomlist;
	for (int i = 1;i < 5;++i) {
		Sprite* room = Sprite::create("RoomScene/c3.png");
		room->setPosition(Vec2(visibleSize.width * 0.2f + origin.x, visibleSize.height - room->getContentSize().height*2.5*(i + 1)));
		room->setScale(2.5);
		roomlist.pushBack(room);
		this->addChild(room);
	}
	


	//show the property of the player
	Sprite* proplist = Sprite::create("RoomScene/teamBackground_0.png");
	proplist->setPosition(Vec2(visibleSize.width + origin.x - proplist->getContentSize().width*2.5, visibleSize.height - proplist->getContentSize().height));
	proplist->setScale(2.5);
	this->addChild(proplist);

	//ready button
	const auto readybutton = MenuItemLabel::create(
		Label::createWithTTF("Ready?", Settings::Font::Type::base, Settings::Font::Size::label),
		CC_CALLBACK_1(RoomScene::menuReadyCallback, this));
	readybutton->setPosition(visibleSize.width*0.4f+readybutton->getContentSize().width, visibleSize.height*0.1f);
	const auto mn = Menu::create();
	mn->addChild(readybutton, 1);
	mn->setPosition(1, 0);
	this->addChild(mn);

	/*// ready button
	auto button = cocos2d::ui::Button::create("button_normal.png","button_selected.png","button_surround.png");
	button->setTitleText("Ready?");
	button->setTitleFontName("fonts/OpenSans-Regular.ttf");
	button->setTitleFontSize(32);
	button->setPosition(Vec2(visibleSize.width / 2 + button->getContentSize().width, visibleSize.height*0.1f));
	button->addTouchEventListener(CC_CALLBACK_1(GameScene::createScene(), this));

	this->addChild(button, 1);
	*/
	addChild(createText());

	return true;
}

cocos2d::Menu* RoomScene::createText() {
	const auto buttons = Menu::create();

	const auto backButton = MenuItemLabel::create(
		Label::createWithTTF("Back", Settings::Font::Type::base, Settings::Font::Size::label),
		CC_CALLBACK_1(RoomScene::menuBackCallback, this));

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto baseY = visibleSize.height * 0.85f;

	backButton->setPosition(backButton->getContentSize().width / 2 + 30, baseY + 30);

	buttons->addChild(backButton, 1);

	buttons->setPosition(0, 0);

	return buttons;
}
void RoomScene::menuBackCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
void RoomScene::menuReadyCallback(cocos2d::Ref* pSender)
{
	const auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}