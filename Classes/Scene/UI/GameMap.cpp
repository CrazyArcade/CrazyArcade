#include "GameMap.h"

USING_NS_CC;

bool GameMap::init()
{
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

cocos2d::Vec2 GameMap::tileCoordToPosition(const cocos2d::Vec2 & pos)
{
    auto mapSize = tileMap->getMapSize();
    auto tileSize = tileMap->getTileSize();

    float x = pos.x * tileSize.width + tileSize.width / 2;
    float y = (mapSize.height - pos.y) * tileSize.height - tileSize.height / 2;
    CCLOG("pos x: %f y: %f", x, y);
    return Vec2(x, y);
}

cocos2d::Vec2 GameMap::postitionTotileCoord(const cocos2d::Vec2 & pos)
{
    Size mapSize = tileMap->getMapSize();
    Size tileSize = tileMap->getTileSize();
    int x = pos.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - pos.y) / tileSize.height;
    CCLOG("coord x: %f y: %f", x, y);
    return Vec2(x, y);
}
