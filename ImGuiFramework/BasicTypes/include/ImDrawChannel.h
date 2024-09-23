#pragma once

#include "ImVector.h"
#include "ImDrawCmd.h"
#include "ImTypeDefs.h"

// [Internal] For use by ImDrawListSplitter
struct ImDrawChannel
{
    ImVector<ImDrawCmd> _CmdBuffer;
    ImVector<ImDrawIdx> _IdxBuffer;
};