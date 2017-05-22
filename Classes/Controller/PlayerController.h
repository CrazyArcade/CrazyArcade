#ifndef __CONTROLLER_PLAYER_H__
#define __CONTROLLER_PLAYER_H__

#include "cocos2d.h"
#include "Model/Player.h"

class PlayerController : public cocos2d::Layer
{
public:
    virtual bool init();
    ~PlayerController();
    
    Player* createPlayer(const std::string& id, const std::string& role = "temp");
    Player* createLocalPlayer(const std::string& id, const std::string& role = "temp");

    void setStatus(const std::string& id, Player::Status status);
    Player* getPlayer(const std::string& id);

    void localPlayerMove();

    virtual void update(float dt);

    CREATE_FUNC(PlayerController);
private:
    cocos2d::Map<std::string, Player*> _playerList;
    Player* localPlayer;

    std::pair<cocos2d::Vec2, std::pair<cocos2d::Vec2, cocos2d::Vec2>> getNextPos(const cocos2d::Vec2& pos, Player::Direction direction);
};
#endif
