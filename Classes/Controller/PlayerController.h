#pragma once

#include "cocos2d.h"
#include "Player.h"

class PlayerController : public cocos2d::Layer
{
public:
    virtual bool init();
    ~PlayerController();
    
    Player* createPlayer();
    void setStatus(std::string, Player::Status);
    Player* getPlayer(std::string);

    CREATE_FUNC(PlayerController);
private:
    cocos2d::Vector<Player*> _playerList;
};

