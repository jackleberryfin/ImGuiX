#pragma once

#include "Basic/ImVec2.h"

// Resizing callback data to apply custom constraint. As enabled by SetNextWindowSizeConstraints(). Callback is called during the next Begin().
// NB: For basic min/max size constraint on each axis you don't need to use the callback! The SetNextWindowSizeConstraints() parameters are enough.
struct ImGuiImGuiSizeCallbackData {
    void* UserData;     // Read-only.   What user passed to SetNextWindowSizeConstraints(). Generally store an integer or float in here (need reinterpret_cast<>).
    ImVec2 Pos;         // Read-only.   Window position, for reference.
    ImVec2 CurrentSize; // Read-only.   Current window size.
    ImVec2 DesiredSize; // Read-write.  Desired size, based on user's mouse position. Write to this field to restrain resizing.
};

typedef int (*ImGuiInputTextCallback)(ImGuiInputTextCallbackData* data); // Callback function for ImGui::InputText()
typedef void (*ImGuiSizeCallback)(ImGuiSizeCallbackData* data);          // Callback function for ImGui::SetNextWindowSizeConstraints()