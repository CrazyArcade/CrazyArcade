#ifndef __MODEL_PLAYER_H__
#define __MODEL_PLAYER_H__

#include "cocos2d.h"
#include "Entity.h"

class Player : public Entity
{
public:
    /** 
     * create Player with role 
     * @return Player Object
     */
    static Player * create(const std::string& id, int role);
    
    enum class Status : std::int8_t
    {
        FREE,
        FREEZE,
        DIE
    };

    enum class Direction : std::int8_t
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

    struct Attr
    {
        uint8_t speed;
        uint8_t damage;
        uint8_t maxBubble;
        uint8_t currentBubble;
    };

    uint8_t getSpeed();
    void setSpeed(uint8_t speed);

    uint8_t getDamage();
    void setDamage(uint8_t damage);

    uint8_t getBubble();
    void setMaxBubble(uint8_t maxBubble, uint8_t currentBubble);
    bool isCanSetBubble();
    void setBubble();
    void boomBubble();

    void setStatus(Status);
    Status getStatus();

    void isLocal(bool a);
    bool isLocal();

    void setDirectionByKey(Direction direction);
    void removeDirectionByKey(Direction direction);
    void updateDirection();
    void setDirection(Direction direction);
    Direction getDirection();
    

private:
    Status _status;
    Attr attr;
    cocos2d::Size size;
    // record what time the direction was set
    time_t directions[4];
    Direction direction;
    std::string roleName;

    bool _isLocal;

    bool init();
    bool initWithRole(int Role);
    bool initAnimation();

};
#endif
