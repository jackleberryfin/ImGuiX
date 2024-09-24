#pragma once

#include "Basic/ImTypes.h"
#include "Basic/ImVector.h"

#include "ImDrawCmd.h"
#include "ImDrawCmdHeader.h"
#include "ImDrawListSharedData.h"
#include "ImDrawListSplitter.h"
#include "ImDrawVert.h"

struct ImDrawList {
    // This is what you have to render
    ImVector<ImDrawCmd> CmdBuffer; // Draw commands. Typically 1 command = 1 GPU draw call, unless the command is a callback.
    ImVector<ImDrawIdx> IdxBuffer; // Index buffer. Each command consume ImDrawCmd::ElemCount of those
    ImVector<ImDrawVert> VtxBuffer; // Vertex buffer.
    ImDrawListFlags Flags;          // Flags, you may poke into these to adjust anti-aliasing settings per-primitive.

    // [Internal, used while building lists]
    unsigned int _VtxCurrentIdx; // [Internal] generally == VtxBuffer.Size unless we are past 64K vertices, in which case
                                 // this gets reset to 0.
    ImDrawListSharedData* _Data; // Pointer to shared draw data (you can use ImGui::GetDrawListSharedData() to get the one
                                 // from current ImGui context)
    ImDrawVert* _VtxWritePtr; // [Internal] point within VtxBuffer.Data after each add command (to avoid using the ImVector<>
                              // operators too much)
    ImDrawIdx* _IdxWritePtr;  // [Internal] point within IdxBuffer.Data after each add command (to avoid using the ImVector<>
                              // operators too much)
    ImVector<ImVec2> _Path;   // [Internal] current path building
    ImDrawCmdHeader _CmdHeader; // [Internal] template of active commands. Fields should match those of CmdBuffer.back().
    ImDrawListSplitter
        _Splitter; // [Internal] for channels api (note: prefer using your own persistent instance of ImDrawListSplitter!)
    ImVector<ImVec4> _ClipRectStack;       // [Internal]
    ImVector<ImTextureID> _TextureIdStack; // [Internal]
    float _FringeScale;     // [Internal] anti-alias fringe is scaled by this value, this helps to keep things sharp while
                            // zooming at vertex buffer content
    const char* _OwnerName; // Pointer to owner window's name for debugging

    // If you want to create ImDrawList instances, pass them ImGui::GetDrawListSharedData() or create and use your own
    // ImDrawListSharedData (so you can use ImDrawList without ImGui)
    ImDrawList(ImDrawListSharedData* shared_data) {
        memset(this, 0, sizeof(*this));
        _Data = shared_data;
    }

    ~ImDrawList() { _ClearFreeMemory(); }

