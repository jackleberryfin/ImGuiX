#pragma once

#include "Basic/ImEnum.h"

#include "Draw/ImDrawData.h"
#include "Draw/ImDrawList.h"
#include "Draw/ImDrawVert.h"

namespace ImGui {

#define IM_ALLOC(_SIZE) MemAlloc(_SIZE)
#define IM_FREE(_PTR) MemFree(_PTR)
#define IM_PLACEMENT_NEW(_PTR) new (ImNewWrapper(), _PTR)
#define IM_NEW(_TYPE) new (ImNewWrapper(), ImGui::MemAlloc(sizeof(_TYPE))) _TYPE

// IM_FREE() == ImGui::MemFree()
void ImGui::MemFree(void* ptr) {
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
    if (ptr != NULL)
        if (ImGuiContext* ctx = GImGui)
            DebugAllocHook(&ctx->DebugAllocInfo, ctx->FrameCount, ptr, (size_t)-1);
#endif
    return (*GImAllocatorFreeFunc)(ptr, GImAllocatorUserData);
}

void AddDrawListToDrawDataEx(ImDrawData* draw_data, ImVector<ImDrawList*>* out_list, ImDrawList* draw_list) {
    if (draw_list->CmdBuffer.Size == 0)
        return;
    if (draw_list->CmdBuffer.Size == 1 && draw_list->CmdBuffer[0].ElemCount == 0 && draw_list->CmdBuffer[0].UserCallback == NULL)
        return;

    // Draw list sanity check. Detect mismatch between PrimReserve() calls and incrementing _VtxCurrentIdx, _VtxWritePtr etc.
    // May trigger for you if you are using PrimXXX functions incorrectly.
    IM_ASSERT(draw_list->VtxBuffer.Size == 0 || draw_list->_VtxWritePtr == draw_list->VtxBuffer.Data + draw_list->VtxBuffer.Size);
    IM_ASSERT(draw_list->IdxBuffer.Size == 0 || draw_list->_IdxWritePtr == draw_list->IdxBuffer.Data + draw_list->IdxBuffer.Size);
    if (!(draw_list->Flags & ImDrawListFlags_AllowVtxOffset))
        IM_ASSERT((int)draw_list->_VtxCurrentIdx == draw_list->VtxBuffer.Size);

    // Check that draw_list doesn't use more vertices than indexable (default ImDrawIdx = unsigned short = 2 bytes = 64K
    // vertices per ImDrawList = per window) If this assert triggers because you are drawing lots of stuff manually:
    // - First, make sure you are coarse clipping yourself and not trying to draw many things outside visible bounds.
    //   Be mindful that the lower-level ImDrawList API doesn't filter vertices. Use the Metrics/Debugger window to inspect
    //   draw list contents.
    // - If you want large meshes with more than 64K vertices, you can either:
    //   (A) Handle the ImDrawCmd::VtxOffset value in your renderer backend, and set 'io.BackendFlags |=
    //   ImGuiBackendFlags_RendererHasVtxOffset'.
    //       Most example backends already support this from 1.71. Pre-1.71 backends won't.
    //       Some graphics API such as GL ES 1/2 don't have a way to offset the starting vertex so it is not supported for
    //       them.
    //   (B) Or handle 32-bit indices in your renderer backend, and uncomment '#define ImDrawIdx unsigned int' line in
    //   imconfig.h.
    //       Most example backends already support this. For example, the OpenGL example code detect index size at
    //       compile-time:
    //         glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT :
    //         GL_UNSIGNED_INT, idx_buffer_offset);
    //       Your own engine or render API may use different parameters or function calls to specify index sizes.
    //       2 and 4 bytes indices are generally supported by most graphics API.
    // - If for some reason neither of those solutions works for you, a workaround is to call BeginChild()/EndChild() before
    // reaching
    //   the 64K limit to split your draw commands in multiple draw lists.
    if (sizeof(ImDrawIdx) == 2)
        IM_ASSERT(draw_list->_VtxCurrentIdx < (1 << 16) && "Too many vertices in ImDrawList using 16-bit indices. Read comment above");

    // Add to output list + records state in ImDrawData
    out_list->push_back(draw_list);
    draw_data->CmdListsCount++;
    draw_data->TotalVtxCount += draw_list->VtxBuffer.Size;
    draw_data->TotalIdxCount += draw_list->IdxBuffer.Size;
}

}; // namespace ImGui