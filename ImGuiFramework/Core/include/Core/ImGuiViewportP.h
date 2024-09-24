#pragma once

#include <cfloat>

#include "Basic/ImTypeDefs.h"
#include "Basic/ImVec2.h"

#include "Draw/ImDrawData.h"
#include "Draw/ImDrawDataBuilder.h"
#include "ImGuiWindow.h"

// ImGuiViewport Private/Internals fields (cardinal sin: we are using inheritance!)
// Every instance of ImGuiViewport is in fact a ImGuiViewportP.
struct ImGuiViewportP : public ImGuiViewport
{
    ImGuiWindow *Window; // Set when the viewport is owned by a window (and ImGuiViewportFlags_CanHostOtherWindows is NOT set)
    int Idx;
    int LastFrameActive;       // Last frame number this viewport was activated by a window
    int LastFocusedStampCount; // Last stamp number from when a window hosted by this viewport was focused (by comparing this value between two viewport we have an implicit viewport z-order we use as fallback)
    ImGuiID LastNameHash;
    ImVec2 LastPos;
    ImVec2 LastSize;
    float Alpha; // Window opacity (when dragging dockable windows/viewports we make them transparent)
    float LastAlpha;
    bool LastFocusedHadNavWindow; // Instead of maintaining a LastFocusedWindow (which may harder to correctly maintain), we merely store weither NavWindow != NULL last time the viewport was focused.
    short PlatformMonitor;
    int BgFgDrawListsLastFrame[2]; // Last frame number the background (0) and foreground (1) draw lists were used
    ImDrawList *BgFgDrawLists[2];  // Convenience background (0) and foreground (1) draw lists. We use them to draw software mouser cursor when io.MouseDrawCursor is set and to draw most debug overlays.
    ImDrawData DrawDataP;
    ImDrawDataBuilder DrawDataBuilder; // Temporary data while building final ImDrawData
    ImVec2 LastPlatformPos;
    ImVec2 LastPlatformSize;
    ImVec2 LastRendererSize;

    // Per-viewport work area
    // - Insets are >= 0.0f values, distance from viewport corners to work area.
    // - BeginMainMenuBar() and DockspaceOverViewport() tend to use work area to avoid stepping over existing contents.
    // - Generally 'safeAreaInsets' in iOS land, 'DisplayCutout' in Android land.
    ImVec2 WorkInsetMin;      // Work Area inset locked for the frame. GetWorkRect() always fits within GetMainRect().
    ImVec2 WorkInsetMax;      // "
    ImVec2 BuildWorkInsetMin; // Work Area inset accumulator for current frame, to become next frame's WorkInset
    ImVec2 BuildWorkInsetMax; // "

    ImGuiViewportP()
    {
        Window = NULL;
        Idx = -1;
        LastFrameActive = BgFgDrawListsLastFrame[0] = BgFgDrawListsLastFrame[1] = LastFocusedStampCount = -1;
        LastNameHash = 0;
        Alpha = LastAlpha = 1.0f;
        LastFocusedHadNavWindow = false;
        PlatformMonitor = -1;
        BgFgDrawLists[0] = BgFgDrawLists[1] = NULL;
        LastPlatformPos = LastPlatformSize = LastRendererSize = ImVec2(FLT_MAX, FLT_MAX);
    }
    ~ImGuiViewportP()
    {
        if (BgFgDrawLists[0])
            IM_DELETE(BgFgDrawLists[0]);
        if (BgFgDrawLists[1])
            IM_DELETE(BgFgDrawLists[1]);
    }
    void ClearRequestFlags() { PlatformRequestClose = PlatformRequestMove = PlatformRequestResize = false; }

    // Calculate work rect pos/size given a set of offset (we have 1 pair of offset for rect locked from last frame data, and 1 pair for currently building rect)
    ImVec2 CalcWorkRectPos(const ImVec2 &inset_min) const { return ImVec2(Pos.x + inset_min.x, Pos.y + inset_min.y); }
    ImVec2 CalcWorkRectSize(const ImVec2 &inset_min, const ImVec2 &inset_max) const { return ImVec2(ImMax(0.0f, Size.x - inset_min.x - inset_max.x), ImMax(0.0f, Size.y - inset_min.y - inset_max.y)); }
    void UpdateWorkRect()
    {
        WorkPos = CalcWorkRectPos(WorkInsetMin);
        WorkSize = CalcWorkRectSize(WorkInsetMin, WorkInsetMax);
    } // Update public fields

    // Helpers to retrieve ImRect (we don't need to store BuildWorkRect as every access tend to change it, hence the code asymmetry)
    ImRect GetMainRect() const { return ImRect(Pos.x, Pos.y, Pos.x + Size.x, Pos.y + Size.y); }
    ImRect GetWorkRect() const { return ImRect(WorkPos.x, WorkPos.y, WorkPos.x + WorkSize.x, WorkPos.y + WorkSize.y); }
    ImRect GetBuildWorkRect() const
    {
        ImVec2 pos = CalcWorkRectPos(BuildWorkInsetMin);
        ImVec2 size = CalcWorkRectSize(BuildWorkInsetMin, BuildWorkInsetMax);
        return ImRect(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
    }
};