#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"
#include "Basic/ImRect.h"

// [Internal] sizeof() ~ 112
// We use the terminology "Enabled" to refer to a column that is not Hidden by user/api.
// We use the terminology "Clipped" to refer to a column that is out of sight because of scrolling/clipping.
// This is in contrast with some user-facing api such as IsItemVisible() / IsRectVisible() which use "Visible" to mean "not clipped".
struct ImGuiTableColumn
{
    ImGuiTableColumnFlags Flags; // Flags after some patching (not directly same as provided by user). See ImGuiTableColumnFlags_
    float WidthGiven;            // Final/actual width visible == (MaxX - MinX), locked in TableUpdateLayout(). May be > WidthRequest to honor minimum width, may be < WidthRequest to honor shrinking columns down in tight space.
    float MinX;                  // Absolute positions
    float MaxX;
    float WidthRequest;             // Master width absolute value when !(Flags & _WidthStretch). When Stretch this is derived every frame from StretchWeight in TableUpdateLayout()
    float WidthAuto;                // Automatic width
    float WidthMax;                 // Maximum width (FIXME: overwritten by each instance)
    float StretchWeight;            // Master width weight when (Flags & _WidthStretch). Often around ~1.0f initially.
    float InitStretchWeightOrWidth; // Value passed to TableSetupColumn(). For Width it is a content width (_without padding_).
    ImRect ClipRect;                // Clipping rectangle for the column
    ImGuiID UserID;                 // Optional, value passed to TableSetupColumn()
    float WorkMinX;                 // Contents region min ~(MinX + CellPaddingX + CellSpacingX1) == cursor start position when entering column
    float WorkMaxX;                 // Contents region max ~(MaxX - CellPaddingX - CellSpacingX2)
    float ItemWidth;                // Current item width for the column, preserved across rows
    float ContentMaxXFrozen;        // Contents maximum position for frozen rows (apart from headers), from which we can infer content width.
    float ContentMaxXUnfrozen;
    float ContentMaxXHeadersUsed; // Contents maximum position for headers rows (regardless of freezing). TableHeader() automatically softclip itself + report ideal desired size, to avoid creating extraneous draw calls
    float ContentMaxXHeadersIdeal;
    ImS16 NameOffset;                             // Offset into parent ColumnsNames[]
    ImGuiTableColumnIdx DisplayOrder;             // Index within Table's IndexToDisplayOrder[] (column may be reordered by users)
    ImGuiTableColumnIdx IndexWithinEnabledSet;    // Index within enabled/visible set (<= IndexToDisplayOrder)
    ImGuiTableColumnIdx PrevEnabledColumn;        // Index of prev enabled/visible column within Columns[], -1 if first enabled/visible column
    ImGuiTableColumnIdx NextEnabledColumn;        // Index of next enabled/visible column within Columns[], -1 if last enabled/visible column
    ImGuiTableColumnIdx SortOrder;                // Index of this column within sort specs, -1 if not sorting on this column, 0 for single-sort, may be >0 on multi-sort
    ImGuiTableDrawChannelIdx DrawChannelCurrent;  // Index within DrawSplitter.Channels[]
    ImGuiTableDrawChannelIdx DrawChannelFrozen;   // Draw channels for frozen rows (often headers)
    ImGuiTableDrawChannelIdx DrawChannelUnfrozen; // Draw channels for unfrozen rows
    bool IsEnabled;                               // IsUserEnabled && (Flags & ImGuiTableColumnFlags_Disabled) == 0
    bool IsUserEnabled;                           // Is the column not marked Hidden by the user? (unrelated to being off view, e.g. clipped by scrolling).
    bool IsUserEnabledNextFrame;
    bool IsVisibleX; // Is actually in view (e.g. overlapping the host window clipping rectangle, not scrolled).
    bool IsVisibleY;
    bool IsRequestOutput; // Return value for TableSetColumnIndex() / TableNextColumn(): whether we request user to output contents or not.
    bool IsSkipItems;     // Do we want item submissions to this column to be completely ignored (no layout will happen).
    bool IsPreserveWidthAuto;
    ImS8 NavLayerCurrent;              // ImGuiNavLayer in 1 byte
    ImU8 AutoFitQueue;                 // Queue of 8 values for the next 8 frames to request auto-fit
    ImU8 CannotSkipItemsQueue;         // Queue of 8 values for the next 8 frames to disable Clipped/SkipItem
    ImU8 SortDirection : 2;            // ImGuiSortDirection_Ascending or ImGuiSortDirection_Descending
    ImU8 SortDirectionsAvailCount : 2; // Number of available sort directions (0 to 3)
    ImU8 SortDirectionsAvailMask : 4;  // Mask of available sort directions (1-bit each)
    ImU8 SortDirectionsAvailList;      // Ordered list of available sort directions (2-bits each, total 8-bits)

    ImGuiTableColumn()
    {
        memset(this, 0, sizeof(*this));
        StretchWeight = WidthRequest = -1.0f;
        NameOffset = -1;
        DisplayOrder = IndexWithinEnabledSet = -1;
        PrevEnabledColumn = NextEnabledColumn = -1;
        SortOrder = -1;
        SortDirection = ImGuiSortDirection_None;
        DrawChannelCurrent = DrawChannelFrozen = DrawChannelUnfrozen = (ImU8)-1;
    }
};