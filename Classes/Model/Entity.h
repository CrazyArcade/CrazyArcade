#ifndef __MODEL_ENTITY_H__
#define __MODEL_ENTITY_H__

#include "cocos2d.h"
#include <string>

class Entity : public cocos2d::Sprite
{
public:
    Entity() = default;
    ~Entity() = default;

    void setID(std::string);
    std::string getID() const;

    // virtual void setStatus();

protected:
    std::string _id;
    
};
#endif
