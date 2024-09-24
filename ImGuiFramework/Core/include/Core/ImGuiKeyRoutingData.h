#pragma once

#include "Basic/ImTypeDefs.h"

// Routing table entry (sizeof() == 16 bytes)
struct ImGuiKeyRoutingData
{
    ImGuiKeyRoutingIndex NextEntryIndex;
    ImU16 Mods;            // Technically we'd only need 4-bits but for simplify we store ImGuiMod_ values which need 16-bits.
    ImU8 RoutingCurrScore; // [DEBUG] For debug display
    ImU8 RoutingNextScore; // Lower is better (0: perfect score)
    ImGuiID RoutingCurr;
    ImGuiID RoutingNext;

    ImGuiKeyRoutingData()
    {
        NextEntryIndex = -1;
        Mods = 0;
        RoutingCurrScore = RoutingNextScore = 255;
        RoutingCurr = RoutingNext = ImGuiKeyOwner_NoOwner;
    }
};