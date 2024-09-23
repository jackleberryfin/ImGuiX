#pragma once

#include "Basic/ImVector.h"
#include "Basic/ImVec2.h"
#include "Basic/ImVec4.h"

#include "Font/ImFont.h"

struct IMGUI_API ImDrawListSharedData
{
    ImVec2 TexUvWhitePixel;       // UV of white pixel in the atlas
    ImFont *Font;                 // Current/default font (optional, for simplified AddText overload)
    float FontSize;               // Current/default font size (optional, for simplified AddText overload)
    float FontScale;              // Current/default font scale (== FontSize / Font->FontSize)
    float CurveTessellationTol;   // Tessellation tolerance when using PathBezierCurveTo()
    float CircleSegmentMaxError;  // Number of circle segments to use per pixel of radius for AddCircle() etc
    ImVec4 ClipRectFullscreen;    // Value for PushClipRectFullscreen()
    ImDrawListFlags InitialFlags; // Initial flags at the beginning of the frame (it is possible to alter flags on a per-drawlist basis afterwards)

    // [Internal] Temp write buffer
    ImVector<ImVec2> TempBuffer;

    // [Internal] Lookup tables
    ImVec2 ArcFastVtx[IM_DRAWLIST_ARCFAST_TABLE_SIZE]; // Sample points on the quarter of the circle.
    float ArcFastRadiusCutoff;                         // Cutoff radius after which arc drawing will fallback to slower PathArcTo()
    ImU8 CircleSegmentCounts[64];                      // Precomputed segment count for given radius before we calculate it dynamically (to avoid calculation overhead)
    const ImVec4 *TexUvLines;                          // UV of anti-aliased lines in the atlas

    ImDrawListSharedData();
    void SetCircleTessellationMaxError(float max_error);
};