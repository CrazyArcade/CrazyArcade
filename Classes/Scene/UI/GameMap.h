#ifndef __SCENE_UI_MAP__
#define __SCENE_UI_MAP__

#include "cocos2d.h"
#include "Settings.h"

class GameMap : public cocos2d::Layer
{
public:
    virtual bool init();
    void setMap(const char * mapName);
    void addObject();
    void deleteObject(int x, int y);
    CREATE_FUNC(GameMap);

private:
    cocos2d::TMXTiledMap * tileMap;
    cocos2d::TMXLayer * objectLayer;
};

#endif