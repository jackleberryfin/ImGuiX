#pragma once

#include "Basic/ImTypes.h"
#include "Basic/ImVector.h"

#include "ImDrawCmd.h"

// [Internal] For use by ImDrawListSplitter
struct ImDrawChannel {
    ImVector<ImDrawCmd> _CmdBuffer;
    ImVector<ImDrawIdx> _IdxBuffer;
};