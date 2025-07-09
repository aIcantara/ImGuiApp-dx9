#ifndef DRAW_H
#define DRAW_H

#include <imgui.h>

#include <windows.h>
#include <string>

class CDraw
{
public:
    CDraw(const std::string& title, HWND& hWnd);

    void render();

private:
    HWND hWnd;
    
    std::string windowTitle;

    void init();

    void windowDrag();
};

#endif // DRAW_H