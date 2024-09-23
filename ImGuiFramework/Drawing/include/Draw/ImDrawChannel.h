#pragma once

#include "Basic/ImVector.h"
#include "Basic/ImTypeDefs.h"

#include "ImDrawCmd.h"

// [Internal] For use by ImDrawListSplitter
struct ImDrawChannel
{
    ImVector<ImDrawCmd> _CmdBuffer;
    ImVector<ImDrawIdx> _IdxBuffer;
};