#ifndef __CONTROLLER_PROP_H__
#define __CONTROLLER_PROP_H__

#include "cocos2d.h"
#include "Model/Prop.h"

class PropController : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(PropController);
};
#endif
