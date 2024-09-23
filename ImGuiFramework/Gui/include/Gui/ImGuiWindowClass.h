#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"

// [ALPHA] Rarely used / very advanced uses only. Use with SetNextWindowClass() and DockSpace() functions.
// Important: the content of this class is still highly WIP and likely to change and be refactored
// before we stabilize Docking features. Please be mindful if using this.
// Provide hints:
// - To the platform backend via altered viewport flags (enable/disable OS decoration, OS task bar icons, etc.)
// - To the platform backend for OS level parent/child relationships of viewport.
// - To the docking system for various options and filtering.
struct ImGuiWindowClass
{
    ImGuiID ClassId;                               // User data. 0 = Default class (unclassed). Windows of different classes cannot be docked with each others.
    ImGuiID ParentViewportId;                      // Hint for the platform backend. -1: use default. 0: request platform backend to not parent the platform. != 0: request platform backend to create a parent<>child relationship between the platform windows. Not conforming backends are free to e.g. parent every viewport to the main viewport or not.
    ImGuiID FocusRouteParentWindowId;              // ID of parent window for shortcut focus route evaluation, e.g. Shortcut() call from Parent Window will succeed when this window is focused.
    ImGuiViewportFlags ViewportFlagsOverrideSet;   // Viewport flags to set when a window of this class owns a viewport. This allows you to enforce OS decoration or task bar icon, override the defaults on a per-window basis.
    ImGuiViewportFlags ViewportFlagsOverrideClear; // Viewport flags to clear when a window of this class owns a viewport. This allows you to enforce OS decoration or task bar icon, override the defaults on a per-window basis.
    ImGuiTabItemFlags TabItemFlagsOverrideSet;     // [EXPERIMENTAL] TabItem flags to set when a window of this class gets submitted into a dock node tab bar. May use with ImGuiTabItemFlags_Leading or ImGuiTabItemFlags_Trailing.
    ImGuiDockNodeFlags DockNodeFlagsOverrideSet;   // [EXPERIMENTAL] Dock node flags to set when a window of this class is hosted by a dock node (it doesn't have to be selected!)
    bool DockingAlwaysTabBar;                      // Set to true to enforce single floating windows of this class always having their own docking node (equivalent of setting the global io.ConfigDockingAlwaysTabBar)
    bool DockingAllowUnclassed;                    // Set to true to allow windows of this class to be docked/merged with an unclassed window. // FIXME-DOCK: Move to DockNodeFlags override?

    ImGuiWindowClass()
    {
        memset(this, 0, sizeof(*this));
        ParentViewportId = (ImGuiID)-1;
        DockingAllowUnclassed = true;
    }
};