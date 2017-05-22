#include "PlayerController.h"
#include "Scene/UI/GameMap.h"

USING_NS_CC;

bool PlayerController::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto listener = EventListenerCustom::create("on_local_player_move", [=](EventCustom* event)
    {
        char* buf = static_cast<char*>(event->getUserData());
        int mode;
        int direction;
        sscanf(buf, "%d %d", &mode, &direction);
        if (mode)
        {
            localPlayer->setDirection(static_cast<Player::Direction>(direction));
        }
        else
        {
            localPlayer->removeDirection(static_cast<Player::Direction>(direction));
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    scheduleUpdate();
    return true;
}

PlayerController::~PlayerController()
{

}

Player* PlayerController::createPlayer(const std::string& id, const std::string& role)
{
    auto player = Player::create(id, role);

    this->_playerList.pushBack(player);
    return player;
}

Player * PlayerController::createLocalPlayer(const std::string & id, const std::string & role)
{
    localPlayer = createPlayer(id, role);
    return localPlayer;
}

void PlayerController::setStatus(std::string id, Player::Status status)
{
    auto player = this->getPlayer(id);
    if (player)
    {
        player->setStatus(status);
    }
}

Player * PlayerController::getPlayer(std::string id)
{
    for (auto player : this->_playerList)
    {
        if (player->getID() == id)
        {
            return player;
        }
    }
    return nullptr;
}

void PlayerController::localPlayerMove()
{
    if (localPlayer->getStatus() == Player::Status::FREE && localPlayer->getDirection() != Player::Direction::NONE)
    {
        auto map = dynamic_cast<GameMap*>(Director::getInstance()->getRunningScene()->getChildByName("root")->getChildByName("map"));
        if (map == nullptr) return;

        const auto speed = localPlayer->getSpeed();
        for (uint8_t i = 0; i < speed; ++i)
        {
            auto pair = getNextPos(localPlayer->getPosition(), localPlayer->getDirection());
            auto nextPos = pair.first, logicPos1 = pair.second.first, logicPos2 = pair.second.second;

            if (map->isCanAccess(logicPos1) && map->isCanAccess(logicPos2))
            {
                localPlayer->setPosition(nextPos);
            }
        }
    }
}

void PlayerController::update(float dt)
{
    if (localPlayer) localPlayerMove();
}

std::pair<cocos2d::Vec2, std::pair<cocos2d::Vec2, cocos2d::Vec2>> PlayerController::getNextPos(const cocos2d::Vec2& pos, Player::Direction direction)
{
    int step = 1;

    Vec2 nextPos(pos.x, pos.y);
    Vec2 logicPos1(pos.x, pos.y), logicPos2(pos.x, pos.y);

    switch (direction)
    {
    case Player::Direction::LEFT:
        nextPos.x -= step;
        logicPos1.x = logicPos2.x = nextPos.x - 20;
        logicPos1.y -= 16;
        logicPos2.y += 16;
        break;
    case Player::Direction::RIGHT:
        nextPos.x += step;
        logicPos1.x = logicPos2.x = nextPos.x + 20;
        logicPos1.y -= 16;
        logicPos2.y += 16;
        break;
    case Player::Direction::UP:
        nextPos.y += step;
        logicPos1.y = logicPos2.y = nextPos.y + 20;
        logicPos1.x += 16;
        logicPos2.x -= 16;
        break;
    case Player::Direction::DOWN:
        nextPos.y -= step;
        logicPos1.y = logicPos2.y = nextPos.y - 20;
        logicPos1.x += 16;
        logicPos2.x -= 16;
        break;
    default:
        break;
    }
    return std::make_pair(nextPos, std::make_pair(logicPos1, logicPos2));
}
