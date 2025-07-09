#ifndef DRAW_H
#define DRAW_H

#include "fonts/fonts.h"

#include <imgui.h>

#include <windows.h>

class CDraw
{
public:
    CDraw(const char* title, HWND& hWnd);

    void render();

private:
    CFonts fonts;

    HWND hWnd;
    
    const char* title;
};

#endif // DRAW_H