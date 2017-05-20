#include "GameMap.h"

USING_NS_CC;

bool GameMap::init()
{
    this->setName("map");
    return true;
}

void GameMap::setMap(const char * mapName)
{
    CCASSERT(Settings::Map::list.find(mapName) != Settings::Map::list.cend(), "Map NOT Found");
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto path = Settings::Map::path + std::string{ mapName } +".tmx";
    tileMap = TMXTiledMap::create(path);
    addChild(tileMap, -1);

    boxLayer = tileMap->getLayer("Box");
    entityLayer = tileMap->getLayer("Entity");
    
    this->setPosition(Vec2(visibleSize.width * 0.05f, visibleSize.height * 0.05f));
}

void GameMap::addEntity(const cocos2d::Vec2& pos)
{
    //layers[GameMap::ObjectLayer]->add
    // TODO
}

void GameMap::removeEntity(const cocos2d::Vec2 & pos)
{
    entityLayer->removeTileAt(pos);
}

void GameMap::removeBox(const cocos2d::Vec2& pos)
{
    boxLayer->removeTileAt(pos);
}

cocos2d::Vec2 GameMap::tileCoordToPosition(const cocos2d::Vec2 & coord)
{
    auto mapSize = tileMap->getMapSize();
    auto tileSize = tileMap->getTileSize();

    int x = coord.x * tileSize.width + tileSize.width / 2;
    int y = (mapSize.height - coord.y) * tileSize.height - tileSize.height / 2;
    //CCLOG("pos x: %f y: %f", x, y);
    return Vec2(x, y);
}

cocos2d::Vec2 GameMap::positionToTileCoord(const cocos2d::Vec2 & pos)
{
    Size mapSize = tileMap->getMapSize();
    Size tileSize = tileMap->getTileSize();
    int x = pos.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - pos.y) / tileSize.height;
    // edge case
    x = MIN(MAX(0, x), mapSize.width - 1);
    y = MIN(MAX(0, y), mapSize.height - 1);
    //CCLOG("coord x: %f y: %f", x, y);
    return Vec2(x, y);
}

bool GameMap::isCanAccess(const cocos2d::Vec2 & pos)
{
    auto coord = positionToTileCoord(pos);
    if (isInMap(pos) && boxLayer->getTileGIDAt(coord) == 0)
    {
        return true;
    }
    return false;
}

bool GameMap::isInMap(const cocos2d::Vec2 & pos)
{
    auto mapSize = tileMap->getMapSize();
    auto tileSize = tileMap->getTileSize();
    return 0 <= pos.x && pos.x < mapSize.width * tileSize.width
        && 0 <= pos.y && pos.y < mapSize.height * tileSize.height;
}
