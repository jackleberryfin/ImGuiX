#pragma once

#include "Basic/ImVec2.h"

#include "ImFont.h"

// See ImFontAtlas::AddCustomRectXXX functions.
struct ImFontAtlasCustomRect
{
    unsigned short Width, Height; // Input    // Desired rectangle dimension
    unsigned short X, Y;          // Output   // Packed position in Atlas
    unsigned int GlyphID;         // Input    // For custom font glyphs only (ID < 0x110000)
    float GlyphAdvanceX;          // Input    // For custom font glyphs only: glyph xadvance
    ImVec2 GlyphOffset;           // Input    // For custom font glyphs only: glyph display offset
    ImFont *Font;                 // Input    // For custom font glyphs only: target font
    ImFontAtlasCustomRect()
    {
        Width = Height = 0;
        X = Y = 0xFFFF;
        GlyphID = 0;
        GlyphAdvanceX = 0.0f;
        GlyphOffset = ImVec2(0, 0);
        Font = NULL;
    }
    bool IsPacked() const { return X != 0xFFFF; }
};