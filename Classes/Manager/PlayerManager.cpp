#include "PlayerManager.h"
#include "Scene/UI/GameMap.h"
#include "api_generated.h"
USING_NS_CC;

bool PlayerManager::init()
{
    if (!Layer::init())
    {
        return false;
    }

    addCustomEvent();

    scheduleUpdate();

    return true;
}

Player* PlayerManager::createPlayer(const std::string& id, const std::string& role)
{
    auto player = Player::create(id, role);
    if (player)
    {
        this->_playerList.insert(id, player);
        return player;
    }
    return nullptr;
}

Player * PlayerManager::createLocalPlayer(const std::string & id, const std::string & role)
{
    localPlayer = createPlayer(id, role);
    if (localPlayer)
    {
        localPlayer->isLocal(true);
        this->_playerList.insert(id, localPlayer);
    }
    return localPlayer;
}

void PlayerManager::setStatus(const std::string& id, Player::Status status)
{
    auto player = this->getPlayer(id);
    if (player)
    {
        player->setStatus(status);
    }
}

Player * PlayerManager::getPlayer(const std::string& id)
{
    return _playerList.at(id);
}

Player * PlayerManager::getLocalPlayer()
{
    return localPlayer;
}

void PlayerManager::localPlayerMove()
{
    if (localPlayer->getStatus() == Player::Status::FREE && localPlayer->getDirection() != Player::Direction::NONE)
    {
        auto map = GameMap::getCurrentMap();
        if (map == nullptr) return;

        const auto speed = localPlayer->getSpeed();
        for (uint8_t i = 0; i < speed; ++i)
        {
            auto currentPos = localPlayer->getPosition();
            auto pair = getNextPos(currentPos, localPlayer->getDirection());
            auto nextPos = pair.first, logicPos1 = pair.second.first, logicPos2 = pair.second.second;
            
            if (!map->isInMap(logicPos1) || !map->isInMap(logicPos2)) break;

            if (map->isInSameTile(currentPos, logicPos1) && map->isInSameTile(currentPos, logicPos2))
            {
                localPlayer->setPosition(nextPos);
            } 
            else if (map->isCanAccess(logicPos1) && map->isCanAccess(logicPos2))
            {
                localPlayer->setPosition(nextPos);
            }
            else
            {
                break;
            }

            if (map->at(map->positionToTileCoord(nextPos)) >= 100)
            {
                auto pos = new int[2];
                pos[0] = nextPos.x, pos[1] = nextPos.y;
                getParent()->getEventDispatcher()->dispatchCustomEvent("prop_eat", pos);
                CC_SAFE_DELETE_ARRAY(pos);
            }
        }
    }
}

void PlayerManager::update(float dt)
{
    if (localPlayer) { 
        localPlayerMove();
    }
}

std::pair<cocos2d::Vec2, std::pair<cocos2d::Vec2, cocos2d::Vec2>> PlayerManager::getNextPos(const cocos2d::Vec2& pos, Player::Direction direction)
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

void PlayerManager::addCustomEvent()
{

}
