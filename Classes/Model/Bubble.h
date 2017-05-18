#ifndef __MODEL_BUBBLE_H__
#define __MODEL_BUBBLE_H__

#include "Entity.h"

class Bubble : public Entity
{
public:
    Bubble();
    ~Bubble();

    enum class Status : std::int8_t
    {
        ALIVE,
        BOOM
    };

    void setStatus(Status);
private:
    Status _status;
};
#endif
