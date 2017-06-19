/*<<<<<<< HEAD
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

	Sprite * bg = Sprite::create("SettingsScene/background5.jpg");
	//bg->setScale(2.4);
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
	listener->onTouchesEnded = CC_CALLBACK_2(OpenURL::onTouchesEnded, this);

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
=======*/
#include "LoginScene.h"
#include "Settings.h"
#include "StartScene.h"
#include "Scene/UI/CheckBox.h"
#include "Model/User.h"

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

    createBackground();
    createLoginButton();

    initUserBox();

    return true;
}

void LoginScene::createBackground()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite * bg = Sprite::create("Scene/bg03.jpg");
    bg->setScale(2.4f);
    //set transparent
    bg->setOpacity(255);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    addChild(bg);
}

void LoginScene::createLoginButton()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto loginButton = ui::Button::create("RoomScene/button_normal.png", "RoomScene/button_selected.png");
    loginButton->setTitleText("Login");
    loginButton->setTitleFontSize(Settings::Font::Size::normal);
    loginButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.35f));
    loginButton->setOpacity(233);

    loginButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type != ui::Widget::TouchEventType::ENDED) return;
        auto username = usernameInput->getString();
        if (username.empty())
        {
            MessageBox("Username can't be empty", "Alert");
        }
        else
        {
            username.substr(0, 16);
            User::getInstance()->setName(username);

            Director::getInstance()->replaceScene(TransitionFade::create(1.2f, StartScene::createScene()));
        }
    });
    addChild(loginButton);
    //login menu
    /*
    auto loginOnItem = cocos2d::MenuItemImage::create(
        "LoginScene/login03.png",
        "LoginScene/login03.png");
    auto loginOffItem = loginOnItem;
    auto loginToggleItem = cocos2d::MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(LoginScene::menuLoginCallback, this),
        loginOnItem,
        loginOffItem,
        NULL);
    loginOnItem->setScale(1.5f);
    loginOffItem->setScale(1.5f);
    loginToggleItem->setPosition(Director::getInstance()->convertToGL(Vec2(visibleSize.width / 2, visibleSize.height * 0.76f)));
    //loginItem->setAnchorPoint(Vec2(1, 0));
    Menu * mn = Menu::create(loginToggleItem, NULL);
    mn->setPosition(Vec2::ZERO);
    */
}

void LoginScene::initUserBox()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    usernameBG = Sprite::create("LoginScene/input_normal.png");
    usernameBG->setScale(1.2f);
    usernameBG->setOpacity(200);

    usernameInput = ui::TextField::create("Input Username Here", Settings::Font::Type::base, Settings::Font::Size::light);

    usernameInput->setColor(Color3B::BLACK);
    usernameInput->setCursorChar('|');
    usernameInput->setCursorEnabled(true);
    usernameInput->setMaxLength(15);
    usernameInput->setMaxLengthEnabled(true);
    usernameInput->setPosition(usernameBG->getContentSize() / 2);
    usernameInput->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));

    usernameBG->addChild(usernameInput);

    usernameBG->setScale(1.5);
    usernameBG->setPosition(Vec2(visibleSize.width / 2,
        visibleSize.height / 2 + usernameBG->getContentSize().height * 2));

    addChild(usernameBG);

}
void LoginScene::initcheckBox()
{
    auto _checkBox = CheckBox::create();
    this->addChild(_checkBox, 0);
}

void LoginScene::textFieldEvent(Ref* sender, ui::TextField::EventType event)
{
    switch (event) {
    case ui::TextField::EventType::ATTACH_WITH_IME:
        usernameBG->setTexture("LoginScene/input_active.png");
        break;
    case ui::TextField::EventType::DETACH_WITH_IME:
        usernameBG->setTexture("LoginScene/input_normal.png");
        break;
    }
}

void LoginScene::menuBackCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
//>>>>>>> refs/remotes/origin/master
}