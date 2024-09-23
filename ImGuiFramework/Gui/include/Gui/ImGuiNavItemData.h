#pragma once

#include "Basic/ImTypeDefs.h"

#include "ImGuiWindow.h"

// Storage for navigation query/results
struct ImGuiNavItemData
{
    ImGuiWindow *Window;                      // Init,Move    // Best candidate window (result->ItemWindow->RootWindowForNav == request->Window)
    ImGuiID ID;                               // Init,Move    // Best candidate item ID
    ImGuiID FocusScopeId;                     // Init,Move    // Best candidate focus scope ID
    ImRect RectRel;                           // Init,Move    // Best candidate bounding box in window relative space
    ImGuiItemFlags InFlags;                   // ????,Move    // Best candidate item flags
    float DistBox;                            //      Move    // Best candidate box distance to current NavId
    float DistCenter;                         //      Move    // Best candidate center distance to current NavId
    float DistAxial;                          //      Move    // Best candidate axial distance to current NavId
    ImGuiSelectionUserData SelectionUserData; // I+Mov    // Best candidate SetNextItemSelectionUserData() value. Valid if (InFlags & ImGuiItemFlags_HasSelectionUserData)

    ImGuiNavItemData() { Clear(); }
    void Clear()
    {
        Window = NULL;
        ID = FocusScopeId = 0;
        InFlags = 0;
        SelectionUserData = -1;
        DistBox = DistCenter = DistAxial = FLT_MAX;
    }
};