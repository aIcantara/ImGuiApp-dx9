#ifndef FONTS_HPP
#define FONTS_HPP

#include <imgui.h>

class CFonts
{
public:
    ImFont* newscycleRegular = nullptr;
    ImFont* swiss721Bt = nullptr;

    void initialize();

private:
    static const ImWchar ranges[];
};

#endif // FONTS_HPP