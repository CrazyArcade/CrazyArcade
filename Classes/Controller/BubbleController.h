#ifndef __CONTROLLER_BUBBLE_H__
#define __CONTROLLER_BUBBLE_H__

#include "cocos2d.h"
#include "Model/Bubble.h"

class BubbleController : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(BubbleController);
};
#endif
