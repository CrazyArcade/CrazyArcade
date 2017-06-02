#ifndef __MANAGER__PROP_H__
#define __MANAGER__PROP_H__

#include "cocos2d.h"
#include "Model/Prop.h"

class PropManager : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(PropManager);
};
#endif
