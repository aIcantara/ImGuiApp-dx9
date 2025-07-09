#include "fonts.h"
#include "bytes.h"

const ImWchar CFonts::ranges[] =
{
    0x0020, 0x00FF,
    0x0400, 0x052F,
    0x2DE0, 0x2DFF,
    0xA640, 0xA69F,
    0xE000, 0xE226,
    0
};

CFonts& CFonts::instance()
{
    static CFonts instance;

    return instance;
}

void CFonts::init()
{
    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig fontConfig;

    fontConfig.PixelSnapH = false;
    fontConfig.OversampleH = 5;
    fontConfig.OversampleV = 5;
    fontConfig.RasterizerMultiply = 1.2f;
    fontConfig.GlyphRanges = ranges;

    medium = io.Fonts->AddFontFromMemoryTTF(rootUIMedium, sizeof(rootUIMedium), 18.0f, &fontConfig, ranges);
}