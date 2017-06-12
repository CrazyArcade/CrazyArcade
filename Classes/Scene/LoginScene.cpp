#include"LoginScene.h"
#include"StartScene.h"


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
	auto editBoxSize = Size(visibleSize.width - 100, visibleSize.height * 0.1);
	
	std::string pNormalSprite = "edit.png";
	_editUserName = cocos2d::ui::EditBox::create(editBoxSize + Size(0,40), cocos2d::ui::Scale9Sprite::create(pNormalSprite));
	_editUserName->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
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
		editBoxSize.height +20),"edit.png");
	_editPassword->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
	_editPassword->setFontColor(Color3B::BLUE);
	_editPassword->setPlaceHolder("Password:");
	_editPassword->setMaxLength(20);
	_editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editPassword->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	_editPassword->setDelegate(this);
	this->addChild(_editPassword);
	
	//login menu
	Menu* mn = Menu::createWithItem(nullptr);

	this->addChild(mn);

	return true;
}
void LoginScene::menuLoginCallback(cocos2d::Ref* pSender)
{


}
void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editbox %p didbegin", editBox);
}
void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{

}
void editBoxTextChanged(
	cocos2d::ui::EditBox* editBox, const std::string &text)
{

}
void editBoxReturn(cocos2d::ui::EditBox* editBox)
{


}