#include"RoomScene.h"
#include"Settings.h"

#include "UI/RoleBox.h"

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
	auto label = Label::createWithTTF("ROOM", Settings::Font::Type::title, Settings::Font::Size::label);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
	label->enableGlow(Color4B::BLUE);
	this->addChild(label,1);

	//static node
	Sprite * bg = Sprite::create("RoomScene/bg03.jpg");
	bg->setScale(1.25);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

    initUserBox();
    std::string roleDefault = "Player";
    for (int i = 1; i <= 2; i++)
        addChild(RoleBox::create(roleDefault + StringUtils::format("%d", i), i));
    
    //initRoleBox();

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

void RoomScene::initUserBox()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    for (int i = 1; i < 9; ++i)
    {
        auto userBox = Sprite::create("RoomScene/roomcase_01.png");
        if (i < 5)
        {
            userBox->setPosition(Vec2(userBox->getContentSize().width * i * 1.25 - userBox->getContentSize().width * 0.5f,
                visibleSize.height*0.68f));
        }
        else
        {
            userBox->setPosition(Vec2(userBox->getContentSize().width * (i - 4)* 1.25 - userBox->getContentSize().width *0.5f
                , visibleSize.height *0.68f - userBox->getContentSize().height * 1.28));
        }
        userBox->setScale(1.25);
        userBoxes.pushBack(userBox);
        this->addChild(userBox);
    }
}
