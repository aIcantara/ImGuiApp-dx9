#include "draw.h"
#include "fonts/fonts.h"

CDraw::CDraw(const std::string& title, HWND& hWnd) : windowTitle(title), hWnd(hWnd)
{
    init();
}

void CDraw::render()
{
    windowDrag();

    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::Begin(windowTitle.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
    {
        ImGui::Text("Simple Text");

        if (ImGui::Button("Exit"))
            PostMessage(hWnd, WM_CLOSE, 0, 0);
    }
    ImGui::End();
}

void CDraw::init()
{
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    io.IniFilename = nullptr;

    ImGui::GetStyle().WindowRounding = 0.0f;

    CFonts::instance().init();
}

void CDraw::windowDrag()
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