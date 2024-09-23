#pragma once

#include "ImFontAtlas.h"

// This structure is likely to evolve as we add support for incremental atlas updates
struct ImFontBuilderIO
{
    bool (*FontBuilder_Build)(ImFontAtlas *atlas);
};