#pragma once

#include "Basic/ImTypes.h"
#include "Basic/ImVec4.h"

struct ImDrawCmdHeader {
    ImVec4 ClipRect;
    ImTextureID TextureId;
    unsigned int VtxOffset;
};