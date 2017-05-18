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
    static Player * create(const std::string& role = "temp");
    
    enum class Status : std::int8_t
    {
        FREE,
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        FREEZE,
        DIE
    };

    void setStatus(Status);
    const Status getStatus() const;

    // TODO
    // void setAnimation();

private:
    Status _status;

    bool init();
    bool initWithRole(const std::string& role);
};
#endif
