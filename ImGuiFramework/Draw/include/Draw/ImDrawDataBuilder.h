#pragma once

#include <memory>

#include "Basic/ImVector.h"

#include "ImDrawList.h"

struct ImDrawDataBuilder
{
    ImVector<ImDrawList *> *Layers[2]; // Pointers to global layers for: regular, tooltip. LayersP[0] is owned by DrawData.
    ImVector<ImDrawList *> LayerData1;

    ImDrawDataBuilder() { memset(this, 0, sizeof(*this)); }
};