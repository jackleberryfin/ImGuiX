#pragma once

#include "Basic/ImVector.h"
#include "Basic/ImVec2.h"
#include "Gui/ImGuiViewport.h"

struct ImDrawData
{
    bool Valid;                      // Only valid after Render() is called and before the next NewFrame() is called.
    int CmdListsCount;               // Number of ImDrawList* to render
    int TotalIdxCount;               // For convenience, sum of all ImDrawList's IdxBuffer.Size
    int TotalVtxCount;               // For convenience, sum of all ImDrawList's VtxBuffer.Size
    ImVector<ImDrawList *> CmdLists; // Array of ImDrawList* to render. The ImDrawLists are owned by ImGuiContext and only pointed to from here.
    ImVec2 DisplayPos;               // Top-left position of the viewport to render (== top-left of the orthogonal projection matrix to use) (== GetMainViewport()->Pos for the main viewport, == (0.0) in most single-viewport applications)
    ImVec2 DisplaySize;              // Size of the viewport to render (== GetMainViewport()->Size for the main viewport, == io.DisplaySize in most single-viewport applications)
    ImVec2 FramebufferScale;         // Amount of pixels for each unit of DisplaySize. Based on io.DisplayFramebufferScale. Generally (1,1) on normal display, (2,2) on OSX with Retina display.
    ImGuiViewport *OwnerViewport;    // Viewport carrying the ImDrawData instance, might be of use to the renderer (generally not).

    // Functions
    ImDrawData() { Clear(); }
    IMGUI_API void Clear();
    IMGUI_API void AddDrawList(ImDrawList *draw_list);     // Helper to add an external draw list into an existing ImDrawData.
    IMGUI_API void DeIndexAllBuffers();                    // Helper to convert all buffers from indexed to non-indexed, in case you cannot render indexed. Note: this is slow and most likely a waste of resources. Always prefer indexed rendering!
    IMGUI_API void ScaleClipRects(const ImVec2 &fb_scale); // Helper to scale the ClipRect field of each ImDrawCmd. Use if your final output buffer is at a different scale than Dear ImGui expects, or if there is a difference between your window resolution and framebuffer resolution.
};