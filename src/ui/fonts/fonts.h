#ifndef FONTS_HPP
#define FONTS_HPP

#include <imgui.h>

class CFonts
{
public:
    static CFonts& instance();

    ImFont* medium = nullptr;
    void init();

private:
    CFonts() = default;
    ~CFonts() = default;
    CFonts(const CFonts&) = delete;
    CFonts& operator=(const CFonts&) = delete;

    static const ImWchar ranges[];
};

#endif // FONTS_HPP