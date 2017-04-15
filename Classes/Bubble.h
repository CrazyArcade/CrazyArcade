#pragma once

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

