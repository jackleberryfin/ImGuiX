#pragma once

#include "Basic/ImVector.h"
#include "Basic/ImTypeDefs.h"
#include "Basic/ImEnum.h"

#include "ImGuiKeyRoutingData.h"

// Routing table: maintain a desired owner for each possible key-chord (key + mods), and setup owner in NewFrame() when mods are matching.
// Stored in main context (1 instance)
struct ImGuiKeyRoutingTable
{
    ImGuiKeyRoutingIndex Index[ImGuiKey_NamedKey_COUNT]; // Index of first entry in Entries[]
    ImVector<ImGuiKeyRoutingData> Entries;
    ImVector<ImGuiKeyRoutingData> EntriesNext; // Double-buffer to avoid reallocation (could use a shared buffer)

    ImGuiKeyRoutingTable() { Clear(); }
    void Clear()
    {
        for (int n = 0; n < IM_ARRAYSIZE(Index); n++)
            Index[n] = -1;
        Entries.clear();
        EntriesNext.clear();
    }
};