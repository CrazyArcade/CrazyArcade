#ifndef __SCENE_UI_MAP__
#define __SCENE_UI_MAP__

#include "cocos2d.h"
#include "Settings.h"
#include "Model/Bubble.h"
#include <vector>


class GameMap : public cocos2d::Layer
{
public:
    enum
    {
        TILE_EMPTY = 0,
        TILE_BOX1,
        TILE_BOX2,
        TILE_WALL,
        TILE_BUBBLE,

    };
    virtual bool init();
    void readMapInfo(const char * mapName);
    void setMap(const char * mapName);

    // remove an entity from map
    void removeEntity(const cocos2d::Vec2& pos);
    // remove a box from map
    void removeBox(const cocos2d::Vec2& pos);

    const cocos2d::Size& getMapSize() { return tileMap->getMapSize(); }

    CREATE_FUNC(GameMap);

    // transform tilecoord to position
    cocos2d::Vec2 tileCoordToPosition(const cocos2d::Vec2& coord);
    // transform position to tilecoord
    cocos2d::Vec2 positionToTileCoord(const cocos2d::Vec2& pos);
    // get centre pos of pos
    cocos2d::Vec2 centrePos(const cocos2d::Vec2& pos);

    bool isCanAccess(const cocos2d::Vec2& pos);
    bool isInMap(const cocos2d::Vec2& pos);
    bool isBoomable(const cocos2d::Vec2& pos);

    void addBubble(Bubble * bubble);
    void removeBubble(Bubble * bubble);

    static GameMap * GameMap::getCurrentMap();

private:
    std::vector<std::vector<int> > mapInfo;
    cocos2d::TMXTiledMap * tileMap;
    // ObjectLayer that store wall, box ...
    cocos2d::TMXLayer * boxLayer;
    // ObjectLayer that store prop, bubble (player?)
    cocos2d::TMXLayer * entityLayer;

    int at(const cocos2d::Vec2& tilecoord) const;
    int & at(const cocos2d::Vec2& tilecoord);

    // add an entity to map
    void addEntity(const cocos2d::Vec2& pos, int tileType);
};

#endif