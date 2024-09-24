#pragma once

#include "Basic/ImVec1.h"
#include "Basic/ImVec2.h"
#include "Basic/ImTypeDefs.h"

// Stacked storage data for BeginGroup()/EndGroup()
struct IMGUI_API ImGuiGroupData
{
    ImGuiID WindowID;
    ImVec2 BackupCursorPos;
    ImVec2 BackupCursorMaxPos;
    ImVec2 BackupCursorPosPrevLine;
    ImVec1 BackupIndent;
    ImVec1 BackupGroupOffset;
    ImVec2 BackupCurrLineSize;
    float BackupCurrLineTextBaseOffset;
    ImGuiID BackupActiveIdIsAlive;
    bool BackupActiveIdPreviousFrameIsAlive;
    bool BackupHoveredIdIsAlive;
    bool BackupIsSameLine;
    bool EmitItem;
};