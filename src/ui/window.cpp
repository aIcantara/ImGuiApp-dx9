#include "window.h"
#include "draw.h"

#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

CWindow::CWindow(const char* title, ImVec2 size) : resizeWidth(0), resizeHeight(0), hWnd(nullptr)
{
    wc = { sizeof(wc), CS_CLASSDC, wndProc, 0L, 0L, GetModuleHandleA(nullptr), nullptr, nullptr, nullptr, nullptr, title, nullptr };
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(
        WS_EX_LAYERED,
        wc.lpszClassName,
        title,
        WS_POPUP,
        (GetSystemMetrics(SM_CXSCREEN) / 2) - (size.x / 2),
        (GetSystemMetrics(SM_CYSCREEN) / 2) - (size.y / 2),
        size.x,
        size.y,
        nullptr,
        nullptr,
        wc.hInstance,
        this
    );

    SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    if (!createDeviceD3D())
    {
        cleanupDeviceD3D();

        UnregisterClass(wc.lpszClassName, wc.hInstance);

        return;
    }

    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    CDraw draw(title, hWnd);

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(pd3dDevice);

    bool quit = false;

    while (!quit)
    {
        MSG msg;
        
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                quit = true;
        }

        if (quit)
            break;

        if (resizeWidth != 0 && resizeHeight != 0)
        {
            d3dpp.BackBufferWidth = resizeWidth;
            d3dpp.BackBufferHeight = resizeHeight;
            resizeWidth = resizeHeight = 0;

            resetDevice();
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        {
            moving();
            
            draw.render();
        }
        ImGui::EndFrame();

        pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

        if (pd3dDevice->BeginScene() >= 0)
        {
            pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

            ImGui::Render();

            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

            pd3dDevice->EndScene();
        }

        HRESULT result = pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

        if (result == D3DERR_DEVICELOST && pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            resetDevice();
    }
}

CWindow::~CWindow()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    cleanupDeviceD3D();

    DestroyWindow(hWnd);

    UnregisterClass(wc.lpszClassName, wc.hInstance);
}

void CWindow::moving()
{
    static POINT lastCursorPos;
    static POINT lastWindowPos;

    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered() && !ImGui::IsAnyItemFocused())
    {
        POINT cursorPos;

        GetCursorPos(&cursorPos);

        if (cursorPos.x != lastCursorPos.x || cursorPos.y != lastCursorPos.y)
        {
            if (lastCursorPos.x != 0 && lastCursorPos.y != 0)
            {
                int deltaX = cursorPos.x - lastCursorPos.x;
                int deltaY = cursorPos.y - lastCursorPos.y;

                RECT windowRect;

                GetWindowRect(hWnd, &windowRect);

                SetWindowPos(hWnd, nullptr, windowRect.left + deltaX, windowRect.top + deltaY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            }

            lastCursorPos = cursorPos;
        }
    }
    else
    {
        lastCursorPos.x = 0;
        lastCursorPos.y = 0;
    }
}

bool CWindow::createDeviceD3D()
{
    if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice) < 0)
        return false;

    return true;
}

void CWindow::cleanupDeviceD3D()
{
    if (pd3dDevice)
    {
        pd3dDevice->Release();
        pd3dDevice = nullptr;
    }

    if (pD3D)
    {
        pD3D->Release();
        pD3D = nullptr;
    }
}

void CWindow::resetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();

    HRESULT hr = pd3dDevice->Reset(&d3dpp);

    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);

    ImGui_ImplDX9_CreateDeviceObjects();
}

LRESULT WINAPI CWindow::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    CWindow* window = reinterpret_cast<CWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (uMsg)
    {
    case WM_SIZE:
    {
        if (wParam == SIZE_MINIMIZED)
            return 0;

        if (window)
        {
            window->resizeWidth = (UINT)LOWORD(lParam);
            window->resizeHeight = (UINT)HIWORD(lParam);
        }

        return 0;
    }

    case WM_SYSCOMMAND:
    {
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;

        break;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);

        return 0;
    }
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}