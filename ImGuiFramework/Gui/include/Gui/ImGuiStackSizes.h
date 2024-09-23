#pragma once

#include <memory>

#include "ImGuiContext.h"

// sizeof() = 18
struct IMGUI_API ImGuiStackSizes
{
    short SizeOfIDStack;
    short SizeOfColorStack;
    short SizeOfStyleVarStack;
    short SizeOfFontStack;
    short SizeOfFocusScopeStack;
    short SizeOfGroupStack;
    short SizeOfItemFlagsStack;
    short SizeOfBeginPopupStack;
    short SizeOfDisabledStack;

    ImGuiStackSizes() { memset(this, 0, sizeof(*this)); }
    void SetToContextState(ImGuiContext *ctx);
    void CompareWithContextState(ImGuiContext *ctx);
};