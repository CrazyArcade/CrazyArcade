#ifndef __SCENE_UI_MAP__
#define __SCENE_UI_MAP__

#include "cocos2d.h"
#include "Settings.h"
#include <vector>


/*
 * ZOrder:
 * 10: The top of box
 * 6 : Player
 * 5 : Box
 * 2 : Bubble
 * 1 : Prop
 * 0 : background
 **/

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

    void addBubble(cocos2d::Sprite * bubble);
    void removeBubble(cocos2d::Sprite * bubble);

    void addPlayer(cocos2d::Sprite * player);

    void addProp(cocos2d::Sprite * prop);
    void removeProp(cocos2d::Sprite * prop);

    static GameMap * GameMap::getCurrentMap();

private:
    std::vector<std::vector<int> > mapInfo;
    cocos2d::TMXTiledMap * tileMap;
    // ObjectLayer that store wall, box ...
    cocos2d::TMXLayer * boxLayer;
    // The rest of box
    cocos2d::TMXLayer * boxTop;
    // The box which is out of map 
    cocos2d::TMXLayer * boxOutOfMap;

    int at(const cocos2d::Vec2& tilecoord) const;
    int & at(const cocos2d::Vec2& tilecoord);

    // add an entity to map
    void addEntity(const cocos2d::Vec2& pos, int tileType);
};

#endif