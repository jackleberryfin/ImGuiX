#pragma once

#include "Basic/ImVec2.h"

// Stacked style modifier, backup of modified data so we can restore it. Data type inferred from the variable.
struct ImGuiStyleMod
{
    ImGuiStyleVar VarIdx;
    union
    {
        int BackupInt[2];
        float BackupFloat[2];
    };
    ImGuiStyleMod(ImGuiStyleVar idx, int v)
    {
        VarIdx = idx;
        BackupInt[0] = v;
    }
    ImGuiStyleMod(ImGuiStyleVar idx, float v)
    {
        VarIdx = idx;
        BackupFloat[0] = v;
    }
    ImGuiStyleMod(ImGuiStyleVar idx, ImVec2 v)
    {
        VarIdx = idx;
        BackupFloat[0] = v.x;
        BackupFloat[1] = v.y;
    }
};