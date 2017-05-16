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
    tileMap->setAnchorPoint(Vec2(0, 0));
    tileMap->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.05f));
    objectLayer = tileMap->getLayer("Object");

    addChild(tileMap, -1);
}

void GameMap::addObject()
{
    // TODO
}

void GameMap::deleteObject(int x, int y)
{
    objectLayer->removeTileAt(Vec2(x, y));
}
