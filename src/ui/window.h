#ifndef WINDOW_H
#define WINDOW_H

#include <imgui.h>

#include <string>
#include <d3d9.h>

class CWindow
{
public:
    CWindow(const std::string& title, int width, int height);
    ~CWindow();

private:
    HWND hWnd;
    WNDCLASSEX wc;

    LPDIRECT3D9 D3D;
    LPDIRECT3DDEVICE9 d3dDevice;
    D3DPRESENT_PARAMETERS d3dpp;

    UINT resizeWidth, resizeHeight;

    bool createDeviceD3D();
    void cleanupDeviceD3D();
    void resetDevice();

    static LRESULT WINAPI wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // WINDOW_H