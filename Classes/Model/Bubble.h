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

    static Bubble * create(const std::string & id, uint8_t damage = 1);

    bool init();

    uint8_t getDamage();

    void setStatus(Status status);
private:
    // Status _status;
    uint8_t _damage;
};
#endif
