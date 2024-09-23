#pragma once

#include "ImTypeDefs.h"
#include "ImVector.h"
#include "ImDrawChannel.h"

struct ImDrawListSplitter
{
    int _Current;                      // Current channel number (0)
    int _Count;                        // Number of active channels (1+)
    ImVector<ImDrawChannel> _Channels; // Draw channels (not resized down so _Count might be < Channels.Size)

    inline ImDrawListSplitter() { memset(this, 0, sizeof(*this)); }
    inline ~ImDrawListSplitter() { ClearFreeMemory(); }
    inline void Clear()
    {
        _Current = 0;
        _Count = 1;
    } // Do not clear Channels[] so our allocations are reused next frame
    IMGUI_API void ClearFreeMemory();
    IMGUI_API void Split(ImDrawList *draw_list, int count);
    IMGUI_API void Merge(ImDrawList *draw_list);
    IMGUI_API void SetCurrentChannel(ImDrawList *draw_list, int channel_idx);
};