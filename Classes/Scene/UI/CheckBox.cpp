#include"CheckBox.h"

USING_NS_CC;

bool CheckBox::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	createAlert();

	auto checkbox = ui::CheckBox::create("Scene/checkbox_normal.png",
		"Scene/checkbox_active.png");
	checkbox->addTouchEventListener([&](cocos2d::Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	auto loginform = Sprite::create("RoomScene/loginform.png");
	loginform->setScale(1.5);
	loginform->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//checkbox->setAnchorPoint(Vec2(0.1,0.1));
	checkbox->setPosition(Vec2(visibleSize.width *0.2f, visibleSize.height*0.35f));
	checkbox->addEventListener(CC_CALLBACK_2(CheckBox::SelectedEvent, this));
	this->addChild(checkbox);
	return true;
}
void CheckBox::SelectedEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
	switch (type)
	{
	case ui::CheckBox::EventType::SELECTED:
		break;
	case ui::CheckBox::EventType::UNSELECTED:
		break;
	default:
		break;
	}

}
void CheckBox::createAlert()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	ui::Text* alert = ui::Text::create("keep login?", "fonts/QuickSand-Bold.ttf", 16);
	alert->setColor(Color3B());
	alert->setPosition(Vec2(visibleSize.width*0.25f,visibleSize.height*0.35f));
	this->addChild(alert);

}