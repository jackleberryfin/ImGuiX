#pragma once

#include "Basic/ImTypeDefs.h"

struct ImGuiDataTypeStorage
{
    ImU8 Data[8]; // Opaque storage to fit any data up to ImGuiDataType_COUNT
};