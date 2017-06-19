#ifndef __UTIL_GAMEAUDIO_H__
#define __UTIL_GAMEAUDIO_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class GameAudio
{
public:
    static GameAudio * getInstance();

    void playEffect(const char * name);

    void stopEffect();

    void setEffectOn(bool val);

    bool getEffectOn();

    void playBgm(const char * name);

    void stopBgm();

    void setBgmOn(bool val);

    bool getBgmOn();
private:
    GameAudio()
    {
        audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
        isEffectOn = cocos2d::UserDefault::getInstance()->getBoolForKey("isEffectOn", true);
        isBgmOn = cocos2d::UserDefault::getInstance()->getBoolForKey("isBgmOn", true);
    };

    bool isEffectOn;
    bool isBgmOn;

    std::string currentBgm;
    CocosDenshion::SimpleAudioEngine * audioEngine;
};


#endif