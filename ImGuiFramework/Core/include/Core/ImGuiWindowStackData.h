#pragma once

#include "ImGuiWindow.h"
#include "ImGuiLastItemData.h"
#include "ImGuiStackSizes.h"

// Data saved for each window pushed into the stack
struct ImGuiWindowStackData
{
    ImGuiWindow *Window;
    ImGuiLastItemData ParentLastItemDataBackup;
    ImGuiStackSizes StackSizesOnBegin; // Store size of various stacks for asserting
    bool DisabledOverrideReenable;     // Non-child window override disabled flag
};