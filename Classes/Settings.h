#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <cstdint>
#include <set>

namespace Settings
{
    namespace Font
    {
        namespace Size
        {
            constexpr int title  = 60;
            constexpr int label  = 40;
            constexpr int normal = 32;
            constexpr int light  = 24;
        }
        namespace Type
        {
            constexpr char title[] = "fonts/Quicksand-Bold.ttf";
            constexpr char base[] = "fonts/OpenSans-Regular.ttf";
        };
    }
    namespace Map
    {
        constexpr char path[] = "map/";
        static std::set<const char *> list{
            "town_10"
        };
    }
    namespace Sever
    {
        constexpr char addr[] = "ws://dev.server.crazyarcade:4000";
    }
}
#endif
