#include "BubbleManager.h"
#include "Scene/UI/GameMap.h"
#include "api_generated.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Bubble * BubbleManager::createBubble(const std::string & id, const std::string& playerID, const cocos2d::Vec2 & pos, uint8_t damage)
{
    auto bubble = Bubble::create(id, playerID, damage);
    if (bubble)
    {
        bubble->setPosition(pos);
        _bubbleList.insert(id, bubble);

        return bubble;
    }
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/bubbleSet.mp3", false);
    return nullptr;
}

Bubble * BubbleManager::getBubble(const std::string & id)
{
    return _bubbleList.at(id);
}

void BubbleManager::boom(const std::string & id)
{
    auto map = GameMap::getCurrentMap();
    if (map == nullptr) return;

    auto bubble = getBubble(id);
    auto damage = bubble->getDamage();
    auto pos = map->positionToTileCoord(bubble->getPosition());
    const std::vector<Vec2> dirs = {
        Vec2(-1, 0), // left
        Vec2(1, 0), // right
        Vec2(0, -1), // top
        Vec2(0, 1), // bottom
    };
    bool isEnd[4] = { false, false, false, false };

    auto removeBox = [map](const Vec2& coord, bool& isEnd, BubbleWave::Direction direction, bool isTerminal)
    {
        BubbleWave* bubbleWave = nullptr;
        auto pos = map->tileCoordToPosition(coord);
        if (!map->isInMap(pos))
        {
            isEnd = true;
            return;
        }
        auto tileType = map->at(coord);
        if (tileType == map->TILE_EMPTY || tileType == map->TILE_BUBBLE || tileType >= 100)
        {
            if ((direction == BubbleWave::Direction::LEFT && coord.x == 0) ||
                (direction == BubbleWave::Direction::RIGHT && coord.x == map->getMapSize().width - 1) ||
                (direction == BubbleWave::Direction::UP && coord.y == 0) ||
                (direction == BubbleWave::Direction::DOWN && coord.y == map->getMapSize().height - 1) || isTerminal)
            {
                bubbleWave = BubbleWave::create(BubbleWave::PosInWave::TERMINAL, direction);
                isEnd = true;
            }
            else
            {
                bubbleWave = BubbleWave::create(BubbleWave::PosInWave::MIDDLE, direction);
            }
            if (tileType >= 100)
            {
                // TODO remove prop
            }
        }
        else if (tileType == map->TILE_BOX1 || tileType == map->TILE_BOX2)
        {
            map->removeBox(pos);
            bubbleWave = BubbleWave::create(BubbleWave::PosInWave::TERMINAL, direction);
            isEnd = true;
        }
        else
        {
            isEnd = true;
        }
        if (bubbleWave) {
            bubbleWave->setPosition(pos);
            map->addSprite(bubbleWave, 3);
        }
    };
    
    auto bubbleWaveCenter = BubbleWave::create(BubbleWave::PosInWave::CENTER, BubbleWave::Direction::NONE);
    if (bubbleWaveCenter)
    {
        bubbleWaveCenter->setPosition(bubble->getPosition());
        map->addSprite(bubbleWaveCenter, 3);
    }

    for (uint8_t i = 1; i <= damage; i++)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (isEnd[j]) continue;
            auto nextPos = pos + dirs[j] * i;
            removeBox(nextPos, isEnd[j], static_cast<BubbleWave::Direction>(j), i == damage);
        }
    }
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/bubbleBoom.mp3", false, 1.0f, 1.0f, 1.0f);
    // remove
    map->removeBubble(bubble);
    _bubbleList.erase(id);
}

bool BubbleManager::init()
{
    if (!Layer::init())
    {
        return false;
    }

    return true;
}

void BubbleManager::addCustomEvent()
{
    auto dispatcher = this->getEventDispatcher();
}
