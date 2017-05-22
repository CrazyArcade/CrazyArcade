#ifndef __MODEL_BUBBLE_H__
#define __MODEL_BUBBLE_H__

#include "Entity.h"

class Bubble : public Entity
{
public:

    enum class Status : std::int8_t
    {
        ALIVE,
        BOOM
    };

    Bubble * createAt(const std::string & id, const cocos2d::Vec2 & pos, uint8_t damage = 1);

    bool init();

    void setStatus(Status);
private:
    Status _status;
    uint8_t _damage;
};
#endif
