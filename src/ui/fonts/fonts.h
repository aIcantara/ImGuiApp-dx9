#ifndef FONTS_HPP
#define FONTS_HPP

#include <imgui.h>

namespace fonts
{
    static ImFont* newscycleRegular;
    static ImFont* swiss721Bt;

    const ImWchar ranges[] =
    {
        0x0020, 0x00FF,
        0x0400, 0x052F,
        0x2DE0, 0x2DFF,
        0xA640, 0xA69F,
        0xE000, 0xE226,
        0
    };

    void initialize();
} // namespace fonts

#endif // FONTS_HPP