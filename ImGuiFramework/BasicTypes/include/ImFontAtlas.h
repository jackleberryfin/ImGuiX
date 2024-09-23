#pragma once

#include "ImTypeDefs.h"
#include "ImFont.h"
#include "ImFontConfig.h"

struct ImFontAtlas
{
    IMGUI_API ImFontAtlas();
    IMGUI_API ~ImFontAtlas();
    IMGUI_API ImFont *AddFont(const ImFontConfig *font_cfg);
    IMGUI_API ImFont *AddFontDefault(const ImFontConfig *font_cfg = NULL);
    IMGUI_API ImFont *AddFontFromFileTTF(const char *filename, float size_pixels, const ImFontConfig *font_cfg = NULL, const ImWchar *glyph_ranges = NULL);
    IMGUI_API ImFont *AddFontFromMemoryTTF(void *font_data, int font_data_size, float size_pixels, const ImFontConfig *font_cfg = NULL, const ImWchar *glyph_ranges = NULL);                                       // Note: Transfer ownership of 'ttf_data' to ImFontAtlas! Will be deleted after destruction of the atlas. Set font_cfg->FontDataOwnedByAtlas=false to keep ownership of your data and it won't be freed.
    IMGUI_API ImFont *AddFontFromMemoryCompressedTTF(const void *compressed_font_data, int compressed_font_data_size, float size_pixels, const ImFontConfig *font_cfg = NULL, const ImWchar *glyph_ranges = NULL); // 'compressed_font_data' still owned by caller. Compress with binary_to_compressed_c.cpp.
    IMGUI_API ImFont *AddFontFromMemoryCompressedBase85TTF(const char *compressed_font_data_base85, float size_pixels, const ImFontConfig *font_cfg = NULL, const ImWchar *glyph_ranges = NULL);                   // 'compressed_font_data_base85' still owned by caller. Compress with binary_to_compressed_c.cpp with -base85 parameter.
    IMGUI_API void ClearInputData();                                                                                                                                                                               // Clear input data (all ImFontConfig structures including sizes, TTF data, glyph ranges, etc.) = all the data used to build the texture and fonts.
    IMGUI_API void ClearTexData();                                                                                                                                                                                 // Clear output texture data (CPU side). Saves RAM once the texture has been copied to graphics memory.
    IMGUI_API void ClearFonts();                                                                                                                                                                                   // Clear output font data (glyphs storage, UV coordinates).
    IMGUI_API void Clear();                                                                                                                                                                                        // Clear all input and output.

    // Build atlas, retrieve pixel data.
    // User is in charge of copying the pixels into graphics memory (e.g. create a texture with your engine). Then store your texture handle with SetTexID().
    // The pitch is always = Width * BytesPerPixels (1 or 4)
    // Building in RGBA32 format is provided for convenience and compatibility, but note that unless you manually manipulate or copy color data into
    // the texture (e.g. when using the AddCustomRect*** api), then the RGB pixels emitted will always be white (~75% of memory/bandwidth waste.
    IMGUI_API bool Build();                                                                                                          // Build pixels data. This is called automatically for you by the GetTexData*** functions.
    IMGUI_API void GetTexDataAsAlpha8(unsigned char **out_pixels, int *out_width, int *out_height, int *out_bytes_per_pixel = NULL); // 1 byte per-pixel
    IMGUI_API void GetTexDataAsRGBA32(unsigned char **out_pixels, int *out_width, int *out_height, int *out_bytes_per_pixel = NULL); // 4 bytes-per-pixel
    bool IsBuilt() const { return Fonts.Size > 0 && TexReady; }                                                                      // Bit ambiguous: used to detect when user didn't build texture but effectively we should check TexID != 0 except that would be backend dependent...
    void SetTexID(ImTextureID id) { TexID = id; }

    //-------------------------------------------
    // Glyph Ranges
    //-------------------------------------------

    // Helpers to retrieve list of common Unicode ranges (2 value per range, values are inclusive, zero-terminated list)
    // NB: Make sure that your string are UTF-8 and NOT in your local code page.
    // Read https://github.com/ocornut/imgui/blob/master/docs/FONTS.md/#about-utf-8-encoding for details.
    // NB: Consider using ImFontGlyphRangesBuilder to build glyph ranges from textual data.
    IMGUI_API const ImWchar *GetGlyphRangesDefault();                 // Basic Latin, Extended Latin
    IMGUI_API const ImWchar *GetGlyphRangesGreek();                   // Default + Greek and Coptic
    IMGUI_API const ImWchar *GetGlyphRangesKorean();                  // Default + Korean characters
    IMGUI_API const ImWchar *GetGlyphRangesJapanese();                // Default + Hiragana, Katakana, Half-Width, Selection of 2999 Ideographs
    IMGUI_API const ImWchar *GetGlyphRangesChineseFull();             // Default + Half-Width + Japanese Hiragana/Katakana + full set of about 21000 CJK Unified Ideographs
    IMGUI_API const ImWchar *GetGlyphRangesChineseSimplifiedCommon(); // Default + Half-Width + Japanese Hiragana/Katakana + set of 2500 CJK Unified Ideographs for common simplified Chinese
    IMGUI_API const ImWchar *GetGlyphRangesCyrillic();                // Default + about 400 Cyrillic characters
    IMGUI_API const ImWchar *GetGlyphRangesThai();                    // Default + Thai characters
    IMGUI_API const ImWchar *GetGlyphRangesVietnamese();              // Default + Vietnamese characters

