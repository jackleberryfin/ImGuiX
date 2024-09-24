#pragma once

#include "Basic/ImVec2.h"

// (Optional) This is required when enabling multi-viewport. Represent the bounds of each connected monitor/display and their DPI.
// We use this information for multiple DPI support + clamping the position of popups and tooltips so they don't straddle multiple monitors.
struct ImGuiPlatformMonitor
{
    ImVec2 MainPos, MainSize; // Coordinates of the area displayed on this monitor (Min = upper left, Max = bottom right)
    ImVec2 WorkPos, WorkSize; // Coordinates without task bars / side bars / menu bars. Used to avoid positioning popups/tooltips inside this region. If you don't have this info, please copy the value for MainPos/MainSize.
    float DpiScale;           // 1.0f = 96 DPI
    void *PlatformHandle;     // Backend dependant data (e.g. HMONITOR, GLFWmonitor*, SDL Display Index, NSScreen*)
    ImGuiPlatformMonitor()
    {
        MainPos = MainSize = WorkPos = WorkSize = ImVec2(0, 0);
        DpiScale = 1.0f;
        PlatformHandle = NULL;
    }
};