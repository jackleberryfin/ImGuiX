#pragma once

#include "ImGui.h"

template <typename T> void IM_DELETE(T* p) {
    if (p) {
        p->~T();
        ImGui::MemFree(p);
    }
}

// Bit array for named keys
typedef ImBitArray<ImGuiKey_NamedKey_COUNT, -ImGuiKey_NamedKey_BEGIN> ImBitArrayForNamedKeys;