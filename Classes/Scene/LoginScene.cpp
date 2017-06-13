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

	Sprite * bg = Sprite::create("RoomScene/bg.png");
	bg->setScale(1.5);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//log in item,username editbox input
	auto editBoxSize = Size(visibleSize.width/2, visibleSize.height * 0.1);
	
	std::string pNormalSprite = "RoomScene/c8.png";
	_editUserName = cocos2d::ui::EditBox::create(editBoxSize + Size(0,20) , cocos2d::ui::Scale9Sprite::create(pNormalSprite));
	_editUserName->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	_editUserName->setFontColor(Color3B::BLUE);
	_editUserName->setPlaceHolder("Name:");
	_editUserName->setPlaceholderFontColor(Color3B::WHITE);
	_editUserName->setMaxLength(20);
	_editUserName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editUserName->setDelegate(this);
	_editUserName->setVisible(true);
	this->addChild(_editUserName);

	//password editbox
	_editPassword = cocos2d::ui::EditBox::create(Size(editBoxSize.width,
		editBoxSize.height +20),"RoomScene/c8.png");
	_editPassword->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - editBoxSize.height*1.5));
	_editPassword->setFontColor(Color3B::BLUE);
	_editPassword->setPlaceHolder("Password:");
	_editPassword->setMaxLength(20);
	_editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editPassword->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	_editPassword->setDelegate(this);
	this->addChild(_editPassword);
	
	//login menu
	auto loginItem = cocos2d::MenuItemImage::create(
		"RoomScene/login.png",
		"RoomScene/login.png");
	auto loginToggleItem = cocos2d::MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(LoginScene::menuLoginCallback, this),
		loginItem,
		NULL
	);

	loginItem->setPosition(Director::getInstance()->convertToGL(Vec2(visibleSize.width/2,visibleSize.height*3/4)));

    Menu * mn = Menu::create(loginToggleItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	addChild(createText());

	return true;
}
void LoginScene::menuLoginCallback(cocos2d::Ref* pSender)
{
	auto scene = RoomScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void LoginScene::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editbox %p didbegin", editBox);
}
void LoginScene::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{

}
void LoginScene::editBoxTextChanged(
	cocos2d::ui::EditBox* editBox, const std::string &text)
{

}
void LoginScene::editBoxReturn(cocos2d::ui::EditBox* editBox)
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