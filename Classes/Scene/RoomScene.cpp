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

	createUI();
	return true;
}

void RoomScene::createUI()
{
	addChild(createBackground());
	addChild(createTitle());
	addChild(createReadyButton());
	addChild(createText());
	initUserBox();
	initRoleBox();
}
void RoomScene::initUserBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//playercaselist
	Vector<Sprite*> roomCase1list;
	Vector<Sprite*> roomCase2list;
	for (int i = 1; i < 9;++i)
	{
		Sprite* roomcase1 = Sprite::create("RoomScene/roomcase_01.png");
		Sprite* roomcase2 = Sprite::create("RoomScene/roomcase_02.png");
		if (i < 5) {
			roomcase1->setPosition(Vec2(roomcase1->getContentSize().width * i * 1.25 - roomcase1->getContentSize().width * 0.5f,
				visibleSize.height*0.68f));
			/*roomcase2->setPosition(Vec2(visibleSize.width*0.05f + roomcase1->getContentSize().width * i * 1.2,
			visibleSize.height * 0.68f - roomcase1->getContentSize().height + roomcase2->getContentSize().height));*/
		}
		else {
			roomcase1->setPosition(Vec2(roomcase1->getContentSize().width * (i - 4)* 1.25 - roomcase1->getContentSize().width *0.5f
				, visibleSize.height *0.68f - roomcase1->getContentSize().height * 1.28));
			/*roomcase2->setPosition(Vec2(visibleSize.width*0.05f + playercase2->getContentSize().width * (i - 4)* 1.2,
			visibleSize.height*0.68f - roomcase1->getContentSize().height * 2 + roomcase2->getContentSize().height));*/
		}
		roomcase1->setScale(1.25);
		roomcase2->setScale(1.25);

		roomCase1list.pushBack(roomcase1);
		roomCase2list.pushBack(roomcase2);
		this->addChild(roomcase1);
		//this->addChild(roomcase2);
	}
}
void RoomScene::initRoleBox()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//playercase 
	//the case backgorund
	auto caseTitle = Sprite::create("RoomScene/003c.png");
	auto roomcase = Sprite::create("RoomScene/roomcase_01.png");
	caseTitle->setPosition(Vec2(roomcase->getContentSize().width * 6 * 1.25, visibleSize.height * 0.8f));
	caseTitle->setScale(0.5);
	this->addChild(caseTitle, 1);
	DrawNode* casebg = DrawNode::create();
	casebg->drawSolidRect(Vec2(roomcase->getContentSize().width * 1.25 * 4.2, visibleSize.height * 0.85f),
		Vec2(visibleSize.width * 0.97f, visibleSize.height * 0.4f), Color4F(1.0 / 255, 108.0 / 255, 250.0 / 255, 0.95));
	for (int i = 1;i < 5; ++i) {
		casebg->drawSolidRect(Vec2(roomcase->getContentSize().width * 1.25 * 4.2 + roomcase->getContentSize().width * (i - 1) + roomcase->getContentSize().width * 0.1,
			visibleSize.height * 0.85f - caseTitle->getContentSize().height * 0.6),
			Vec2(roomcase->getContentSize().width*1.25*4.2 + roomcase->getContentSize().width * i,
				visibleSize.height*.85f - caseTitle->getContentSize().height * 3 * 0.5), Color4F(31.0 / 255, 58.0 / 255, 147.0 / 255, 0.95));

		casebg->drawSolidRect(Vec2(roomcase->getContentSize().width * 1.25 * 4.2 + roomcase->getContentSize().width * (i - 1) + roomcase->getContentSize().width * 0.1,
			visibleSize.height * 0.85f - caseTitle->getContentSize().height * 3 * 0.6),
			Vec2(roomcase->getContentSize().width*1.25*4.2 + roomcase->getContentSize().width * i,
				visibleSize.height*0.42f), Color4F(31.0 / 255, 58.0 / 255, 147.0 / 255, 0.95));
	}
	this->addChild(casebg);
}
cocos2d::Label* RoomScene::createTitle()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//the title
	auto label = Label::createWithTTF("ROOM", "fonts/OpenSans-Regular.ttf", 32);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
	label->enableGlow(Color4B::BLUE);
	return label;
}
cocos2d::Sprite* RoomScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//static node the background
	Sprite * bg = Sprite::create("RoomScene/bg03.jpg");
	bg->setScale(1.25);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	
	return bg;
}
cocos2d::Menu* RoomScene::createReadyButton()
{
	//ready button
	const auto readybutton = MenuItemLabel::create(
		Label::createWithTTF("Ready?", Settings::Font::Type::base, Settings::Font::Size::label),
		CC_CALLBACK_1(RoomScene::menuReadyCallback, this));

	const auto visibleSize = Director::getInstance()->getVisibleSize();

	readybutton->setPosition(visibleSize.width*0.4f + readybutton->getContentSize().width, visibleSize.height*0.1f);

	const auto mn = Menu::create();
	mn->addChild(readybutton, 1);
	mn->setPosition(1, 0);

	return mn;
}

cocos2d::Menu* RoomScene::createText() 
{
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