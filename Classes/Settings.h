#ifndef __SETTINGS_H__
#define __SETTINGS_H__

//#define NETWORK

#include <cstdint>
#include <set>

namespace Settings
{
    namespace Font
    {
        namespace Size
        {
            constexpr int chat = 24;
            constexpr int title  = 60;
            constexpr int label  = 40;
            constexpr int normal = 32;
            constexpr int light  = 24;
            constexpr int result = 48;
        }
        namespace Type
        {
            constexpr char title[] = "fonts/Quicksand-Bold.ttf";
            constexpr char base[] = "fonts/OpenSans-Regular.ttf";
        };
    }
    namespace Map
    {
        constexpr char path[] = "GameItem/Map/";
        static std::set<const char *> list{
            "town_10"
        };
        namespace TileSize
        {
            constexpr int height = 40;
            constexpr int width = 40;
        }
    }
    namespace Player
    {
        constexpr char path[] = "GameItem/Player/";
        constexpr char player2Animation[] = "GameItem/Player/Player2/animation.plist";
    }
    namespace Bubble
    {
        constexpr char path[] = "GameItem/Bubble/bubble.png";
        constexpr char alive[] = "GameItem/Bubble/Alive/alive.plist";
        constexpr char* explosionPath[9]{
            "GameItem/Bubble/ExplosionCenter/ExplosionCenter.plist",
            "GameItem/Bubble/ExplosionLEFT/ExplosionLEFT.plist",
            "GameItem/Bubble/ExplosionRIGHT/ExplosionRIGHT.plist",
            "GameItem/Bubble/ExplosionUP/ExplosionUP.plist",
            "GameItem/Bubble/ExplosionDOWN/ExplosionDOWN.plist",
            "GameItem/Bubble/ExplosionWaveLEFT/ExplosionWaveLEFT.plist",
            "GameItem/Bubble/ExplosionWaveRIGHT/ExplosionWaveRIGHT.plist",
            "GameItem/Bubble/ExplosionWaveUP/ExplosionWaveUP.plist",
            "GameItem/Bubble/ExplosionWaveDOWN/ExplosionWaveDOWN.plist",
        };
        constexpr char aliveAnimation[] = "GameItem/Bubble/Alive/alive.plist";
    }
    namespace Prop
    {
        constexpr char path[] = "GameItem/Prop/";
        constexpr char * name[] = {
            "speed.png",
            "bubble.png",
            "damage.png"
        };
    }
    namespace Server
    {
        constexpr char addr[] = "ws://dev.server.crazyarcade.giuem.com:4000";
    }
}
#endif
