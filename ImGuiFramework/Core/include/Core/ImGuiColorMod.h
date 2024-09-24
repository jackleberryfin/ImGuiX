#pragma once

#include "Basic/ImVec4.h"
#include "Basic/ImTypeDefs.h"

// Stacked color modifier, backup of modified data so we can restore it
struct ImGuiColorMod
{
    ImGuiCol Col;
    ImVec4 BackupValue;
};