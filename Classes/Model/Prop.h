#ifndef __MODEL_PROP_H__
#define __MODEL_PROP_H__

#include "cocos2d.h"
#include "Entity.h"

class Prop : public Entity
{
public:
    enum class Type
    {
        EMPTY = 0,
        SPEED = 100,
        BUBBLE,
        DAMAGE
    };
    
    static Prop * create(const std::string& id, Type type);

    bool init(Type type);

    int getType();

private:
    Type type;
};
#endif
