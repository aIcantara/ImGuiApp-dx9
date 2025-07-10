#include "draw.h"

CDraw::CDraw(const char* title, HWND& hWnd) : hWnd(hWnd), title(title)
{
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    io.IniFilename = nullptr;

    ImGui::GetStyle().WindowRounding = 0.0f;

    fonts.initialize();
}

void CDraw::render()
{
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
    {
        ImGui::Text("Swiss721Bt (Default Font)");

        ImGui::PushFont(fonts.newscycleRegular);

        ImGui::Text("NewscycleRegular");
        
        ImGui::PopFont();

        if (ImGui::Button("Exit"))
            PostMessage(hWnd, WM_CLOSE, 0, 0);
    }
    ImGui::End();
}