#pragma once

#include "Basic/ImVec2.h"

#include "ImFont.h"

struct ImFontConfig
{
    void *FontData;                //          // TTF/OTF data
    int FontDataSize;              //          // TTF/OTF data size
    bool FontDataOwnedByAtlas;     // true     // TTF/OTF data ownership taken by the container ImFontAtlas (will delete memory itself).
    int FontNo;                    // 0        // Index of font within TTF/OTF file
    float SizePixels;              //          // Size in pixels for rasterizer (more or less maps to the resulting font height).
    int OversampleH;               // 2        // Rasterize at higher quality for sub-pixel positioning. Note the difference between 2 and 3 is minimal. You can reduce this to 1 for large glyphs save memory. Read https://github.com/nothings/stb/blob/master/tests/oversample/README.md for details.
    int OversampleV;               // 1        // Rasterize at higher quality for sub-pixel positioning. This is not really useful as we don't use sub-pixel positions on the Y axis.
    bool PixelSnapH;               // false    // Align every glyph to pixel boundary. Useful e.g. if you are merging a non-pixel aligned font with the default font. If enabled, you can set OversampleH/V to 1.
    ImVec2 GlyphExtraSpacing;      // 0, 0     // Extra spacing (in pixels) between glyphs. Only X axis is supported for now.
    ImVec2 GlyphOffset;            // 0, 0     // Offset all glyphs from this font input.
    const ImWchar *GlyphRanges;    // NULL     // THE ARRAY DATA NEEDS TO PERSIST AS LONG AS THE FONT IS ALIVE. Pointer to a user-provided list of Unicode range (2 value per range, values are inclusive, zero-terminated list).
    float GlyphMinAdvanceX;        // 0        // Minimum AdvanceX for glyphs, set Min to align font icons, set both Min/Max to enforce mono-space font
    float GlyphMaxAdvanceX;        // FLT_MAX  // Maximum AdvanceX for glyphs
    bool MergeMode;                // false    // Merge into previous ImFont, so you can combine multiple inputs font into one ImFont (e.g. ASCII font + icons + Japanese glyphs). You may want to use GlyphOffset.y when merge font of different heights.
    unsigned int FontBuilderFlags; // 0        // Settings for custom font builder. THIS IS BUILDER IMPLEMENTATION DEPENDENT. Leave as zero if unsure.
    float RasterizerMultiply;      // 1.0f     // Linearly brighten (>1.0f) or darken (<1.0f) font output. Brightening small fonts may be a good workaround to make them more readable. This is a silly thing we may remove in the future.
    float RasterizerDensity;       // 1.0f     // DPI scale for rasterization, not altering other font metrics: make it easy to swap between e.g. a 100% and a 400% fonts for a zooming display. IMPORTANT: If you increase this it is expected that you increase font scale accordingly, otherwise quality may look lowered.
    ImWchar EllipsisChar;          // -1       // Explicitly specify unicode codepoint of ellipsis character. When fonts are being merged first specified ellipsis will be used.

    // [Internal]
    char Name[40]; // Name (strictly to ease debugging)
    ImFont *DstFont;

    IMGUI_API ImFontConfig();
};