    //-------------------------------------------
    // [BETA] Custom Rectangles/Glyphs API
    //-------------------------------------------

    // You can request arbitrary rectangles to be packed into the atlas, for your own purposes.
    // - After calling Build(), you can query the rectangle position and render your pixels.
    // - If you render colored output, set 'atlas->TexPixelsUseColors = true' as this may help some backends decide of preferred texture format.
    // - You can also request your rectangles to be mapped as font glyph (given a font + Unicode point),
    //   so you can render e.g. custom colorful icons and use them as regular glyphs.
    // - Read docs/FONTS.md for more details about using colorful icons.
    // - Note: this API may be redesigned later in order to support multi-monitor varying DPI settings.
    IMGUI_API int AddCustomRectRegular(int width, int height);
    IMGUI_API int AddCustomRectFontGlyph(ImFont *font, ImWchar id, int width, int height, float advance_x, const ImVec2 &offset = ImVec2(0, 0));
    ImFontAtlasCustomRect *GetCustomRectByIndex(int index)
    {
        IM_ASSERT(index >= 0);
        return &CustomRects[index];
    }

    // [Internal]
    IMGUI_API void CalcCustomRectUV(const ImFontAtlasCustomRect *rect, ImVec2 *out_uv_min, ImVec2 *out_uv_max) const;
    IMGUI_API bool GetMouseCursorTexData(ImGuiMouseCursor cursor, ImVec2 *out_offset, ImVec2 *out_size, ImVec2 out_uv_border[2], ImVec2 out_uv_fill[2]);

    //-------------------------------------------
    // Members
    //-------------------------------------------

    ImFontAtlasFlags Flags; // Build flags (see ImFontAtlasFlags_)
    ImTextureID TexID;      // User data to refer to the texture once it has been uploaded to user's graphic systems. It is passed back to you during rendering via the ImDrawCmd structure.
    int TexDesiredWidth;    // Texture width desired by user before Build(). Must be a power-of-two. If have many glyphs your graphics API have texture size restrictions you may want to increase texture width to decrease height.
    int TexGlyphPadding;    // Padding between glyphs within texture in pixels. Defaults to 1. If your rendering method doesn't rely on bilinear filtering you may set this to 0 (will also need to set AntiAliasedLinesUseTex = false).
    bool Locked;            // Marked as Locked by ImGui::NewFrame() so attempt to modify the atlas will assert.
    void *UserData;         // Store your own atlas related user-data (if e.g. you have multiple font atlas).

    // [Internal]
    // NB: Access texture data via GetTexData*() calls! Which will setup a default font for you.
    bool TexReady;                                          // Set when texture was built matching current font input
    bool TexPixelsUseColors;                                // Tell whether our texture data is known to use colors (rather than just alpha channel), in order to help backend select a format.
    unsigned char *TexPixelsAlpha8;                         // 1 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight
    unsigned int *TexPixelsRGBA32;                          // 4 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight * 4
    int TexWidth;                                           // Texture width calculated during Build().
    int TexHeight;                                          // Texture height calculated during Build().
    ImVec2 TexUvScale;                                      // = (1.0f/TexWidth, 1.0f/TexHeight)
    ImVec2 TexUvWhitePixel;                                 // Texture coordinates to a white pixel
    ImVector<ImFont *> Fonts;                               // Hold all the fonts returned by AddFont*. Fonts[0] is the default font upon calling ImGui::NewFrame(), use ImGui::PushFont()/PopFont() to change the current font.
    ImVector<ImFontAtlasCustomRect> CustomRects;            // Rectangles for packing custom texture data into the atlas.
    ImVector<ImFontConfig> ConfigData;                      // Configuration data
    ImVec4 TexUvLines[IM_DRAWLIST_TEX_LINES_WIDTH_MAX + 1]; // UVs for baked anti-aliased lines

    // [Internal] Font builder
    const ImFontBuilderIO *FontBuilderIO; // Opaque interface to a font builder (default to stb_truetype, can be changed to use FreeType by defining IMGUI_ENABLE_FREETYPE).
    unsigned int FontBuilderFlags;        // Shared flags (for all fonts) for custom font builder. THIS IS BUILD IMPLEMENTATION DEPENDENT. Per-font override is also available in ImFontConfig.

    // [Internal] Packing data
    int PackIdMouseCursors; // Custom texture rectangle ID for white pixel and mouse cursors
    int PackIdLines;        // Custom texture rectangle ID for baked anti-aliased lines

    // [Obsolete]
    // typedef ImFontAtlasCustomRect    CustomRect;         // OBSOLETED in 1.72+
    // typedef ImFontGlyphRangesBuilder GlyphRangesBuilder; // OBSOLETED in 1.67+
};