#pragma once

#include <memory>

#include "Basic/Imvec2.h"

// (Optional) Support for IME (Input Method Editor) via the platform_io.Platform_SetImeDataFn() function.
struct ImGuiPlatformImeData
{
    bool WantVisible;      // A widget wants the IME to be visible
    ImVec2 InputPos;       // Position of the input cursor
    float InputLineHeight; // Line height

    ImGuiPlatformImeData() { memset(this, 0, sizeof(*this)); }
};