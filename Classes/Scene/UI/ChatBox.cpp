#include "Scene/UI/ChatBox.h"

USING_NS_CC;

bool ChatBox::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    boxInput = cocos2d::ui::TextField::create("Chat Here",
        Settings::Font::Type::base, Settings::Font::Size::chat);

    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(ChatBox::keyReleasedAct, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    //chat history display
    boxHistory = cocos2d::ui::RichText::create();
    boxHistory->ignoreContentAdaptWithSize(false);
    boxHistory->setContentSize(Size(250, 800));
    boxHistory->setWrapMode(cocos2d::ui::RichText::WrapMode::WRAP_PER_CHAR);

    boxInput->setPosition(Vec2(visibleSize.width *0.12, visibleSize.height*0.2));
    boxHistory->setPosition(Vec2(visibleSize.width *0.12, visibleSize.height*0.2 + getContentSize().height / 2 + boxInput->getContentSize().height / 2 + 30));

    addChild(boxInput);
    addChild(boxHistory);
    return true;
}

void ChatBox::keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
    switch (keycode) {
    case EventKeyboard::KeyCode::KEY_ENTER:
        if (isInputing) {
            static_cast<TextFieldTTF*>(boxInput->getVirtualRenderer())->detachWithIME();
            if (!boxInput->getString().empty()) {
                updateHistory(boxInput->getString());
                boxInput->setString("");
            }
            isInputing = false;
        }
        else {
            boxInput->attachWithIME();
            isInputing = true;
        }
    }
}

void ChatBox::InputStart()
{
}

void ChatBox::InputFinish()
{
}

void ChatBox::updateHistory(std::string txt)
{
    boxHistory->pushBackElement(cocos2d::ui::RichElementText::create(1, cocos2d::Color3B::WHITE, 255, txt,
        Settings::Font::Type::base, Settings::Font::Size::chat));
    // TODO pop judge and richtext format
}
