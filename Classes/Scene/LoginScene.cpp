#include"LoginScene.h"



USING_NS_CC;
USING_NS_CC_EXT;

Scene* LoginScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoginScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->addChild(createBackground());
//	this->addChild(createLoginBox());
	this->addChild(createText());
	this->addChild(createLoginItem());
	initUserBox();
	initPasswordBox();
	initcheckBox();
	initURLSkip();

	return true;
}
cocos2d::Sprite* LoginScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite * bg = Sprite::create("Scene/bg03.jpg");
	bg->setScale(2.4);
	//set transparent
	bg->setOpacity(255);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	
	return bg;
}
cocos2d::Sprite* LoginScene::createLoginBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite * loginBox = Sprite::create("RoomScene/loginform02.png");
	loginBox->setScale(1.5);
	loginBox->setOpacity(255);
    loginBox->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));

	return loginBox;
}
cocos2d::Menu* LoginScene::createLoginItem()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//login menu
	auto loginOnItem = cocos2d::MenuItemImage::create(
		"RoomScene/login03.png",
		"RoomScene/login03.png");
	auto loginOffItem = loginOnItem;
	auto loginToggleItem = cocos2d::MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(LoginScene::menuLoginCallback, this),
		loginOnItem,
		loginOffItem,
		NULL);
	loginOnItem->setScale(1.5);
	loginOffItem->setScale(1.5);
	loginToggleItem->setPosition(Director::getInstance()->convertToGL(Vec2(visibleSize.width / 3, visibleSize.height * 0.76f)));
	//loginItem->setAnchorPoint(Vec2(1, 0));
	Menu * mn = Menu::create(loginToggleItem, NULL);
	mn->setPosition(Vec2::ZERO);
	return mn;
}
void LoginScene::initUserBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//log in item,username editbox input
	auto input = Sprite::create("RoomScene/input_normal.png");
	//log in item,username editbox input
	auto editBoxSize = input->getContentSize()* 1.5;

	std::string pNormalSprite = "RoomScene/input_normal.png";
	_editUserName = cocos2d::ui::EditBox::create(editBoxSize, cocos2d::ui::Scale9Sprite::create(pNormalSprite));
	_editUserName->setPosition(Vec2(visibleSize.width / 3 + origin.x,
		visibleSize.height / 2 + origin.y + input->getContentSize().height*2));
	_editUserName->setFontColor(Color3B::BLUE);
	_editUserName->setPlaceHolder("Name:");
	_editUserName->setPlaceholderFontColor(Color3B::GRAY);
	_editUserName->setMaxLength(20);
	_editUserName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editUserName->setOpacity(100);
	_editUserName->setDelegate(this);
	_editUserName->setVisible(true);
	this->addChild(_editUserName);

}
void LoginScene::initPasswordBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto input = Sprite::create("RoomScene/input_normal.png");
	//log in item,username editbox input
	auto editBoxSize = input->getContentSize() * 1.5;

	//password editbox
	_editPassword = cocos2d::ui::EditBox::create(Size(editBoxSize.width,
		editBoxSize.height), "RoomScene/input_normal.png");
	_editPassword->setPosition(Vec2(visibleSize.width / 3 + origin.x,
		visibleSize.height / 2 + origin.y - editBoxSize.height*1.5 + input->getContentSize().height*2));
	_editPassword->setFontColor(Color3B::BLUE);
	_editPassword->setPlaceHolder("Password:");
	_editPassword->setMaxLength(20);
	_editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editPassword->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	_editPassword->setOpacity(100);
	_editPassword->setDelegate(this);
	this->addChild(_editPassword);

}
void LoginScene::initcheckBox()
{
	auto _checkBox = CheckBox::create();
	this->addChild(_checkBox, 0);
}

void LoginScene::initURLSkip()
{
	/*auto label = Label::createWithTTF("Forget the password?", "fonts/QuickSand-Bold.ttf", 10);
	addChild(label, 0);
	label->setPosition();

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(OpenURL::onTouchesEnded, this);*/

}
void LoginScene::menuLoginCallback(cocos2d::Ref* pSender)
{
	auto scene = RoomScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void LoginScene::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin", editBox);
}
void LoginScene::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd", editBox);
}
void LoginScene::editBoxTextChanged(
	cocos2d::ui::EditBox* editBox, const std::string &text)
{
	log("editBox %p TextChanged, text: %s", editBox, text.c_str());
}
void LoginScene::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
	log("edit return");
}
void LoginScene::checkboxSelectedEvent(cocos2d::Ref* pSender)
{

}
void LoginScene::menuBackCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
cocos2d::Menu* LoginScene::createText() {
	const auto buttons = Menu::create();

	const auto backButton = cocos2d::MenuItemLabel::create(
		Label::createWithTTF("Back", Settings::Font::Type::base, Settings::Font::Size::label),
		CC_CALLBACK_1(LoginScene::menuBackCallback, this));

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto baseY = visibleSize.height * 0.85f;

	backButton->setPosition(backButton->getContentSize().width / 2 + 30, baseY + 30);

	buttons->addChild(backButton, 1);

	buttons->setPosition(0, 0);

	return buttons;
}