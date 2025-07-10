#ifndef WINDOW_H
#define WINDOW_H

#include <imgui.h>

#include <d3d9.h>

class CWindow
{
public:
    CWindow(const char*, ImVec2 size);
    ~CWindow();

private:
    HWND hWnd;
    WNDCLASSEXW wc;

    LPDIRECT3D9 pD3D;
    LPDIRECT3DDEVICE9 pd3dDevice;
    D3DPRESENT_PARAMETERS d3dpp;

    UINT resizeWidth, resizeHeight;

    void moving();

    bool createDeviceD3D();
    void cleanupDeviceD3D();
    void resetDevice();

    static LRESULT WINAPI wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // WINDOW_H