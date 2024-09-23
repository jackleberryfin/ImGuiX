#pragma once

#include "Basic/ImVector.h"

#include "ImGuiListClipper.h"
#include "ImGuiListClipperRange.h"

// Temporary clipper data, buffers shared/reused between instances
struct ImGuiListClipperData
{
    ImGuiListClipper *ListClipper;
    float LossynessOffset;
    int StepNo;
    int ItemsFrozen;
    ImVector<ImGuiListClipperRange> Ranges;

    ImGuiListClipperData() { memset(this, 0, sizeof(*this)); }
    void Reset(ImGuiListClipper *clipper)
    {
        ListClipper = clipper;
        StepNo = ItemsFrozen = 0;
        Ranges.resize(0);
    }
};