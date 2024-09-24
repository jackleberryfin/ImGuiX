#pragma once

// Flags for ImDrawList functions
// (Legacy: bit 0 must always correspond to ImDrawFlags_Closed to be backward compatible with old API using a bool. Bits 1..3
// must be unused)
enum ImDrawFlags_ {
    ImDrawFlags_None = 0,
    ImDrawFlags_Closed = 1 << 0, // PathStroke(), AddPolyline(): specify that shape should be closed (Important: this is
                                 // always == 1 for legacy reason)
    ImDrawFlags_RoundCornersTopLeft = 1 << 4, // AddRect(), AddRectFilled(), PathRect(): enable rounding top-left corner only
                                              // (when rounding > 0.0f, we default to all corners). Was 0x01.
    ImDrawFlags_RoundCornersTopRight = 1 << 5,    // AddRect(), AddRectFilled(), PathRect(): enable rounding top-right corner
                                                  // only (when rounding > 0.0f, we default to all corners). Was 0x02.
    ImDrawFlags_RoundCornersBottomLeft = 1 << 6,  // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-left
                                                  // corner only (when rounding > 0.0f, we default to all corners). Was 0x04.
    ImDrawFlags_RoundCornersBottomRight = 1 << 7, // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-right
                                                  // corner only (when rounding > 0.0f, we default to all corners). Wax 0x08.
    ImDrawFlags_RoundCornersNone = 1 << 8, // AddRect(), AddRectFilled(), PathRect(): disable rounding on all corners (when
                                           // rounding > 0.0f). This is NOT zero, NOT an implicit flag!
    ImDrawFlags_RoundCornersTop = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersBottom = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersLeft = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersTopLeft,
    ImDrawFlags_RoundCornersRight = ImDrawFlags_RoundCornersBottomRight | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersAll = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight |
                                  ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersDefault_ =
        ImDrawFlags_RoundCornersAll, // Default to ALL corners if none of the _RoundCornersXX flags are specified.
    ImDrawFlags_RoundCornersMask_ = ImDrawFlags_RoundCornersAll | ImDrawFlags_RoundCornersNone,
};

// Flags for ImDrawList instance. Those are set automatically by ImGui:: functions from ImGuiIO settings, and generally not
// manipulated directly. It is however possible to temporarily alter flags between calls to ImDrawList:: functions.
enum ImDrawListFlags_ {
    ImDrawListFlags_None = 0,
    ImDrawListFlags_AntiAliasedLines =
        1 << 0, // Enable anti-aliased lines/borders (*2 the number of triangles for 1.0f wide line or lines thin enough to
                // be drawn using textures, otherwise *3 the number of triangles)
    ImDrawListFlags_AntiAliasedLinesUseTex =
        1 << 1, // Enable anti-aliased lines/borders using textures when possible. Require backend to render with bilinear
                // filtering (NOT point/nearest filtering).
    ImDrawListFlags_AntiAliasedFill = 1 << 2, // Enable anti-aliased edge around filled shapes (rounded rectangles, circles).
    ImDrawListFlags_AllowVtxOffset = 1 << 3,  // Can emit 'VtxOffset > 0' to allow large meshes. Set when
                                              // 'ImGuiBackendFlags_RendererHasVtxOffset' is enabled.
};