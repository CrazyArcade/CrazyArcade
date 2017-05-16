#ifndef __SETTING_H__
#define __SETTING_H__

#include <cstdint>

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
            constexpr char * title = "fonts/Quicksand-Bold.ttf";
            constexpr char * base  = "fonts/OpenSans-Regular.ttf";
        };
    }
}
#endif
