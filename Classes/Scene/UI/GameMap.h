#ifndef __SCENE_UI_MAP__
#define __SCENE_UI_MAP__

#include "cocos2d.h"
#include "Settings.h"

class GameMap : public cocos2d::Layer
{
public:
    virtual bool init();
    void setMap(const char * mapName);
    // add an entity to map
    void addEntity(const cocos2d::Vec2& pos);
    // remove an entity from map
    void removeEntity(const cocos2d::Vec2& pos);
    // remove a box from map
    void removeBox(const cocos2d::Vec2& pos);
    CREATE_FUNC(GameMap);

    // transform titecoord to position
    cocos2d::Vec2 tileCoordToPosition(const cocos2d::Vec2& coord);
    // transform position to titecoord
    cocos2d::Vec2 positionToTileCoord(const cocos2d::Vec2& pos);
    // get centre pos of pos
    cocos2d::Vec2 centrePos(const cocos2d::Vec2& pos);

    bool isCanAccess(const cocos2d::Vec2& pos);
    bool isInMap(const cocos2d::Vec2& pos);

private:
    cocos2d::TMXTiledMap * tileMap;
    // ObjectLayer that store wall, box ...
    cocos2d::TMXLayer * boxLayer;
    // ObjectLayer that store prop, bubble (player?)
    cocos2d::TMXLayer * entityLayer;
};

#endif