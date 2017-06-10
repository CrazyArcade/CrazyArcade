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
	auto label = Label::createWithTTF("ROOM", "fonts/OpenSans-Regular.ttf", 32);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height ));
	label->enableGlow(Color4B::BLUE);
	this->addChild(label, 1);

	//static node
	Sprite * bg = Sprite::create("RoomScene/bg03.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//the room list
	auto label1 = Label::createWithTTF("roomlist", Settings::Font::Type::base, Settings::Font::Size::normal);
	label1->setPosition(Vec2(visibleSize.width*0.25f , visibleSize.height - label->getContentSize().height * 2));
	label1->enableShadow();
	this->addChild(label1, 1);

	Vector<Sprite*> roomlist;
	for (int i = 1;i < 5;++i) {
		Sprite* room = Sprite::create("RoomScene/c3.png");
		room->setPosition(Vec2(visibleSize.width * 0.25f, visibleSize.height - room->getContentSize().height*2.5*(i + 1)));
		room->setScale(2.5);
		roomlist.pushBack(room);
		this->addChild(room);
	}

	//show the property of the player
	Vector<Sprite*> proplist;
	for (int i = 1;i < 5;++i) {
		Sprite* prop = Sprite::create("RoomScene/teamBackground_0.png");
		prop->setPosition(Vec2(visibleSize.width*0.5f + origin.x + prop->getContentSize().width, visibleSize.height - prop->getContentSize().height * 2.5*(i + 1)));
		prop->setScale(2.5);
		proplist.pushBack(prop);
		this->addChild(prop);
	}

	auto propiter = proplist.begin();
	auto prop = *propiter;
	auto label2 = Label::createWithTTF("proplist", Settings::Font::Type::base, Settings::Font::Size::normal);
	label2->setPosition(Vec2(visibleSize.width*0.6f , visibleSize.height - prop->getContentSize().height * 2));
	label2->enableShadow();
	this->addChild(label2, 1);

	//the player case
	auto s = Director::getInstance()->getWinSize();
	DrawNode *drawNode = DrawNode::create();
	this->addChild(drawNode, 20);
	Vec2 points[] = { Vec2(visibleSize.width*0.2f,visibleSize.height*0.2f),Vec2(visibleSize.width*0.3f,visibleSize.height*0.2f),
	Vec2(visibleSize.width*0.4f,visibleSize.height*0.2f),Vec2(visibleSize.width*0.5f,visibleSize.height*0.2f) };
	drawNode->drawPolygon(points, sizeof(points) / sizeof(points[0]), 
		Color4F(1, 0, 0, 0), 2, Color4F(0, 0, 1, 1));
	drawNode->drawSolidRect(Vec2(visibleSize.width*0.15f, visibleSize.height*0.15f), Vec2(visibleSize.width*0.22f, visibleSize.height*0.30f), Color4F(34/255,110/255,1,0.7));
	drawNode->drawSolidRect(Vec2(visibleSize.width*0.23f, visibleSize.height*0.15f), Vec2(visibleSize.width*0.30f, visibleSize.height*0.30f), Color4F(34 / 255, 110 / 255, 1, 0.7));
	/*Vector<Sprite*> playerCaselist;
	for (int i = 1;i < 4;++i) {
		Sprite * playerCase = Sprite::create("RoomScene/player_bg.png");
		playerCase->setPosition(Vec2(visibleSize.width*0.1f + playerCase->getContentSize().width*i, visibleSize.height*0.18f));
		playerCaselist.pushBack(playerCase);
		this->addChild(playerCase);
	}
	*/


	////ready button
	const auto readybutton = MenuItemLabel::create(
		Label::createWithTTF("Ready?", Settings::Font::Type::base, Settings::Font::Size::label),
		CC_CALLBACK_1(RoomScene::menuReadyCallback, this));
	readybutton->setPosition(visibleSize.width*0.4f + readybutton->getContentSize().width, visibleSize.height*0.1f);
	const auto mn = Menu::create();
	mn->addChild(readybutton, 1);
	mn->setPosition(1, 0);
	this->addChild(mn);

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