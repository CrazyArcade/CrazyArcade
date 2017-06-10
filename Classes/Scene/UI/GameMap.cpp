#include "GameMap.h"
#include <json/filereadstream.h>
#include <json/document.h> 

USING_NS_CC;

bool GameMap::init()
{
    this->setName("map");
    return true;
}

void GameMap::readMapInfo(const char * mapName)
{
    using namespace rapidjson;
    
    auto path = Settings::Map::path + std::string{ mapName } + ".json";
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
    boxTop = tileMap->getLayer("BoxTop");
    boxOutOfMap = tileMap->getLayer("BoxOutOfMap");

    boxTop->setLocalZOrder(10);
    boxLayer->setLocalZOrder(5);
    boxOutOfMap->setLocalZOrder(5);

    readMapInfo(mapName);

    this->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * 0.05));
}

int GameMap::at(const cocos2d::Vec2 & tilecoord) const
{
    return mapInfo[tilecoord.y][tilecoord.x];
}

int & GameMap::at(const cocos2d::Vec2 & tilecoord)
{
    return mapInfo[tilecoord.y][tilecoord.x];
}

void GameMap::addEntity(const cocos2d::Vec2& pos, int tileType)
{
    auto coord = positionToTileCoord(pos);
    at(coord) = tileType;
}

void GameMap::removeEntity(const cocos2d::Vec2 & pos)
{
    auto coord = positionToTileCoord(pos);
    at(coord) = TILE_EMPTY;
}

void GameMap::removeBox(const cocos2d::Vec2& pos)
{
    auto coord = positionToTileCoord(pos);
    if (coord.y == 0)
    {
        boxOutOfMap->removeTileAt(coord);
    }
    else
    {
        boxLayer->removeTileAt(coord);
        boxTop->removeTileAt(coord + Vec2(0, -1));
    }
    auto tile = at(coord);
    if (tile == TILE_BOX1 || tile == TILE_BOX2)
    {
        at(coord) = TILE_EMPTY;
    }
    
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
    if (at(coord) == TILE_EMPTY || at(coord) >= 100)
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
    auto tilecoord = positionToTileCoord(pos);
    return isInMap(pos) && (at(tilecoord) == TILE_BOX1 || at(tilecoord) == TILE_BOX2);
}

bool GameMap::isInSameTile(const cocos2d::Vec2 & pos1, const cocos2d::Vec2 & pos2)
{
    return positionToTileCoord(pos1) == positionToTileCoord(pos2);
}

void GameMap::addBubble(cocos2d::Sprite * bubble)
{
    bubble->setLocalZOrder(2);
    tileMap->addChild(bubble);
    addEntity(bubble->getPosition(), TILE_BUBBLE);
}

void GameMap::removeBubble(cocos2d::Sprite * bubble)
{
    tileMap->removeChild(bubble);
    removeEntity(bubble->getPosition());
}

void GameMap::addPlayer(cocos2d::Sprite * player)
{
    player->setLocalZOrder(6);
    tileMap->addChild(player);
}

void GameMap::addProp(cocos2d::Sprite * prop, int type)
{
    prop->setLocalZOrder(1);
    tileMap->addChild(prop);
    removeBox(prop->getPosition());
    addEntity(prop->getPosition(), type);
}

void GameMap::removeProp(cocos2d::Sprite * prop)
{
    tileMap->removeChild(prop);
    removeEntity(prop->getPosition());
}

void GameMap::addSprite(cocos2d::Sprite * sprite, int zOrder)
{
    tileMap->addChild(sprite, zOrder);
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
