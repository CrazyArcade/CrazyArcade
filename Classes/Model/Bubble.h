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

    static Bubble * create(const std::string & id, const std::string& playerID, uint8_t damage = 1);

    bool init();

    uint8_t getDamage();

    void setStatus(Status status);
private:
    uint8_t _damage;
    std::string _playerID;

    // LEFT, RIGHT, UP, DOWN
    BubbleWave* _bubbleWave[4];

    void initAnimation();
};

class BubbleWave :public Entity {
public:
    bool init();

    static BubbleWave* create(std::string Dir, Bubble* bubble);

    std::string dir;
private:
    uint8_t range[4];

    void initAnimation();
};
#endif
