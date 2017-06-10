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

void ChatBox::boxInputInit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    boxInput = cocos2d::ui::TextField::create("Chat Here",
        Settings::Font::Type::base, Settings::Font::Size::chat);
    boxInput->setCursorEnabled(true);
    boxInput->setCursorChar('|');
    boxInput->setTextHorizontalAlignment(cocos2d::TextHAlignment::LEFT);

    addChild(boxInput);
}

void ChatBox::boxHistoryInit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    boxHistory = cocos2d::ui::ListView::create();
    boxHistory->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    boxHistory->setContentSize(Size(270, 380));

    boxInput->setPosition(Vec2(visibleSize.width *0.03 + boxInput->getContentSize().width / 2, visibleSize.height*0.2));
    boxHistory->setPosition(Vec2(visibleSize.width *0.03, visibleSize.height*0.2 + getContentSize().height / 2 + boxInput->getContentSize().height / 2 + 30));

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
    auto text = cocos2d::ui::Text::create("[Me]:" + txt, Settings::Font::Type::base, Settings::Font::Size::chat);
    text->ignoreContentAdaptWithSize(false);
    text->setColor(cocos2d::Color3B::GREEN);
    auto width = text->getContentSize().width;
    text->setContentSize(Size(270, 26 * (1 + (width + 60) / 270)));
    boxHistory->addChild(text, 0, tag);
    if (boxHistory->getChildrenCount() > MAX_MSG_NUM)
        boxHistory->removeChildByTag(tag - MAX_MSG_NUM);
    tag++;
    boxHistory->jumpToBottom();

    //auto ret = cocos2d::ui::RichElementText::create(1, cocos2d::Color3B::WHITE, 255, txt,
    //    Settings::Font::Type::base, Settings::Font::Size::chat);
    //boxHistory->pushBackElement(ret);
    // TODO pop judge and richtext format
}
