#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"
#include "Basic/ImEnum.h"

#include "ImGuiDataTypeStorage.h"

struct ImGuiNextItemData
{
    ImGuiNextItemDataFlags Flags;
    ImGuiItemFlags ItemFlags; // Currently only tested/used for ImGuiItemFlags_AllowOverlap and ImGuiItemFlags_HasSelectionUserData.
    // Non-flags members are NOT cleared by ItemAdd() meaning they are still valid during NavProcessItem()
    ImGuiID FocusScopeId;                     // Set by SetNextItemSelectionUserData()
    ImGuiSelectionUserData SelectionUserData; // Set by SetNextItemSelectionUserData() (note that NULL/0 is a valid value, we use -1 == ImGuiSelectionUserData_Invalid to mark invalid values)
    float Width;                              // Set by SetNextItemWidth()
    ImGuiKeyChord Shortcut;                   // Set by SetNextItemShortcut()
    ImGuiInputFlags ShortcutFlags;            // Set by SetNextItemShortcut()
    bool OpenVal;                             // Set by SetNextItemOpen()
    ImU8 OpenCond;                            // Set by SetNextItemOpen()
    ImGuiDataTypeStorage RefVal;              // Not exposed yet, for ImGuiInputTextFlags_ParseEmptyAsRefVal
    ImGuiID StorageId;                        // Set by SetNextItemStorageID()

    ImGuiNextItemData()
    {
        memset(this, 0, sizeof(*this));
        SelectionUserData = -1;
    }
    inline void ClearFlags()
    {
        Flags = ImGuiNextItemDataFlags_None;
        ItemFlags = ImGuiItemFlags_None;
    } // Also cleared manually by ItemAdd()!
};