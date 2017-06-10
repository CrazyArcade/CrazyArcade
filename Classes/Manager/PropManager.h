#ifndef __MANAGER__PROP_H__
#define __MANAGER__PROP_H__

#include "cocos2d.h"
#include "Model/Prop.h"

class PropManager : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(PropManager);

    Prop * createProp(const std::string& id, Prop::Type type, const cocos2d::Vec2 & pos);

    //void removeProp(Prop * prop);

private:
    cocos2d::Map<std::string, Prop*> _propList;
    
    void addCustomEvent();
};
#endif
