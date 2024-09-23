#pragma once

struct ImFontGlyph
{
    unsigned int Colored : 1;    // Flag to indicate glyph is colored and should generally ignore tinting (make it usable with no shift on little-endian as this is used in loops)
    unsigned int Visible : 1;    // Flag to indicate glyph has no visible pixels (e.g. space). Allow early out when rendering.
    unsigned int Codepoint : 30; // 0x0000..0x10FFFF
    float AdvanceX;              // Distance to next character (= data from font + ImFontConfig::GlyphExtraSpacing.x baked in)
    float X0, Y0, X1, Y1;        // Glyph corners
    float U0, V0, U1, V1;        // Texture coordinates
};