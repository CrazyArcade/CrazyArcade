#include "GameAudio.h"

USING_NS_CC;

#define SET_KEY(name, val) UserDefault::getInstance()->setBoolForKey(name, val)

GameAudio * GameAudio::getInstance()
{
    static GameAudio INSTANCE;
    return &INSTANCE;
}

void GameAudio::playEffect(const char * name)
{
    if (isEffectOn)
    {
        audioEngine->playEffect(name);
    }
}

void GameAudio::stopEffect()
{
    audioEngine->stopAllEffects();
}

void GameAudio::setEffectOn(bool val)
{
    isEffectOn = val;
    SET_KEY("isEffectOn", val);
    if (val)
    {
        audioEngine->resumeAllEffects();
    }
    else
    {
        stopEffect();
    }
}

bool GameAudio::getEffectOn()
{
    return isEffectOn;
}

void GameAudio::playBgm(const char * name)
{
    if (currentBgm != name)
    {
        currentBgm = name;
        audioEngine->playBackgroundMusic(name, true);
    }
    if (!isBgmOn)
    {
        stopBgm();
    }
}

void GameAudio::stopBgm()
{
    audioEngine->stopBackgroundMusic();
}

void GameAudio::setBgmOn(bool val)
{
    isBgmOn = val;
    SET_KEY("isBgmOn", val);
    if (val)
    {
        audioEngine->resumeBackgroundMusic();
    }
    else
    {
        stopBgm();
    }
}

bool GameAudio::getBgmOn()
{
    return isBgmOn;
}


