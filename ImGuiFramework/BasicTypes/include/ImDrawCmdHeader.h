#pragma once

#include "ImVec4.h"
#include "ImTypeDefs.h"

struct ImDrawCmdHeader
{
    ImVec4 ClipRect;
    ImTextureID TextureId;
    unsigned int VtxOffset;
};