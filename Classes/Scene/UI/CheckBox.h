#pragma once
#ifndef _CHECKBOX__
#define _CHECKBOX__

#include"cocos2d.h"
#include"ui/UICheckBox.h"
#include"ui/UIText.h"

class CheckBox :public cocos2d::Layer
{
public:
	virtual bool init();
	void SelectedEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
	CREATE_FUNC(CheckBox);
private:
	cocos2d::ui::CheckBox* checkbox;
	void createAlert();
};

#endif // ! _CHECKBOX__
