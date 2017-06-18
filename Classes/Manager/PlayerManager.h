#ifndef __MANAGER_PLAYER_H__
#define __MANAGER_PLAYER_H__

#include "cocos2d.h"
#include "Model/Player.h"

class PlayerManager : public cocos2d::Layer
{
public:
    virtual bool init();
    
    Player* createPlayer(const std::string& id, int role);
    Player* createLocalPlayer(const std::string& id, int role);

    void setStatus(const std::string& id, Player::Status status);
    Player* getPlayer(const std::string& id);
    Player* getLocalPlayer();

    void localPlayerMove();

    virtual void update(float dt);

    CREATE_FUNC(PlayerManager);
private:
    cocos2d::Map<std::string, Player*> _playerList;
    Player* localPlayer = nullptr;

    std::pair<cocos2d::Vec2, std::pair<cocos2d::Vec2, cocos2d::Vec2>> getNextPos(const cocos2d::Vec2& pos, Player::Direction direction, float step);

    void addCustomEvent();
};
#endif
