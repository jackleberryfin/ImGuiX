#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"

// Sorting specification for one column of a table (sizeof == 12 bytes)
struct ImGuiTableColumnSortSpecs
{
    ImGuiID ColumnUserID;             // User id of the column (if specified by a TableSetupColumn() call)
    ImS16 ColumnIndex;                // Index of the column
    ImS16 SortOrder;                  // Index within parent ImGuiTableSortSpecs (always stored in order starting from 0, tables sorted on a single criteria will always have a 0 here)
    ImGuiSortDirection SortDirection; // ImGuiSortDirection_Ascending or ImGuiSortDirection_Descending

    ImGuiTableColumnSortSpecs() { memset(this, 0, sizeof(*this)); }
};