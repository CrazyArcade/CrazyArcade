#ifndef __MANAGER_BUBBLE_H__
#define __MANAGER_BUBBLE_H__

#include "cocos2d.h"
#include "Model/Bubble.h"


class BubbleManager : public cocos2d::Layer
{
public:

    Bubble * createBubble(const std::string & id, const std::string& playerID, const cocos2d::Vec2 & pos, uint8_t damage);

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
    CREATE_FUNC(BubbleManager);

private:
    cocos2d::Map<std::string, Bubble*> _bubbleList;

    void addCustomEvent();
};
#endif
