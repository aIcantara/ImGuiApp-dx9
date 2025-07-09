#include "fonts.h"
#include "converted.h"

const ImWchar CFonts::ranges[] =
{
    0x0020, 0x00FF,
    0x0400, 0x052F,
    0x2DE0, 0x2DFF,
    0xA640, 0xA69F,
    0xE000, 0xE226,
    0
};

void CFonts::initialize()
{
    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig config;

    config.PixelSnapH = false;
    config.OversampleH = 5;
    config.OversampleV = 5;
    config.RasterizerMultiply = 1.2f;
    config.GlyphRanges = ranges;

    swiss721Bt = io.Fonts->AddFontFromMemoryTTF(converted::swiss721Bt, sizeof(converted::swiss721Bt), 18.0f, &config, ranges);
    newscycleRegular = io.Fonts->AddFontFromMemoryTTF(converted::newscycleRegular, sizeof(converted::newscycleRegular), 21.0f, &config, ranges);
}