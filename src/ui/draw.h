#ifndef DRAW_H
#define DRAW_H

#include <imgui.h>

#include <windows.h>

class CDraw
{
public:
    CDraw(const char* title, HWND& hWnd);

    void render();

private:
    HWND hWnd;
    
    const char* title;
};

#endif // DRAW_H