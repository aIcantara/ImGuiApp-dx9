#include "fonts.h"
#include "converted.h"

void fonts::initialize()
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