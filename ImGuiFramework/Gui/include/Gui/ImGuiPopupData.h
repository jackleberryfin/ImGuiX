#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"

#include "Gui/ImGuiWindow.h"

// Storage for popup stacks (g.OpenPopupStack and g.BeginPopupStack)
struct ImGuiPopupData
{
    ImGuiID PopupId;               // Set on OpenPopup()
    ImGuiWindow *Window;           // Resolved on BeginPopup() - may stay unresolved if user never calls OpenPopup()
    ImGuiWindow *RestoreNavWindow; // Set on OpenPopup(), a NavWindow that will be restored on popup close
    int ParentNavLayer;            // Resolved on BeginPopup(). Actually a ImGuiNavLayer type (declared down below), initialized to -1 which is not part of an enum, but serves well-enough as "not any of layers" value
    int OpenFrameCount;            // Set on OpenPopup()
    ImGuiID OpenParentId;          // Set on OpenPopup(), we need this to differentiate multiple menu sets from each others (e.g. inside menu bar vs loose menu items)
    ImVec2 OpenPopupPos;           // Set on OpenPopup(), preferred popup position (typically == OpenMousePos when using mouse)
    ImVec2 OpenMousePos;           // Set on OpenPopup(), copy of mouse position at the time of opening popup

    ImGuiPopupData()
    {
        memset(this, 0, sizeof(*this));
        ParentNavLayer = OpenFrameCount = -1;
    }
};