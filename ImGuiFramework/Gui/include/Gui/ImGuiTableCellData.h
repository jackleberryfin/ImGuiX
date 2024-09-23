#pragma once

#include "Basic/ImTypeDefs.h"

// Transient cell data stored per row.
// sizeof() ~ 6 bytes
struct ImGuiTableCellData
{
    ImU32 BgColor;              // Actual color
    ImGuiTableColumnIdx Column; // Column number
};