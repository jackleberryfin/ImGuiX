#pragma once

#include "Basic/ImVec4.h"
#include "Basic/ImTypeDefs.h"

struct ImDrawCmdHeader
{
    ImVec4 ClipRect;
    ImTextureID TextureId;
    unsigned int VtxOffset;
};