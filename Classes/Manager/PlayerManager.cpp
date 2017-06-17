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

Player* PlayerManager::createPlayer(const std::string& id, int role)
{
    auto player = Player::create(id, role);
    if (player)
    {
        player->isLocal(false);
        this->_playerList.insert(id, player);
        return player;
    }
    return nullptr;
}

Player * PlayerManager::createLocalPlayer(const std::string & id, int role)
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
    if (localPlayer->getStatus() != Player::Status::FREE) return;
    
    auto map = GameMap::getCurrentMap();
    if (map == nullptr) return;
    
    enum class MoveMode : uint8_t { Direct, Offset };
    auto mode = MoveMode::Direct;
    const auto speed = localPlayer->getSpeed();
    const float step = localPlayer->getRealSpeed() / speed;
    auto direction = localPlayer->getDirection();

    for (uint8_t i = 0; i < speed; ++i)
    {
        if (mode == MoveMode::Direct) {
            direction = localPlayer->getDirection();
        }
        if (direction == Player::Direction::NONE) continue;

        const auto currentPos = localPlayer->getPosition();

        auto pair = getNextPos(currentPos, direction, step);
        auto nextPos = pair.first, logicPos1 = pair.second.first, logicPos2 = pair.second.second;
            
        // next move is out of map
        if (!map->isInMap(logicPos1) || !map->isInMap(logicPos2)) break;
            
        // next move is in same tile
        if (map->isInSameTile(currentPos, logicPos1) && map->isInSameTile(currentPos, logicPos2))
        {
            localPlayer->setPosition(nextPos);
            continue;
        }

        bool isAccessible[] = { map->isCanAccess(logicPos1), map->isCanAccess(logicPos2) };
        
        if (!isAccessible[0] && !isAccessible[1]) break;
        
        // both check point can access
        if (isAccessible[0] && isAccessible[1])
        {
            localPlayer->setPosition(nextPos);
        }
        else // else, try offset
        {
            // offset still can access
            if (mode == MoveMode::Offset) break;

            const std::vector<std::pair<Player::Direction, Player::Direction>> offsetDirections = {
                { Player::Direction::DOWN, Player::Direction::UP },
                { Player::Direction::DOWN, Player::Direction::UP },
                { Player::Direction::RIGHT, Player::Direction::LEFT },
                { Player::Direction::RIGHT, Player::Direction::LEFT },
            };
            
            mode = MoveMode::Offset;
            direction = isAccessible[0] > isAccessible[1] ?
                offsetDirections[static_cast<int>(direction)].first :
                offsetDirections[static_cast<int>(direction)].second;
            // backtrack 
            --i;
            continue;
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

void PlayerManager::update(float dt)
{
    if (localPlayer) { 
        localPlayerMove();
    }
}

std::pair<cocos2d::Vec2, std::pair<cocos2d::Vec2, cocos2d::Vec2>> PlayerManager::getNextPos(const cocos2d::Vec2& pos, Player::Direction direction, float step)
{
    Vec2 nextPos(pos), logicPos1(pos), logicPos2(pos);

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
