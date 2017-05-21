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
    static Player * create(const std::string& id, const std::string& role);
    
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
        uint32_t speed;
        uint32_t power;
        uint32_t bubble;
    };
    Attr attr;

    void setStatus(Status);
    const Status getStatus() const;

    void setDirection(Direction direction);
    void removeDirection(Direction direction);
    Direction getDirection();
    
    // TODO
    // void setAnimation();

private:
    Status _status;
    cocos2d::Size size;
    // record what time the direction was set
    time_t directions[4];

    bool init();
    bool initWithRole(const std::string& role);

};
#endif
