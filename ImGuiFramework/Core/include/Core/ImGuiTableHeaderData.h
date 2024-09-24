#pragma once

#include "Basic/ImTypeDefs.h"

// Parameters for TableAngledHeadersRowEx()
// This may end up being refactored for more general purpose.
// sizeof() ~ 12 bytes
struct ImGuiTableHeaderData
{
    ImGuiTableColumnIdx Index; // Column index
    ImU32 TextColor;
    ImU32 BgColor0;
    ImU32 BgColor1;
};