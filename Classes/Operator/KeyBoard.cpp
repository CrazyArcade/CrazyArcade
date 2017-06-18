#include "KeyBoard.h"

USING_NS_CC;


bool KeyBoard::init()
{
    return true;
}

void KeyBoard::start()
{
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(KeyBoard::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(KeyBoard::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void KeyBoard::stop()
{
    _eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
}

void KeyBoard::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
        auto opcode = static_cast<Operator::OpCode>(static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_LEFT_ARROW));
        handle(opcode, Operator::OpType::PRESS);
        break;
    }
    case EventKeyboard::KeyCode::KEY_SPACE: {
        handle(Operator::OpCode::SPACE, Operator::OpType::PRESS);
    }
    default: break;
    }
}

void KeyBoard::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
        auto opcode = static_cast<Operator::OpCode>(static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_LEFT_ARROW));
        handle(opcode, Operator::OpType::RELEASE);
        break;
    }
    case EventKeyboard::KeyCode::KEY_SPACE: {
        handle(Operator::OpCode::SPACE, Operator::OpType::RELEASE);
    }
    default: break;
    }
}
