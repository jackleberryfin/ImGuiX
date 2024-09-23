#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"
#include "Basic/ImBitArray.h"
#include "Basic/ImRect.h"
#include "Basic/ImSpan.h"

#include "ImGuiWindow.h"
#include "ImGuiTableTempData.h"
#include "ImGuiTableColumn.h"
#include "ImGuiTableCellData.h"
#include "ImGuiTextBuffer.h"
#include "ImGuiTableInstanceData.h"
#include "ImGuiTableColumnSortSpecs.h"
#include "ImGuiTableSortSpecs.h"

// sizeof() ~ 592 bytes + heap allocs described in TableBeginInitMemory()
struct IMGUI_API ImGuiTable
{
    ImGuiID ID;
    ImGuiTableFlags Flags;
    void *RawData;                                   // Single allocation to hold Columns[], DisplayOrderToIndex[] and RowCellData[]
    ImGuiTableTempData *TempData;                    // Transient data while table is active. Point within g.CurrentTableStack[]
    ImSpan<ImGuiTableColumn> Columns;                // Point within RawData[]
    ImSpan<ImGuiTableColumnIdx> DisplayOrderToIndex; // Point within RawData[]. Store display order of columns (when not reordered, the values are 0...Count-1)
    ImSpan<ImGuiTableCellData> RowCellData;          // Point within RawData[]. Store cells background requests for current row.
    ImBitArrayPtr EnabledMaskByDisplayOrder;         // Column DisplayOrder -> IsEnabled map
    ImBitArrayPtr EnabledMaskByIndex;                // Column Index -> IsEnabled map (== not hidden by user/api) in a format adequate for iterating column without touching cold data
    ImBitArrayPtr VisibleMaskByIndex;                // Column Index -> IsVisibleX|IsVisibleY map (== not hidden by user/api && not hidden by scrolling/cliprect)
    ImGuiTableFlags SettingsLoadedFlags;             // Which data were loaded from the .ini file (e.g. when order is not altered we won't save order)
    int SettingsOffset;                              // Offset in g.SettingsTables
    int LastFrameActive;
    int ColumnsCount; // Number of columns declared in BeginTable()
    int CurrentRow;
    int CurrentColumn;
    ImS16 InstanceCurrent;    // Count of BeginTable() calls with same ID in the same frame (generally 0). This is a little bit similar to BeginCount for a window, but multiple table with same ID look are multiple tables, they are just synched.
    ImS16 InstanceInteracted; // Mark which instance (generally 0) of the same ID is being interacted with
    float RowPosY1;
    float RowPosY2;
    float RowMinHeight;    // Height submitted to TableNextRow()
    float RowCellPaddingY; // Top and bottom padding. Reloaded during row change.
    float RowTextBaseline;
    float RowIndentOffsetX;
    ImGuiTableRowFlags RowFlags : 16; // Current row flags, see ImGuiTableRowFlags_
    ImGuiTableRowFlags LastRowFlags : 16;
    int RowBgColorCounter; // Counter for alternating background colors (can be fast-forwarded by e.g clipper), not same as CurrentRow because header rows typically don't increase this.
    ImU32 RowBgColor[2];   // Background color override for current row.
    ImU32 BorderColorStrong;
    ImU32 BorderColorLight;
    float BorderX1;
    float BorderX2;
    float HostIndentX;
    float MinColumnWidth;
    float OuterPaddingX;
    float CellPaddingX;  // Padding from each borders. Locked in BeginTable()/Layout.
    float CellSpacingX1; // Spacing between non-bordered cells. Locked in BeginTable()/Layout.
    float CellSpacingX2;
    float InnerWidth;               // User value passed to BeginTable(), see comments at the top of BeginTable() for details.
    float ColumnsGivenWidth;        // Sum of current column width
    float ColumnsAutoFitWidth;      // Sum of ideal column width in order nothing to be clipped, used for auto-fitting and content width submission in outer window
    float ColumnsStretchSumWeights; // Sum of weight of all enabled stretching columns
    float ResizedColumnNextWidth;
    float ResizeLockMinContentsX2; // Lock minimum contents width while resizing down in order to not create feedback loops. But we allow growing the table.
    float RefScale;                // Reference scale to be able to rescale columns on font/dpi changes.
    float AngledHeadersHeight;     // Set by TableAngledHeadersRow(), used in TableUpdateLayout()
    float AngledHeadersSlope;      // Set by TableAngledHeadersRow(), used in TableUpdateLayout()
    ImRect OuterRect;              // Note: for non-scrolling table, OuterRect.Max.y is often FLT_MAX until EndTable(), unless a height has been specified in BeginTable().
    ImRect InnerRect;              // InnerRect but without decoration. As with OuterRect, for non-scrolling tables, InnerRect.Max.y is
    ImRect WorkRect;
    ImRect InnerClipRect;
    ImRect BgClipRect;                // We use this to cpu-clip cell background color fill, evolve during the frame as we cross frozen rows boundaries
    ImRect Bg0ClipRectForDrawCmd;     // Actual ImDrawCmd clip rect for BG0/1 channel. This tends to be == OuterWindow->ClipRect at BeginTable() because output in BG0/BG1 is cpu-clipped
    ImRect Bg2ClipRectForDrawCmd;     // Actual ImDrawCmd clip rect for BG2 channel. This tends to be a correct, tight-fit, because output to BG2 are done by widgets relying on regular ClipRect.
    ImRect HostClipRect;              // This is used to check if we can eventually merge our columns draw calls into the current draw call of the current window.
    ImRect HostBackupInnerClipRect;   // Backup of InnerWindow->ClipRect during PushTableBackground()/PopTableBackground()
    ImGuiWindow *OuterWindow;         // Parent window for the table
    ImGuiWindow *InnerWindow;         // Window holding the table data (== OuterWindow or a child window)
    ImGuiTextBuffer ColumnsNames;     // Contiguous buffer holding columns names
    ImDrawListSplitter *DrawSplitter; // Shortcut to TempData->DrawSplitter while in table. Isolate draw commands per columns to avoid switching clip rect constantly
    ImGuiTableInstanceData InstanceDataFirst;
    ImVector<ImGuiTableInstanceData> InstanceDataExtra; // FIXME-OPT: Using a small-vector pattern would be good.
    ImGuiTableColumnSortSpecs SortSpecsSingle;
    ImVector<ImGuiTableColumnSortSpecs> SortSpecsMulti; // FIXME-OPT: Using a small-vector pattern would be good.
    ImGuiTableSortSpecs SortSpecs;                      // Public facing sorts specs, this is what we return in TableGetSortSpecs()
    ImGuiTableColumnIdx SortSpecsCount;
    ImGuiTableColumnIdx ColumnsEnabledCount;        // Number of enabled columns (<= ColumnsCount)
    ImGuiTableColumnIdx ColumnsEnabledFixedCount;   // Number of enabled columns using fixed width (<= ColumnsCount)
    ImGuiTableColumnIdx DeclColumnsCount;           // Count calls to TableSetupColumn()
    ImGuiTableColumnIdx AngledHeadersCount;         // Count columns with angled headers
    ImGuiTableColumnIdx HoveredColumnBody;          // Index of column whose visible region is being hovered. Important: == ColumnsCount when hovering empty region after the right-most column!
    ImGuiTableColumnIdx HoveredColumnBorder;        // Index of column whose right-border is being hovered (for resizing).
    ImGuiTableColumnIdx HighlightColumnHeader;      // Index of column which should be highlighted.
    ImGuiTableColumnIdx AutoFitSingleColumn;        // Index of single column requesting auto-fit.
    ImGuiTableColumnIdx ResizedColumn;              // Index of column being resized. Reset when InstanceCurrent==0.
    ImGuiTableColumnIdx LastResizedColumn;          // Index of column being resized from previous frame.
    ImGuiTableColumnIdx HeldHeaderColumn;           // Index of column header being held.
    ImGuiTableColumnIdx ReorderColumn;              // Index of column being reordered. (not cleared)
    ImGuiTableColumnIdx ReorderColumnDir;           // -1 or +1
    ImGuiTableColumnIdx LeftMostEnabledColumn;      // Index of left-most non-hidden column.
    ImGuiTableColumnIdx RightMostEnabledColumn;     // Index of right-most non-hidden column.
    ImGuiTableColumnIdx LeftMostStretchedColumn;    // Index of left-most stretched column.
    ImGuiTableColumnIdx RightMostStretchedColumn;   // Index of right-most stretched column.
    ImGuiTableColumnIdx ContextPopupColumn;         // Column right-clicked on, of -1 if opening context menu from a neutral/empty spot
    ImGuiTableColumnIdx FreezeRowsRequest;          // Requested frozen rows count
    ImGuiTableColumnIdx FreezeRowsCount;            // Actual frozen row count (== FreezeRowsRequest, or == 0 when no scrolling offset)
    ImGuiTableColumnIdx FreezeColumnsRequest;       // Requested frozen columns count
    ImGuiTableColumnIdx FreezeColumnsCount;         // Actual frozen columns count (== FreezeColumnsRequest, or == 0 when no scrolling offset)
    ImGuiTableColumnIdx RowCellDataCurrent;         // Index of current RowCellData[] entry in current row
    ImGuiTableDrawChannelIdx DummyDrawChannel;      // Redirect non-visible columns here.
    ImGuiTableDrawChannelIdx Bg2DrawChannelCurrent; // For Selectable() and other widgets drawing across columns after the freezing line. Index within DrawSplitter.Channels[]
    ImGuiTableDrawChannelIdx Bg2DrawChannelUnfrozen;
    bool IsLayoutLocked; // Set by TableUpdateLayout() which is called when beginning the first row.
    bool IsInsideRow;    // Set when inside TableBeginRow()/TableEndRow().
    bool IsInitializing;
    bool IsSortSpecsDirty;
    bool IsUsingHeaders;            // Set when the first row had the ImGuiTableRowFlags_Headers flag.
    bool IsContextPopupOpen;        // Set when default context menu is open (also see: ContextPopupColumn, InstanceInteracted).
    bool DisableDefaultContextMenu; // Disable default context menu contents. You may submit your own using TableBeginContextMenuPopup()/EndPopup()
    bool IsSettingsRequestLoad;
    bool IsSettingsDirty;       // Set when table settings have changed and needs to be reported into ImGuiTableSetttings data.
    bool IsDefaultDisplayOrder; // Set when display order is unchanged from default (DisplayOrder contains 0...Count-1)
    bool IsResetAllRequest;
    bool IsResetDisplayOrderRequest;
    bool IsUnfrozenRows;        // Set when we got past the frozen row.
    bool IsDefaultSizingPolicy; // Set if user didn't explicitly set a sizing policy in BeginTable()
    bool IsActiveIdAliveBeforeTable;
    bool IsActiveIdInTable;
    bool HasScrollbarYCurr; // Whether ANY instance of this table had a vertical scrollbar during the current frame.
    bool HasScrollbarYPrev; // Whether ANY instance of this table had a vertical scrollbar during the previous.
    bool MemoryCompacted;
    bool HostSkipItems; // Backup of InnerWindow->SkipItem at the end of BeginTable(), because we will overwrite InnerWindow->SkipItem on a per-column basis

    ImGuiTable()
    {
        memset(this, 0, sizeof(*this));
        LastFrameActive = -1;
    }
    ~ImGuiTable()
    {
        // JACK_TODO: Enable - IM_FREE(RawData);
    }
};