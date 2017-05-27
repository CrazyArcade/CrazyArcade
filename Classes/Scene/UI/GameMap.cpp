#include "GameMap.h"

USING_NS_CC;

bool GameMap::init()
{
    this->setName("map");
    return true;
}

void GameMap::readMapInfo(const char * mapName)
{
    using namespace rapidjson;

    auto path = Settings::Map::path + std::string{ mapName } +".json";
    FILE* fp = fopen(path.c_str(), "rb");
    char readBuffer[500];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer)); 
    
    Document d;
    d.ParseStream(is);

    mapInfo.resize(13);

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 15; j++) {
            mapInfo[i].push_back(d["info"][i].GetArray()[j].GetInt());
        }
    }

    fclose(fp);
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

    readMapInfo(mapName);

    this->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * 0.05));
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
    mapInfo[pos.x][pos.y] = 0; 
    //boxLayer->removeTileAt(pos);
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
    cocos2d::Size mapSize = tileMap->getMapSize();
    cocos2d::Size tileSize = tileMap->getTileSize();
    int x = pos.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - pos.y) / tileSize.height;
    // edge case
    x = MIN(MAX(0, x), mapSize.width - 1);
    y = MIN(MAX(0, y), mapSize.height - 1);
    //CCLOG("coord x: %f y: %f", x, y);
    return Vec2(x, y);
}

cocos2d::Vec2 GameMap::centrePos(const cocos2d::Vec2 & pos)
{
    return tileCoordToPosition(positionToTileCoord(pos));
}

bool GameMap::isCanAccess(const cocos2d::Vec2 & pos)
{
    auto coord = positionToTileCoord(pos);
    // log("%f %f", coord.x, coord.y);
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

bool GameMap::isBoomable(const cocos2d::Vec2 & pos)
{
    auto Pos = positionToTileCoord(pos);
    return isInMap(pos) && (mapInfo[Pos.x][Pos.y] == 1 || mapInfo[Pos.x][Pos.y] == 2);
}

GameMap * GameMap::getCurrentMap()
{
    auto map = dynamic_cast<GameMap*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("root")->getChildByName("map"));
    if (map)
    {
        return map;
    }
    return nullptr;
}
