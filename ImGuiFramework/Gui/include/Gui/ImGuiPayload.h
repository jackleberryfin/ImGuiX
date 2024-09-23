#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"

// Data payload for Drag and Drop operations: AcceptDragDropPayload(), GetDragDropPayload()
struct ImGuiPayload
{
    // Members
    void *Data;   // Data (copied and owned by dear imgui)
    int DataSize; // Data size

    // [Internal]
    ImGuiID SourceId;       // Source item id
    ImGuiID SourceParentId; // Source parent id (if available)
    int DataFrameCount;     // Data timestamp
    char DataType[32 + 1];  // Data type tag (short user-supplied string, 32 characters max)
    bool Preview;           // Set when AcceptDragDropPayload() was called and mouse has been hovering the target item (nb: handle overlapping drag targets)
    bool Delivery;          // Set when AcceptDragDropPayload() was called and mouse button is released over the target item.

    ImGuiPayload() { Clear(); }
    void Clear()
    {
        SourceId = SourceParentId = 0;
        Data = NULL;
        DataSize = 0;
        memset(DataType, 0, sizeof(DataType));
        DataFrameCount = -1;
        Preview = Delivery = false;
    }
    bool IsDataType(const char *type) const { return DataFrameCount != -1 && strcmp(type, DataType) == 0; }
    bool IsPreview() const { return Preview; }
    bool IsDelivery() const { return Delivery; }
};