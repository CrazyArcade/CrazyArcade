#ifndef __OPERATOR_HROCKER_H__
#define __OPERATOR_HROCKER_H__

#include "cocos2d.h"
#include "Operator.h"

class Rocker : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(Rocker);

    Operator::HandleFunc handle;

    void start();

    void stop();
private:
    bool isCanMove;

    cocos2d::Vec2 leftPos;
    cocos2d::Vec2 rightPos;

    cocos2d::Sprite * rockerBGL;
    cocos2d::Sprite * rockerDotL;
    cocos2d::Sprite * rockerBGR;
    cocos2d::Sprite * rockerDotR;

    cocos2d::Sprite * createRockerBG(const cocos2d::Vec2& pos);
    cocos2d::Sprite * createRockerDot(const cocos2d::Vec2& pos, float scale = 1.0f);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    float getRad(cocos2d::Point pos1, cocos2d::Point pos2);
};


#endif // !__OPERATOR_HROCKER_H__


