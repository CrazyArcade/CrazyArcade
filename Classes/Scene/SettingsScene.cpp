#include "SettingsScene.h"
#include "Settings.h"
#include "Util/GameAudio.h"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SettingsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool SettingsScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto middleX = visibleSize.width / 2;

    Sprite * bg = Sprite::create("SettingsScene/background1.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(bg, -1);

    auto musicLabel = createLabel("Background Music");
    auto musicCheckBox = createCheckBox([=](Ref*, ui::CheckBox::EventType type) {
        GameAudio::getInstance()->setBgmOn(type == ui::CheckBox::EventType::SELECTED);
    });
    musicLabel->setPosition(Vec2(middleX, visibleSize.height * 0.7f));
    musicCheckBox->setPosition(Vec2(middleX + 20, visibleSize.height * 0.7f));
    musicCheckBox->setSelected(GameAudio::getInstance()->getBgmOn());
    addChild(musicLabel);
    addChild(musicCheckBox);

    auto effectLabel = createLabel("Effect Music");
    auto effectCheckBox = createCheckBox([=](Ref*, ui::CheckBox::EventType type)
    {
        GameAudio::getInstance()->setEffectOn(type == ui::CheckBox::EventType::SELECTED);
    });
    effectLabel->setPosition(Vec2(middleX, visibleSize.height * 0.6f));
    effectCheckBox->setPosition(Vec2(middleX + 20, visibleSize.height * 0.6f));
    effectCheckBox->setSelected(GameAudio::getInstance()->getBgmOn());
    addChild(effectLabel);
    addChild(effectCheckBox);

    addChild(createText());

    auto keyEventListener = EventListenerKeyboard::create();
    keyEventListener->onKeyReleased = [](EventKeyboard::KeyCode code, Event* event)
    {
        if (code == EventKeyboard::KeyCode::KEY_ESCAPE)
        {
            Director::getInstance()->popScene();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyEventListener, this);

    return true;
}

cocos2d::Menu* SettingsScene::createText()
{
    const auto buttons = Menu::create();

    const auto backButton = MenuItemLabel::create(
        Label::createWithTTF("OK", Settings::Font::Type::title, Settings::Font::Size::normal),
        CC_CALLBACK_1(SettingsScene::menuOkCallback, this));

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    backButton->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.2f);
    static_cast<Label*>(backButton->getLabel())->enableGlow(Color4B(0, 0, 0, 255 * 0.6f));

    buttons->addChild(backButton, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

void SettingsScene::onEnter()
{
    Layer::onEnter();
    GameAudio::getInstance()->playBgm("Sound/mainScene.mp3");
}

void SettingsScene::menuOkCallback(cocos2d::Ref * pSender)
{
    Director::getInstance()->popScene();
}

cocos2d::ui::CheckBox * SettingsScene::createCheckBox(std::function<void(Ref*, ui::CheckBox::EventType)> callback)
{
    auto checkBox = ui::CheckBox::create("Scene/checkbox_normal.png", "Scene/checkbox_active.png");
    checkBox->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    checkBox->addEventListener(callback);
    return checkBox;
}

cocos2d::Label * SettingsScene::createLabel(const char * text)
{
    auto label = Label::createWithTTF(text, Settings::Font::Type::title, Settings::Font::Size::normal);
    label->enableShadow(Color4B(0, 0, 0, 255 * 0.15f), Size(2, -2), 2);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    return label;
}
