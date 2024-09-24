#pragma once

#include "Basic/ImVec2.h"
#include "Basic/ImTypeDefs.h"
#include "Basic/ImRect.h"
#include "Basic/ImEnum.h"

#include "Gui/ImGuiWindowClass.h"

// Storage for SetNexWindow** functions
struct ImGuiNextWindowData
{
    ImGuiNextWindowDataFlags Flags;
    ImGuiCond PosCond;
    ImGuiCond SizeCond;
    ImGuiCond CollapsedCond;
    ImGuiCond DockCond;
    ImVec2 PosVal;
    ImVec2 PosPivotVal;
    ImVec2 SizeVal;
    ImVec2 ContentSizeVal;
    ImVec2 ScrollVal;
    ImGuiChildFlags ChildFlags;
    bool PosUndock;
    bool CollapsedVal;
    ImRect SizeConstraintRect;
    ImGuiSizeCallback SizeCallback;
    void *SizeCallbackUserData;
    float BgAlphaVal; // Override background alpha
    ImGuiID ViewportId;
    ImGuiID DockId;
    ImGuiWindowClass WindowClass;
    ImVec2 MenuBarOffsetMinVal; // (Always on) This is not exposed publicly, so we don't clear it and it doesn't have a corresponding flag (could we? for consistency?)
    ImGuiWindowRefreshFlags RefreshFlagsVal;

    ImGuiNextWindowData() { memset(this, 0, sizeof(*this)); }
    inline void ClearFlags() { Flags = ImGuiNextWindowDataFlags_None; }
};