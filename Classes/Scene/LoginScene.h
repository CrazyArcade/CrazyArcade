#ifndef  _LOGINSCENE_SCENE_H__
#define  _LOGINSCENE_SCENE_H__

#include"cocos2d.h"
#include"cocos2d/cocos/ui/CocosGUI.h"
#include"cocos2d/extensions/cocos-ext.h"


class LoginScene :public cocos2d::Layer,public cocos2d::ui::EditBoxDelegate
{
protected:
	cocos2d::ui::EditBox* _editUserName;
	cocos2d::ui::EditBox* _editPassword;
private:
	cocos2d::Menu* createText();
	cocos2d::Sprite* createBackground();
	cocos2d::Sprite* createLoginBox();
	cocos2d::Menu* createLoginItem();
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuLoginCallback(cocos2d::Ref* pSender);
	void checkboxSelectedEvent(cocos2d::Ref* pSender);
	void initUserBox();
	void initPasswordBox();
	void initcheckBox();
	void initURLSkip();
public:
	
	static cocos2d::Scene * createScene();
	virtual bool init();
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(
		cocos2d::ui::EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
	CREATE_FUNC(LoginScene);

};
#endif // ! _LOGINSCENE_SCENE_H__
