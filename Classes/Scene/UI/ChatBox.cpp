#include "Scene/UI/ChatBox.h"

USING_NS_CC;

constexpr int MAX_MSG_NUM = 10;

bool ChatBox::init()
{
    boxInputInit();
    boxHistoryInit();

    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(ChatBox::keyReleasedAct, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(EventListenerCustom::create("update_chat", [=](EventCustom * event) {
        auto text = static_cast<char *>(event->getUserData());
        updateHistory(std::string(text));
    }), this);
    return true;
}

void ChatBox::keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
    switch (keycode) {
    case EventKeyboard::KeyCode::KEY_ENTER:
        if (isInputing) {
            static_cast<TextFieldTTF*>(boxInput->getVirtualRenderer())->detachWithIME();
            if (!boxInput->getString().empty()) {
                if (sendText) sendText(boxInput->getString());
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

void ChatBox::boxInputInit()
{
    boxInput = cocos2d::ui::TextField::create("Chat Here",
        Settings::Font::Type::base, Settings::Font::Size::chat);
    boxInput->setTextColor(Color4B(0, 0, 0, 255 * 0.9f));
    boxInput->setCursorEnabled(true);
    boxInput->setCursorChar('|');
    addChild(boxInput);
}

void ChatBox::boxHistoryInit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    boxHistory = cocos2d::ui::ListView::create();
    boxHistory->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    boxHistory->setContentSize(Size(400, 150));
    boxHistory->setBackGroundColor(Color3B(238, 238, 238));
    boxHistory->setBackGroundColorOpacity(225 * 0.8f);
    //boxInput->setPosition(Vec2(visibleSize.width *0.03 + boxInput->getContentSize().width / 2, visibleSize.height*0.2));
    //boxHistory->setPosition(Vec2(visibleSize.width *0.03, visibleSize.height*0.2 + getContentSize().height / 2 + boxInput->getContentSize().height / 2 + 30));

    addChild(boxHistory);
}

void ChatBox::InputStart()
{
}

void ChatBox::InputFinish()
{
}

void ChatBox::updateHistory(const std::string& txt)
{
    auto text = cocos2d::ui::Text::create(txt, Settings::Font::Type::base, Settings::Font::Size::chat);
    text->ignoreContentAdaptWithSize(false);
    text->setColor(cocos2d::Color3B::BLUE);
    auto width = text->getContentSize().width;
    text->setContentSize(Size(400, 26 * (1 + (width + 60) / 400)));
    boxHistory->addChild(text, 0);
    if (boxHistory->getChildrenCount() > MAX_MSG_NUM)
        boxHistory->removeItem(0);

    boxHistory->forceDoLayout();
    boxHistory->jumpToBottom();
    
    //auto ret = cocos2d::ui::RichElementText::create(1, cocos2d::Color3B::WHITE, 255, txt,
    //    Settings::Font::Type::base, Settings::Font::Size::chat);
    //boxHistory->pushBackElement(ret);
    // TODO pop judge and richtext format
}
