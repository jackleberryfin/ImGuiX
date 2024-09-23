#pragma once

#include "Basic/ImTypeDefs.h"

// Note that Max is exclusive, so perhaps should be using a Begin/End convention.
struct ImGuiListClipperRange
{
    int Min;
    int Max;
    bool PosToIndexConvert;   // Begin/End are absolute position (will be converted to indices later)
    ImS8 PosToIndexOffsetMin; // Add to Min after converting to indices
    ImS8 PosToIndexOffsetMax; // Add to Min after converting to indices

    static ImGuiListClipperRange FromIndices(int min, int max)
    {
        ImGuiListClipperRange r = {min, max, false, 0, 0};
        return r;
    }
    static ImGuiListClipperRange FromPositions(float y1, float y2, int off_min, int off_max)
    {
        ImGuiListClipperRange r = {(int)y1, (int)y2, true, (ImS8)off_min, (ImS8)off_max};
        return r;
    }
};