    IMGUI_API void PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max,
                                bool intersect_with_current_clip_rect =
                                    false); // Render-level scissoring. This is passed down to your render function but not
                                            // used for CPU-side coarse clipping. Prefer using higher-level
                                            // ImGui::PushClipRect() to affect logic (hit-testing and widget culling)
    IMGUI_API void PushClipRectFullScreen();
    IMGUI_API void PopClipRect();
    IMGUI_API void PushTextureID(ImTextureID texture_id);
    IMGUI_API void PopTextureID();

    inline ImVec2 GetClipRectMin() const {
        const ImVec4& cr = _ClipRectStack.back();
        return ImVec2(cr.x, cr.y);
    }

    inline ImVec2 GetClipRectMax() const {
        const ImVec4& cr = _ClipRectStack.back();
        return ImVec2(cr.z, cr.w);
    }

    // Primitives
    // - Filled shapes must always use clockwise winding order. The anti-aliasing fringe depends on it. Counter-clockwise
    // shapes will have "inward" anti-aliasing.
    // - For rectangular primitives, "p_min" and "p_max" represent the upper-left and lower-right corners.
    // - For circle primitives, use "num_segments == 0" to automatically calculate tessellation (preferred).
    //   In older versions (until Dear ImGui 1.77) the AddCircle functions defaulted to num_segments == 12.
    //   In future versions we will use textures to provide cheaper and higher-quality circles.
    //   Use AddNgon() and AddNgonFilled() functions if you need to guarantee a specific number of sides.
    IMGUI_API void AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f);
    IMGUI_API void AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0,
                           float thickness = 1.0f); // a: upper-left, b: lower-right (== upper-left + size)
    IMGUI_API void AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f,
                                 ImDrawFlags flags = 0); // a: upper-left, b: lower-right (== upper-left + size)
    IMGUI_API void AddRectFilledMultiColor(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right,
                                           ImU32 col_bot_right, ImU32 col_bot_left);
    IMGUI_API void AddQuad(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col,
                           float thickness = 1.0f);
    IMGUI_API void AddQuadFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col);
    IMGUI_API void AddTriangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness = 1.0f);
    IMGUI_API void AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col);
    IMGUI_API void AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments = 0, float thickness = 1.0f);
    IMGUI_API void AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments = 0);
    IMGUI_API void AddNgon(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
    IMGUI_API void AddNgonFilled(const ImVec2& center, float radius, ImU32 col, int num_segments);
    IMGUI_API void AddEllipse(const ImVec2& center, const ImVec2& radius, ImU32 col, float rot = 0.0f, int num_segments = 0,
                              float thickness = 1.0f);
    IMGUI_API void AddEllipseFilled(const ImVec2& center, const ImVec2& radius, ImU32 col, float rot = 0.0f,
                                    int num_segments = 0);
    IMGUI_API void AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL);
    IMGUI_API void AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin,
                           const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
    IMGUI_API void AddBezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col,
                                  float thickness, int num_segments = 0); // Cubic Bezier (4 control points)
    IMGUI_API void AddBezierQuadratic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness,
                                      int num_segments = 0); // Quadratic Bezier (3 control points)

    // General polygon
    // - Only simple polygons are supported by filling functions (no self-intersections, no holes).
    // - Concave polygon fill is more expensive than convex one: it has O(N^2) complexity. Provided as a convenience fo user
    // but not used by main library.
    IMGUI_API void AddPolyline(const ImVec2* points, int num_points, ImU32 col, ImDrawFlags flags, float thickness);
    IMGUI_API void AddConvexPolyFilled(const ImVec2* points, int num_points, ImU32 col);
    IMGUI_API void AddConcavePolyFilled(const ImVec2* points, int num_points, ImU32 col);

    // Image primitives
    // - Read FAQ to understand what ImTextureID is.
    // - "p_min" and "p_max" represent the upper-left and lower-right corners of the rectangle.
    // - "uv_min" and "uv_max" represent the normalized texture coordinates to use for those corners. Using (0,0)->(1,1)
    // texture coordinates will generally display the entire texture.
    IMGUI_API void AddImage(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max,
                            const ImVec2& uv_min = ImVec2(0, 0), const ImVec2& uv_max = ImVec2(1, 1),
                            ImU32 col = IM_COL32_WHITE);
    IMGUI_API void AddImageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3,
                                const ImVec2& p4, const ImVec2& uv1 = ImVec2(0, 0), const ImVec2& uv2 = ImVec2(1, 0),
                                const ImVec2& uv3 = ImVec2(1, 1), const ImVec2& uv4 = ImVec2(0, 1),
                                ImU32 col = IM_COL32_WHITE);
    IMGUI_API void AddImageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max,
                                   const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding,
                                   ImDrawFlags flags = 0);

    // Stateful path API, add points then finish with PathFillConvex() or PathStroke()
    // - Important: filled shapes must always use clockwise winding order! The anti-aliasing fringe depends on it.
    // Counter-clockwise shapes will have "inward" anti-aliasing.
    //   so e.g. 'PathArcTo(center, radius, PI * -0.5f, PI)' is ok, whereas 'PathArcTo(center, radius, PI, PI * -0.5f)' won't
    //   have correct anti-aliasing when followed by PathFillConvex().
    inline void PathClear() { _Path.Size = 0; }

    inline void PathLineTo(const ImVec2& pos) { _Path.push_back(pos); }

    inline void PathLineToMergeDuplicate(const ImVec2& pos) {
        if (_Path.Size == 0 || memcmp(&_Path.Data[_Path.Size - 1], &pos, 8) != 0)
            _Path.push_back(pos);
    }

    inline void PathFillConvex(ImU32 col) {
        AddConvexPolyFilled(_Path.Data, _Path.Size, col);
        _Path.Size = 0;
    }

    inline void PathFillConcave(ImU32 col) {
        AddConcavePolyFilled(_Path.Data, _Path.Size, col);
        _Path.Size = 0;
    }

    inline void PathStroke(ImU32 col, ImDrawFlags flags = 0, float thickness = 1.0f) {
        AddPolyline(_Path.Data, _Path.Size, col, flags, thickness);
        _Path.Size = 0;
    }

    IMGUI_API void PathArcTo(const ImVec2& center, float radius, float a_min, float a_max, int num_segments = 0);
    IMGUI_API void PathArcToFast(const ImVec2& center, float radius, int a_min_of_12,
                                 int a_max_of_12); // Use precomputed angles for a 12 steps circle
    IMGUI_API void PathEllipticalArcTo(const ImVec2& center, const ImVec2& radius, float rot, float a_min, float a_max,
                                       int num_segments = 0); // Ellipse
    IMGUI_API void PathBezierCubicCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4,
                                          int num_segments = 0); // Cubic Bezier (4 control points)
    IMGUI_API void PathBezierQuadraticCurveTo(const ImVec2& p2, const ImVec2& p3,
                                              int num_segments = 0); // Quadratic Bezier (3 control points)
    IMGUI_API void PathRect(const ImVec2& rect_min, const ImVec2& rect_max, float rounding = 0.0f, ImDrawFlags flags = 0);

    // Advanced
    IMGUI_API void AddCallback(ImDrawCallback callback,
                               void* callback_data); // Your rendering function must check for 'UserCallback' in ImDrawCmd
                                                     // and call the function instead of rendering triangles.
    IMGUI_API void
    AddDrawCmd(); // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering /
                  // blending). Otherwise primitives are merged into the same draw-call as much as possible
    IMGUI_API ImDrawList* CloneOutput() const; // Create a clone of the CmdBuffer/IdxBuffer/VtxBuffer.

    // Advanced: Channels
    // - Use to split render into layers. By switching channels to can render out-of-order (e.g. submit FG primitives before
    // BG primitives)
    // - Use to minimize draw calls (e.g. if going back-and-forth between multiple clipping rectangles, prefer to append into
    // separate channels then merge at the end)
    // - This API shouldn't have been in ImDrawList in the first place!
    //   Prefer using your own persistent instance of ImDrawListSplitter as you can stack them.
    //   Using the ImDrawList::ChannelsXXXX you cannot stack a split over another.
    inline void ChannelsSplit(int count) { _Splitter.Split(this, count); }

    inline void ChannelsMerge() { _Splitter.Merge(this); }

    inline void ChannelsSetCurrent(int n) { _Splitter.SetCurrentChannel(this, n); }

    // Advanced: Primitives allocations
    // - We render triangles (three vertices)
    // - All primitives needs to be reserved via PrimReserve() beforehand.
    IMGUI_API void PrimReserve(int idx_count, int vtx_count);
    IMGUI_API void PrimUnreserve(int idx_count, int vtx_count);
    IMGUI_API void PrimRect(const ImVec2& a, const ImVec2& b,
                            ImU32 col); // Axis aligned rectangle (composed of two triangles)
    IMGUI_API void PrimRectUV(const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col);
    IMGUI_API void PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a,
                              const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col);

    inline void PrimWriteVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) {
        _VtxWritePtr->pos = pos;
        _VtxWritePtr->uv = uv;
        _VtxWritePtr->col = col;
        _VtxWritePtr++;
        _VtxCurrentIdx++;
    }

    inline void PrimWriteIdx(ImDrawIdx idx) {
        *_IdxWritePtr = idx;
        _IdxWritePtr++;
    }

    inline void PrimVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) {
        PrimWriteIdx((ImDrawIdx)_VtxCurrentIdx);
        PrimWriteVtx(pos, uv, col);
    } // Write vertex with unique index

    // Obsolete names
    // inline  void  AddEllipse(const ImVec2& center, float radius_x, float radius_y, ImU32 col, float rot = 0.0f, int
    // num_segments = 0, float thickness = 1.0f) { AddEllipse(center, ImVec2(radius_x, radius_y), col, rot, num_segments,
    // thickness); } // OBSOLETED in 1.90.5 (Mar 2024) inline  void  AddEllipseFilled(const ImVec2& center, float radius_x,
    // float radius_y, ImU32 col, float rot = 0.0f, int num_segments = 0) { AddEllipseFilled(center, ImVec2(radius_x,
    // radius_y), col, rot, num_segments); }                        // OBSOLETED in 1.90.5 (Mar 2024) inline  void
    // PathEllipticalArcTo(const ImVec2& center, float radius_x, float radius_y, float rot, float a_min, float a_max, int
    // num_segments = 0) { PathEllipticalArcTo(center, ImVec2(radius_x, radius_y), rot, a_min, a_max, num_segments); } //
    // OBSOLETED in 1.90.5 (Mar 2024) inline  void  AddBezierCurve(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3,
    // const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0) { AddBezierCubic(p1, p2, p3, p4, col, thickness,
    // num_segments); } // OBSOLETED in 1.80 (Jan 2021) inline  void  PathBezierCurveTo(const ImVec2& p2, const ImVec2& p3,
    // const ImVec2& p4, int num_segments = 0) { PathBezierCubicCurveTo(p2, p3, p4, num_segments); } // OBSOLETED in 1.80
    // (Jan 2021)

    // [Internal helpers]
    IMGUI_API void _ResetForNewFrame();
    IMGUI_API void _ClearFreeMemory();
    IMGUI_API void _PopUnusedDrawCmd();
    IMGUI_API void _TryMergeDrawCmds();
    IMGUI_API void _OnChangedClipRect();
    IMGUI_API void _OnChangedTextureID();
    IMGUI_API void _OnChangedVtxOffset();
    IMGUI_API void _SetTextureID(ImTextureID texture_id);
    IMGUI_API int _CalcCircleAutoSegmentCount(float radius) const;
    IMGUI_API void _PathArcToFastEx(const ImVec2& center, float radius, int a_min_sample, int a_max_sample, int a_step);
    IMGUI_API void _PathArcToN(const ImVec2& center, float radius, float a_min, float a_max, int num_segments);
};