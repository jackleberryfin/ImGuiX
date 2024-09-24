#pragma once

#include "Basic/ImTypeDefs.h"

// Per-instance data that needs preserving across frames (seemingly most others do not need to be preserved aside from debug needs. Does that means they could be moved to ImGuiTableTempData?)
// sizeof() ~ 24 bytes
struct ImGuiTableInstanceData
{
    ImGuiID TableInstanceID;
    float LastOuterHeight;         // Outer height from last frame
    float LastTopHeadersRowHeight; // Height of first consecutive header rows from last frame (FIXME: this is used assuming consecutive headers are in same frozen set)
    float LastFrozenHeight;        // Height of frozen section from last frame
    int HoveredRowLast;            // Index of row which was hovered last frame.
    int HoveredRowNext;            // Index of row hovered this frame, set after encountering it.

    ImGuiTableInstanceData()
    {
        TableInstanceID = 0;
        LastOuterHeight = LastTopHeadersRowHeight = LastFrozenHeight = 0.0f;
        HoveredRowLast = HoveredRowNext = -1;
    }
};