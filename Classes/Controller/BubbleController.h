#ifndef __CONTROLLER_BUBBLE_H__
#define __CONTROLLER_BUBBLE_H__

#include "cocos2d.h"
#include "Model/Bubble.h"

class BubbleController : public cocos2d::Layer
{
public:

    Bubble * createBubble(const cocos2d::Vec2 & pos, const std::string & id, uint8_t damage);
    
    /**
     * get bubble by id
     * @param string id
     * @return Bubble * bubble
     */
    Bubble * getBubble(const std::string & id);

    /**
     * boom a bubble by id
     * @param string id
     */
    void boom(const std::string & id);

    virtual bool init();
    CREATE_FUNC(BubbleController);

private:
    cocos2d::Map<std::string, Bubble*> _bubbleList;
};
#endif
