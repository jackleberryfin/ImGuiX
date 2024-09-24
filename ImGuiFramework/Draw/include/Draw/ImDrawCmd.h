#pragma once

#include <memory>

#include "Basic/ImTypes.h"
#include "Basic/ImVec4.h"

struct ImDrawCmd {
    ImVec4 ClipRect;       // 4*4  // Clipping rectangle (x1, y1, x2, y2). Subtract ImDrawData->DisplayPos to get clipping
                           // rectangle in "viewport" coordinates
    ImTextureID TextureId; // 4-8  // User-provided texture ID. Set by user in ImfontAtlas::SetTexID() for fonts or passed to
                           // Image*() functions. Ignore if never using images or multiple fonts atlas.
    unsigned int VtxOffset; // 4    // Start offset in vertex buffer. ImGuiBackendFlags_RendererHasVtxOffset: always 0,
                            // otherwise may be >0 to support meshes larger than 64K vertices with 16-bit indices.
    unsigned int IdxOffset; // 4    // Start offset in index buffer.
    unsigned int ElemCount; // 4    // Number of indices (multiple of 3) to be rendered as triangles. Vertices are stored in
                            // the callee ImDrawList's vtx_buffer[] array, indices in idx_buffer[].
    ImDrawCallback UserCallback; // 4-8  // If != NULL, call the function instead of rendering the vertices. clip_rect and
                                 // texture_id will be set normally.
    void* UserCallbackData;      // 4-8  // The draw callback code can access this.

    ImDrawCmd() { memset(this, 0, sizeof(*this)); } // Also ensure our padding fields are zeroed

    // Since 1.83: returns ImTextureID associated with this draw call. Warning: DO NOT assume this is always same as
    // 'TextureId' (we will change this function for an upcoming feature)
    inline ImTextureID GetTexID() const { return TextureId; }
};