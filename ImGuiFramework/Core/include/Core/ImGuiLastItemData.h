#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"
#include "Basic/ImRect.h"

// Status storage for the last submitted item
struct ImGuiLastItemData
{
    ImGuiID ID;
    ImGuiItemFlags InFlags;           // See ImGuiItemFlags_
    ImGuiItemStatusFlags StatusFlags; // See ImGuiItemStatusFlags_
    ImRect Rect;                      // Full rectangle
    ImRect NavRect;                   // Navigation scoring rectangle (not displayed)
    // Rarely used fields are not explicitly cleared, only valid when the corresponding ImGuiItemStatusFlags ar set.
    ImRect DisplayRect;     // Display rectangle. ONLY VALID IF (StatusFlags & ImGuiItemStatusFlags_HasDisplayRect) is set.
    ImRect ClipRect;        // Clip rectangle at the time of submitting item. ONLY VALID IF (StatusFlags & ImGuiItemStatusFlags_HasClipRect) is set..
    ImGuiKeyChord Shortcut; // Shortcut at the time of submitting item. ONLY VALID IF (StatusFlags & ImGuiItemStatusFlags_HasShortcut) is set..

    ImGuiLastItemData() { memset(this, 0, sizeof(*this)); }
};