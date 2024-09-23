#pragma once

#include <memory>

#include "Basic/ImVec1.h"
#include "Basic/ImVec2.h"
#include "Basic/ImRect.h"
#include "Basic/ImVector.h"

#include "Draw/ImDrawListSplitter.h"

#include "ImGuiTableHeaderData.h"

// Transient data that are only needed between BeginTable() and EndTable(), those buffers are shared (1 per level of stacked table).
// - Accessing those requires chasing an extra pointer so for very frequently used data we leave them in the main table structure.
// - We also leave out of this structure data that tend to be particularly useful for debugging/metrics.
// FIXME-TABLE: more transient data could be stored in a stacked ImGuiTableTempData: e.g. SortSpecs.
// sizeof() ~ 136 bytes.
struct IMGUI_API ImGuiTableTempData
{
    int TableIndex;                                       // Index in g.Tables.Buf[] pool
    float LastTimeActive;                                 // Last timestamp this structure was used
    float AngledHeadersExtraWidth;                        // Used in EndTable()
    ImVector<ImGuiTableHeaderData> AngledHeadersRequests; // Used in TableAngledHeadersRow()

    ImVec2 UserOuterSize; // outer_size.x passed to BeginTable()
    ImDrawListSplitter DrawSplitter;

    ImRect HostBackupWorkRect;        // Backup of InnerWindow->WorkRect at the end of BeginTable()
    ImRect HostBackupParentWorkRect;  // Backup of InnerWindow->ParentWorkRect at the end of BeginTable()
    ImVec2 HostBackupPrevLineSize;    // Backup of InnerWindow->DC.PrevLineSize at the end of BeginTable()
    ImVec2 HostBackupCurrLineSize;    // Backup of InnerWindow->DC.CurrLineSize at the end of BeginTable()
    ImVec2 HostBackupCursorMaxPos;    // Backup of InnerWindow->DC.CursorMaxPos at the end of BeginTable()
    ImVec1 HostBackupColumnsOffset;   // Backup of OuterWindow->DC.ColumnsOffset at the end of BeginTable()
    float HostBackupItemWidth;        // Backup of OuterWindow->DC.ItemWidth at the end of BeginTable()
    int HostBackupItemWidthStackSize; // Backup of OuterWindow->DC.ItemWidthStack.Size at the end of BeginTable()

    ImGuiTableTempData()
    {
        memset(this, 0, sizeof(*this));
        LastTimeActive = -1.0f;
    }
};