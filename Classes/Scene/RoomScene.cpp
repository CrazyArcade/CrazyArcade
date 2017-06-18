#include "RoomScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/GameScene.h"
#include "Scene/StartScene.h"
#include "Settings.h"

USING_NS_CC;

/*to do */
/*the back button*/
/*the case of the players*/

Scene* RoomScene::createScene()
{
    //scene is an auto release object 
    auto scene = Scene::create();

    //layer is an auto release object
    auto layer = RoomScene::create();

    //add layer as a child to scene
    scene->addChild(layer);

    //return the scene
    return scene;
}

bool RoomScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // room controller
    roomController = RoomController::create();

    // ready button callback
    readyButtonCallBack = CC_CALLBACK_1(RoomController::onUserChangeStats, roomController);
    roleChangeCallback = CC_CALLBACK_1(RoomController::onUserChangeRole, roomController);

    createUI();

    addChild(roomController, -1);
    return true;
}

void RoomScene::createUI()
{
    createBackground();
    createTitle();
    initUserBox();
    initRoleBox();
    initMouseListener();
    createBackButton();
    createReadyButton();
}

void RoomScene::onEnter()
{
    Layer::onEnter();
    readyButton->setTitleText("Ready");
    isReady = false;
}

void RoomScene::createReadyButton()
{
    auto getShowText = [](bool isReady)
    {
        return isReady ? "Cancel" : "Ready";
    };
    readyButton = ui::Button::create("RoomScene/button_normal.png", "RoomScene/button_selected.png");
    readyButton->setTitleText(getShowText(isReady));
    readyButton->setTitleFontSize(Settings::Font::Size::normal);

    readyButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            auto button = static_cast<ui::Button*>(sender);
            isReady = !isReady;
            button->setTitleText(getShowText(isReady));
            if (readyButtonCallBack) readyButtonCallBack(isReady);
        }
    });

    readyButton->setPosition(Vec2(visibleSize.width*0.4f + readyButton->getContentSize().width, visibleSize.height*0.1f));
    this->addChild(readyButton);
}

void RoomScene::createTitle()
{
    //the title
    auto label = Label::createWithTTF("ROOM", Settings::Font::Type::title, Settings::Font::Size::label);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
    label->enableGlow(Color4B::BLUE);
    this->addChild(label, 1);
}

void RoomScene::initUserBox()
{
    for (int i = 0; i < 4; i++) {
        auto _userBox = UserBox::create();
        _userBox->setPosition(Vec2(_userBox->getContentSize().width * (i + 1) * 1.25 - _userBox->getContentSize().width * 0.5f,
            visibleSize.height*0.68f));
        addChild(_userBox);
        roomController->userBoxes.pushBack(_userBox);
    }
}

void RoomScene::initRoleBox()
{
    for (int i = 0; i < 2; ++i)
    {
        auto roleBox = RoleBox::create(static_cast<RoleBox::roleChoice>(i));
        roleBox->setPosition(cocos2d::Vec2(
            visibleSize.width*0.7 + (2 * i - 1)*roleBox->getContentSize().width*0.7,
            visibleSize.height*0.6));
        addChild(roleBox);
        roleBoxes.pushBack(roleBox);
    }
    // default role
    roleBoxes.at(0)->setChosen(true);
}

void RoomScene::initMouseListener()
{
    auto mouseListener = cocos2d::EventListenerMouse::create();

    mouseListener->onMouseUp = [=](Event* event)
    {
        EventMouse* e = (EventMouse*)event;
        auto touch = e->getLocation();
        touch = Vec2(touch.x, touch.y + 147);       // possible upstream bug

        for (auto prev : roleBoxes)
        {
            auto range = prev->getBoundingBox();

            if (range.containsPoint(touch))
            {
                roleChangeCallback(prev->getRole());

                for (auto val : roleBoxes)
                    val->setChosen(false);

                prev->setChosen(true);
                break;
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void RoomScene::createBackButton()
{
    const auto buttons = Menu::create();

    const auto backButton = MenuItemLabel::create(
        Label::createWithTTF("Back", Settings::Font::Type::base, Settings::Font::Size::label),
        [](Ref * ref) { 
        Client::getInstance()->close();
        Director::getInstance()->popScene(); 
    });

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    backButton->setPosition(backButton->getContentSize().width / 2 + 30, baseY + 30);

    buttons->addChild(backButton, 1);

    buttons->setPosition(0, 0);
    this->addChild(buttons);
}

void RoomScene::createBackground()
{
    auto bg = Sprite::create("RoomScene/bg.png");
    bg->setScale(1.6f);
    bg->setLocalZOrder(-1);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(bg);
}