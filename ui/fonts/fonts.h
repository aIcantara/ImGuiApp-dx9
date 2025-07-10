#ifndef FONTS_HPP
#define FONTS_HPP

#include <imgui.h>

class CFonts
{
public:
    ImFont* swiss721Bt = nullptr;
    ImFont* newscycleRegular = nullptr;

    void initialize();
private:
    static const ImWchar ranges[];
};

#endif // FONTS_HPP