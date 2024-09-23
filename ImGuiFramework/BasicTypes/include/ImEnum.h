#pragma once

#include "ImTypeDefs.h"

// Flags for ImGui::Begin()
// (Those are per-window flags. There are shared flags in ImGuiIO: io.ConfigWindowsResizeFromEdges and io.ConfigWindowsMoveFromTitleBarOnly)
enum ImGuiWindowFlags_
{
    ImGuiWindowFlags_None = 0,
    ImGuiWindowFlags_NoTitleBar = 1 << 0,                 // Disable title-bar
    ImGuiWindowFlags_NoResize = 1 << 1,                   // Disable user resizing with the lower-right grip
    ImGuiWindowFlags_NoMove = 1 << 2,                     // Disable user moving the window
    ImGuiWindowFlags_NoScrollbar = 1 << 3,                // Disable scrollbars (window can still scroll with mouse or programmatically)
    ImGuiWindowFlags_NoScrollWithMouse = 1 << 4,          // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    ImGuiWindowFlags_NoCollapse = 1 << 5,                 // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
    ImGuiWindowFlags_AlwaysAutoResize = 1 << 6,           // Resize every window to its content every frame
    ImGuiWindowFlags_NoBackground = 1 << 7,               // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    ImGuiWindowFlags_NoSavedSettings = 1 << 8,            // Never load/save settings in .ini file
    ImGuiWindowFlags_NoMouseInputs = 1 << 9,              // Disable catching mouse, hovering test with pass through.
    ImGuiWindowFlags_MenuBar = 1 << 10,                   // Has a menu-bar
    ImGuiWindowFlags_HorizontalScrollbar = 1 << 11,       // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12,        // Disable taking focus when transitioning from hidden to visible state
    ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13,     // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14,   // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15, // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    ImGuiWindowFlags_NoNavInputs = 1 << 16,               // No gamepad/keyboard navigation within the window
    ImGuiWindowFlags_NoNavFocus = 1 << 17,                // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    ImGuiWindowFlags_UnsavedDocument = 1 << 18,           // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    ImGuiWindowFlags_NoDocking = 1 << 19,                 // Disable docking of this window
    ImGuiWindowFlags_NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
    ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
    ImGuiWindowFlags_NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,

    // [Internal]
    ImGuiWindowFlags_ChildWindow = 1 << 24,  // Don't use! For internal use by BeginChild()
    ImGuiWindowFlags_Tooltip = 1 << 25,      // Don't use! For internal use by BeginTooltip()
    ImGuiWindowFlags_Popup = 1 << 26,        // Don't use! For internal use by BeginPopup()
    ImGuiWindowFlags_Modal = 1 << 27,        // Don't use! For internal use by BeginPopupModal()
    ImGuiWindowFlags_ChildMenu = 1 << 28,    // Don't use! For internal use by BeginMenu()
    ImGuiWindowFlags_DockNodeHost = 1 << 29, // Don't use! For internal use by Begin()/NewFrame()

// Obsolete names
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 30, // Obsoleted in 1.90.0: Use ImGuiChildFlags_AlwaysUseWindowPadding in BeginChild() call.
    ImGuiWindowFlags_NavFlattened = 1 << 31,           // Obsoleted in 1.90.9: Use ImGuiChildFlags_NavFlattened in BeginChild() call.
#endif
};

// Flags for ImGui::BeginChild()
// (Legacy: bit 0 must always correspond to ImGuiChildFlags_Borders to be backward compatible with old API using 'bool border = false'.
// About using AutoResizeX/AutoResizeY flags:
// - May be combined with SetNextWindowSizeConstraints() to set a min/max size for each axis (see "Demo->Child->Auto-resize with Constraints").
// - Size measurement for a given axis is only performed when the child window is within visible boundaries, or is just appearing.
//   - This allows BeginChild() to return false when not within boundaries (e.g. when scrolling), which is more optimal. BUT it won't update its auto-size while clipped.
//     While not perfect, it is a better default behavior as the always-on performance gain is more valuable than the occasional "resizing after becoming visible again" glitch.
//   - You may also use ImGuiChildFlags_AlwaysAutoResize to force an update even when child window is not in view.
//     HOWEVER PLEASE UNDERSTAND THAT DOING SO WILL PREVENT BeginChild() FROM EVER RETURNING FALSE, disabling benefits of coarse clipping.
enum ImGuiChildFlags_
{
    ImGuiChildFlags_None = 0,
    ImGuiChildFlags_Borders = 1 << 0,                // Show an outer border and enable WindowPadding. (IMPORTANT: this is always == 1 == true for legacy reason)
    ImGuiChildFlags_AlwaysUseWindowPadding = 1 << 1, // Pad with style.WindowPadding even if no border are drawn (no padding by default for non-bordered child windows because it makes more sense)
    ImGuiChildFlags_ResizeX = 1 << 2,                // Allow resize from right border (layout direction). Enable .ini saving (unless ImGuiWindowFlags_NoSavedSettings passed to window flags)
    ImGuiChildFlags_ResizeY = 1 << 3,                // Allow resize from bottom border (layout direction). "
    ImGuiChildFlags_AutoResizeX = 1 << 4,            // Enable auto-resizing width. Read "IMPORTANT: Size measurement" details above.
    ImGuiChildFlags_AutoResizeY = 1 << 5,            // Enable auto-resizing height. Read "IMPORTANT: Size measurement" details above.
    ImGuiChildFlags_AlwaysAutoResize = 1 << 6,       // Combined with AutoResizeX/AutoResizeY. Always measure size even when child is hidden, always return true, always disable clipping optimization! NOT RECOMMENDED.
    ImGuiChildFlags_FrameStyle = 1 << 7,             // Style the child window like a framed item: use FrameBg, FrameRounding, FrameBorderSize, FramePadding instead of ChildBg, ChildRounding, ChildBorderSize, WindowPadding.
    ImGuiChildFlags_NavFlattened = 1 << 8,           // [BETA] Share focus scope, allow gamepad/keyboard navigation to cross over parent border to this child or between sibling child windows.

// Obsolete names
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiChildFlags_Border = ImGuiChildFlags_Borders, // Renamed in 1.91.1 (August 2024) for consistency.
#endif
};

// Flags for ImGui::PushItemFlag()
// (Those are shared by all items)
enum ImGuiItemFlags_
{
    ImGuiItemFlags_None = 0,                   // (Default)
    ImGuiItemFlags_NoTabStop = 1 << 0,         // false    // Disable keyboard tabbing. This is a "lighter" version of ImGuiItemFlags_NoNav.
    ImGuiItemFlags_NoNav = 1 << 1,             // false    // Disable any form of focusing (keyboard/gamepad directional navigation and SetKeyboardFocusHere() calls).
    ImGuiItemFlags_NoNavDefaultFocus = 1 << 2, // false    // Disable item being a candidate for default focus (e.g. used by title bar items).
    ImGuiItemFlags_ButtonRepeat = 1 << 3,      // false    // Any button-like behavior will have repeat mode enabled (based on io.KeyRepeatDelay and io.KeyRepeatRate values). Note that you can also call IsItemActive() after any button to tell if it is being held.
    ImGuiItemFlags_AutoClosePopups = 1 << 4,   // true     // MenuItem()/Selectable() automatically close their parent popup window.
    ImGuiItemFlags_AllowDuplicateId = 1 << 5,  // false    // Allow submitting an item with the same identifier as an item already submitted this frame without triggering a warning tooltip if io.ConfigDebugHighlightIdConflicts is set.
};

// Flags for ImGui::InputText()
// (Those are per-item flags. There are shared flags in ImGuiIO: io.ConfigInputTextCursorBlink and io.ConfigInputTextEnterKeepActive)
enum ImGuiInputTextFlags_
{
    // Basic filters (also see ImGuiInputTextFlags_CallbackCharFilter)
    ImGuiInputTextFlags_None = 0,
    ImGuiInputTextFlags_CharsDecimal = 1 << 0,     // Allow 0123456789.+-*/
    ImGuiInputTextFlags_CharsHexadecimal = 1 << 1, // Allow 0123456789ABCDEFabcdef
    ImGuiInputTextFlags_CharsScientific = 1 << 2,  // Allow 0123456789.+-*/eE (Scientific notation input)
    ImGuiInputTextFlags_CharsUppercase = 1 << 3,   // Turn a..z into A..Z
    ImGuiInputTextFlags_CharsNoBlank = 1 << 4,     // Filter out spaces, tabs

    // Inputs
    ImGuiInputTextFlags_AllowTabInput = 1 << 5,       // Pressing TAB input a '\t' character into the text field
    ImGuiInputTextFlags_EnterReturnsTrue = 1 << 6,    // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
    ImGuiInputTextFlags_EscapeClearsAll = 1 << 7,     // Escape key clears content if not empty, and deactivate otherwise (contrast to default behavior of Escape to revert)
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 8, // In multi-line mode, validate with Enter, add new line with Ctrl+Enter (default is opposite: validate with Ctrl+Enter, add line with Enter).

    // Other options
    ImGuiInputTextFlags_ReadOnly = 1 << 9,            // Read-only mode
    ImGuiInputTextFlags_Password = 1 << 10,           // Password mode, display all characters as '*', disable copy
    ImGuiInputTextFlags_AlwaysOverwrite = 1 << 11,    // Overwrite mode
    ImGuiInputTextFlags_AutoSelectAll = 1 << 12,      // Select entire text when first taking mouse focus
    ImGuiInputTextFlags_ParseEmptyRefVal = 1 << 13,   // InputFloat(), InputInt(), InputScalar() etc. only: parse empty string as zero value.
    ImGuiInputTextFlags_DisplayEmptyRefVal = 1 << 14, // InputFloat(), InputInt(), InputScalar() etc. only: when value is zero, do not display it. Generally used with ImGuiInputTextFlags_ParseEmptyRefVal.
    ImGuiInputTextFlags_NoHorizontalScroll = 1 << 15, // Disable following the cursor horizontally
    ImGuiInputTextFlags_NoUndoRedo = 1 << 16,         // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().

    // Callback features
    ImGuiInputTextFlags_CallbackCompletion = 1 << 17, // Callback on pressing TAB (for completion handling)
    ImGuiInputTextFlags_CallbackHistory = 1 << 18,    // Callback on pressing Up/Down arrows (for history handling)
    ImGuiInputTextFlags_CallbackAlways = 1 << 19,     // Callback on each iteration. User code may query cursor position, modify text buffer.
    ImGuiInputTextFlags_CallbackCharFilter = 1 << 20, // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
    ImGuiInputTextFlags_CallbackResize = 1 << 21,     // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
    ImGuiInputTextFlags_CallbackEdit = 1 << 22,       // Callback on any edit (note that InputText() already returns true on edit, the callback is useful mainly to manipulate the underlying buffer while focus is active)

    // Obsolete names
    // ImGuiInputTextFlags_AlwaysInsertMode  = ImGuiInputTextFlags_AlwaysOverwrite   // [renamed in 1.82] name was not matching behavior
};

// Flags for ImGui::TreeNodeEx(), ImGui::CollapsingHeader*()
enum ImGuiTreeNodeFlags_
{
    ImGuiTreeNodeFlags_None = 0,
    ImGuiTreeNodeFlags_Selected = 1 << 0,              // Draw as selected
    ImGuiTreeNodeFlags_Framed = 1 << 1,                // Draw frame with background (e.g. for CollapsingHeader)
    ImGuiTreeNodeFlags_AllowOverlap = 1 << 2,          // Hit testing to allow subsequent widgets to overlap this one
    ImGuiTreeNodeFlags_NoTreePushOnOpen = 1 << 3,      // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
    ImGuiTreeNodeFlags_NoAutoOpenOnLog = 1 << 4,       // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
    ImGuiTreeNodeFlags_DefaultOpen = 1 << 5,           // Default node to be open
    ImGuiTreeNodeFlags_OpenOnDoubleClick = 1 << 6,     // Open on double-click instead of simple click (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
    ImGuiTreeNodeFlags_OpenOnArrow = 1 << 7,           // Open when clicking on the arrow part (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
    ImGuiTreeNodeFlags_Leaf = 1 << 8,                  // No collapsing, no arrow (use as a convenience for leaf nodes).
    ImGuiTreeNodeFlags_Bullet = 1 << 9,                // Display a bullet instead of arrow. IMPORTANT: node can still be marked open/close if you don't set the _Leaf flag!
    ImGuiTreeNodeFlags_FramePadding = 1 << 10,         // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding() before the node.
    ImGuiTreeNodeFlags_SpanAvailWidth = 1 << 11,       // Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line without using AllowOverlap mode.
    ImGuiTreeNodeFlags_SpanFullWidth = 1 << 12,        // Extend hit box to the left-most and right-most edges (cover the indent area).
    ImGuiTreeNodeFlags_SpanTextWidth = 1 << 13,        // Narrow hit box + narrow hovering highlight, will only cover the label text.
    ImGuiTreeNodeFlags_SpanAllColumns = 1 << 14,       // Frame will span all columns of its container table (text will still fit in current column)
    ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 15, // (WIP) Nav: left direction may move to this TreeNode() from any of its child (items submitted between TreeNode and TreePop)
    // ImGuiTreeNodeFlags_NoScrollOnOpen     = 1 << 16,  // FIXME: TODO: Disable automatic scroll on TreePop() if node got just open and contents is not visible
    ImGuiTreeNodeFlags_CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog,

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiTreeNodeFlags_AllowItemOverlap = ImGuiTreeNodeFlags_AllowOverlap, // Renamed in 1.89.7
#endif
};

// Flags for OpenPopup*(), BeginPopupContext*(), IsPopupOpen() functions.
// - To be backward compatible with older API which took an 'int mouse_button = 1' argument instead of 'ImGuiPopupFlags flags',
//   we need to treat small flags values as a mouse button index, so we encode the mouse button in the first few bits of the flags.
//   It is therefore guaranteed to be legal to pass a mouse button index in ImGuiPopupFlags.
// - For the same reason, we exceptionally default the ImGuiPopupFlags argument of BeginPopupContextXXX functions to 1 instead of 0.
//   IMPORTANT: because the default parameter is 1 (==ImGuiPopupFlags_MouseButtonRight), if you rely on the default parameter
//   and want to use another flag, you need to pass in the ImGuiPopupFlags_MouseButtonRight flag explicitly.
// - Multiple buttons currently cannot be combined/or-ed in those functions (we could allow it later).
enum ImGuiPopupFlags_
{
    ImGuiPopupFlags_None = 0,
    ImGuiPopupFlags_MouseButtonLeft = 0,   // For BeginPopupContext*(): open on Left Mouse release. Guaranteed to always be == 0 (same as ImGuiMouseButton_Left)
    ImGuiPopupFlags_MouseButtonRight = 1,  // For BeginPopupContext*(): open on Right Mouse release. Guaranteed to always be == 1 (same as ImGuiMouseButton_Right)
    ImGuiPopupFlags_MouseButtonMiddle = 2, // For BeginPopupContext*(): open on Middle Mouse release. Guaranteed to always be == 2 (same as ImGuiMouseButton_Middle)
    ImGuiPopupFlags_MouseButtonMask_ = 0x1F,
    ImGuiPopupFlags_MouseButtonDefault_ = 1,
    ImGuiPopupFlags_NoReopen = 1 << 5, // For OpenPopup*(), BeginPopupContext*(): don't reopen same popup if already open (won't reposition, won't reinitialize navigation)
    // ImGuiPopupFlags_NoReopenAlwaysNavInit = 1 << 6,   // For OpenPopup*(), BeginPopupContext*(): focus and initialize navigation even when not reopening.
    ImGuiPopupFlags_NoOpenOverExistingPopup = 1 << 7, // For OpenPopup*(), BeginPopupContext*(): don't open if there's already a popup at the same level of the popup stack
    ImGuiPopupFlags_NoOpenOverItems = 1 << 8,         // For BeginPopupContextWindow(): don't return true when hovering items, only when hovering empty space
    ImGuiPopupFlags_AnyPopupId = 1 << 10,             // For IsPopupOpen(): ignore the ImGuiID parameter and test for any popup.
    ImGuiPopupFlags_AnyPopupLevel = 1 << 11,          // For IsPopupOpen(): search/test at any level of the popup stack (default test in the current level)
    ImGuiPopupFlags_AnyPopup = ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel,
};

// Flags for ImGui::Selectable()
enum ImGuiSelectableFlags_
{
    ImGuiSelectableFlags_None = 0,
    ImGuiSelectableFlags_NoAutoClosePopups = 1 << 0, // Clicking this doesn't close parent popup window (overrides ImGuiItemFlags_AutoClosePopups)
    ImGuiSelectableFlags_SpanAllColumns = 1 << 1,    // Frame will span all columns of its container table (text will still fit in current column)
    ImGuiSelectableFlags_AllowDoubleClick = 1 << 2,  // Generate press events on double clicks too
    ImGuiSelectableFlags_Disabled = 1 << 3,          // Cannot be selected, display grayed out text
    ImGuiSelectableFlags_AllowOverlap = 1 << 4,      // (WIP) Hit testing to allow subsequent widgets to overlap this one
    ImGuiSelectableFlags_Highlight = 1 << 5,         // Make the item be displayed as if it is hovered

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiSelectableFlags_DontClosePopups = ImGuiSelectableFlags_NoAutoClosePopups, // Renamed in 1.91.0
    ImGuiSelectableFlags_AllowItemOverlap = ImGuiSelectableFlags_AllowOverlap,     // Renamed in 1.89.7
#endif
};

// Flags for ImGui::BeginCombo()
enum ImGuiComboFlags_
{
    ImGuiComboFlags_None = 0,
    ImGuiComboFlags_PopupAlignLeft = 1 << 0,  // Align the popup toward the left by default
    ImGuiComboFlags_HeightSmall = 1 << 1,     // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    ImGuiComboFlags_HeightRegular = 1 << 2,   // Max ~8 items visible (default)
    ImGuiComboFlags_HeightLarge = 1 << 3,     // Max ~20 items visible
    ImGuiComboFlags_HeightLargest = 1 << 4,   // As many fitting items as possible
    ImGuiComboFlags_NoArrowButton = 1 << 5,   // Display on the preview box without the square arrow button
    ImGuiComboFlags_NoPreview = 1 << 6,       // Display only a square arrow button
    ImGuiComboFlags_WidthFitPreview = 1 << 7, // Width dynamically calculated from preview contents
    ImGuiComboFlags_HeightMask_ = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest,
};

// Flags for ImGui::BeginTabBar()
enum ImGuiTabBarFlags_
{
    ImGuiTabBarFlags_None = 0,
    ImGuiTabBarFlags_Reorderable = 1 << 0,                  // Allow manually dragging tabs to re-order them + New tabs are appended at the end of list
    ImGuiTabBarFlags_AutoSelectNewTabs = 1 << 1,            // Automatically select new tabs when they appear
    ImGuiTabBarFlags_TabListPopupButton = 1 << 2,           // Disable buttons to open the tab list popup
    ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 1 << 3, // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You may handle this behavior manually on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
    ImGuiTabBarFlags_NoTabListScrollingButtons = 1 << 4,    // Disable scrolling buttons (apply when fitting policy is ImGuiTabBarFlags_FittingPolicyScroll)
    ImGuiTabBarFlags_NoTooltip = 1 << 5,                    // Disable tooltips when hovering a tab
    ImGuiTabBarFlags_DrawSelectedOverline = 1 << 6,         // Draw selected overline markers over selected tab
    ImGuiTabBarFlags_FittingPolicyResizeDown = 1 << 7,      // Resize tabs when they don't fit
    ImGuiTabBarFlags_FittingPolicyScroll = 1 << 8,          // Add scroll buttons when tabs don't fit
    ImGuiTabBarFlags_FittingPolicyMask_ = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll,
    ImGuiTabBarFlags_FittingPolicyDefault_ = ImGuiTabBarFlags_FittingPolicyResizeDown,
};

// Flags for ImGui::BeginTabItem()
enum ImGuiTabItemFlags_
{
    ImGuiTabItemFlags_None = 0,
    ImGuiTabItemFlags_UnsavedDocument = 1 << 0,              // Display a dot next to the title + set ImGuiTabItemFlags_NoAssumedClosure.
    ImGuiTabItemFlags_SetSelected = 1 << 1,                  // Trigger flag to programmatically make the tab selected when calling BeginTabItem()
    ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 1 << 2, // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You may handle this behavior manually on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
    ImGuiTabItemFlags_NoPushId = 1 << 3,                     // Don't call PushID()/PopID() on BeginTabItem()/EndTabItem()
    ImGuiTabItemFlags_NoTooltip = 1 << 4,                    // Disable tooltip for the given tab
    ImGuiTabItemFlags_NoReorder = 1 << 5,                    // Disable reordering this tab or having another tab cross over this tab
    ImGuiTabItemFlags_Leading = 1 << 6,                      // Enforce the tab position to the left of the tab bar (after the tab list popup button)
    ImGuiTabItemFlags_Trailing = 1 << 7,                     // Enforce the tab position to the right of the tab bar (before the scrolling buttons)
    ImGuiTabItemFlags_NoAssumedClosure = 1 << 8,             // Tab is selected when trying to close + closure is not immediately assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
};

// Flags for ImGui::IsWindowFocused()
enum ImGuiFocusedFlags_
{
    ImGuiFocusedFlags_None = 0,
    ImGuiFocusedFlags_ChildWindows = 1 << 0,     // Return true if any children of the window is focused
    ImGuiFocusedFlags_RootWindow = 1 << 1,       // Test from root window (top most parent of the current hierarchy)
    ImGuiFocusedFlags_AnyWindow = 1 << 2,        // Return true if any window is focused. Important: If you are trying to tell how to dispatch your low-level inputs, do NOT use this. Use 'io.WantCaptureMouse' instead! Please read the FAQ!
    ImGuiFocusedFlags_NoPopupHierarchy = 1 << 3, // Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
    ImGuiFocusedFlags_DockHierarchy = 1 << 4,    // Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
    ImGuiFocusedFlags_RootAndChildWindows = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows,
};

// Flags for ImGui::IsItemHovered(), ImGui::IsWindowHovered()
// Note: if you are trying to check whether your mouse should be dispatched to Dear ImGui or to your app, you should use 'io.WantCaptureMouse' instead! Please read the FAQ!
// Note: windows with the ImGuiWindowFlags_NoInputs flag are ignored by IsWindowHovered() calls.
enum ImGuiHoveredFlags_
{
    ImGuiHoveredFlags_None = 0,                         // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
    ImGuiHoveredFlags_ChildWindows = 1 << 0,            // IsWindowHovered() only: Return true if any children of the window is hovered
    ImGuiHoveredFlags_RootWindow = 1 << 1,              // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    ImGuiHoveredFlags_AnyWindow = 1 << 2,               // IsWindowHovered() only: Return true if any window is hovered
    ImGuiHoveredFlags_NoPopupHierarchy = 1 << 3,        // IsWindowHovered() only: Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
    ImGuiHoveredFlags_DockHierarchy = 1 << 4,           // IsWindowHovered() only: Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
    ImGuiHoveredFlags_AllowWhenBlockedByPopup = 1 << 5, // Return true even if a popup window is normally blocking access to this item/window
    // ImGuiHoveredFlags_AllowWhenBlockedByModal     = 1 << 6,   // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Unavailable yet.
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 7, // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    ImGuiHoveredFlags_AllowWhenOverlappedByItem = 1 << 8,    // IsItemHovered() only: Return true even if the item uses AllowOverlap mode and is overlapped by another hoverable item.
    ImGuiHoveredFlags_AllowWhenOverlappedByWindow = 1 << 9,  // IsItemHovered() only: Return true even if the position is obstructed or overlapped by another window.
    ImGuiHoveredFlags_AllowWhenDisabled = 1 << 10,           // IsItemHovered() only: Return true even if the item is disabled
    ImGuiHoveredFlags_NoNavOverride = 1 << 11,               // IsItemHovered() only: Disable using gamepad/keyboard navigation state when active, always query mouse
    ImGuiHoveredFlags_AllowWhenOverlapped = ImGuiHoveredFlags_AllowWhenOverlappedByItem | ImGuiHoveredFlags_AllowWhenOverlappedByWindow,
    ImGuiHoveredFlags_RectOnly = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
    ImGuiHoveredFlags_RootAndChildWindows = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows,

    // Tooltips mode
    // - typically used in IsItemHovered() + SetTooltip() sequence.
    // - this is a shortcut to pull flags from 'style.HoverFlagsForTooltipMouse' or 'style.HoverFlagsForTooltipNav' where you can reconfigure desired behavior.
    //   e.g. 'TooltipHoveredFlagsForMouse' defaults to 'ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayShort'.
    // - for frequently actioned or hovered items providing a tooltip, you want may to use ImGuiHoveredFlags_ForTooltip (stationary + delay) so the tooltip doesn't show too often.
    // - for items which main purpose is to be hovered, or items with low affordance, or in less consistent apps, prefer no delay or shorter delay.
    ImGuiHoveredFlags_ForTooltip = 1 << 12, // Shortcut for standard flags when using IsItemHovered() + SetTooltip() sequence.

    // (Advanced) Mouse Hovering delays.
    // - generally you can use ImGuiHoveredFlags_ForTooltip to use application-standardized flags.
    // - use those if you need specific overrides.
    ImGuiHoveredFlags_Stationary = 1 << 13,    // Require mouse to be stationary for style.HoverStationaryDelay (~0.15 sec) _at least one time_. After this, can move on same item/window. Using the stationary test tends to reduces the need for a long delay.
    ImGuiHoveredFlags_DelayNone = 1 << 14,     // IsItemHovered() only: Return true immediately (default). As this is the default you generally ignore this.
    ImGuiHoveredFlags_DelayShort = 1 << 15,    // IsItemHovered() only: Return true after style.HoverDelayShort elapsed (~0.15 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
    ImGuiHoveredFlags_DelayNormal = 1 << 16,   // IsItemHovered() only: Return true after style.HoverDelayNormal elapsed (~0.40 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
    ImGuiHoveredFlags_NoSharedDelay = 1 << 17, // IsItemHovered() only: Disable shared delay system where moving from one item to the next keeps the previous timer for a short time (standard for tooltips with long delays)
};

// Flags for ImGui::DockSpace(), shared/inherited by child nodes.
// (Some flags can be applied to individual nodes directly)
// FIXME-DOCK: Also see ImGuiDockNodeFlagsPrivate_ which may involve using the WIP and internal DockBuilder api.
enum ImGuiDockNodeFlags_
{
    ImGuiDockNodeFlags_None = 0,
    ImGuiDockNodeFlags_KeepAliveOnly = 1 << 0, //       // Don't display the dockspace node but keep it alive. Windows docked into this dockspace node won't be undocked.
    // ImGuiDockNodeFlags_NoCentralNode              = 1 << 1,   //       // Disable Central Node (the node which can stay empty)
    ImGuiDockNodeFlags_NoDockingOverCentralNode = 1 << 2, //       // Disable docking over the Central Node, which will be always kept empty.
    ImGuiDockNodeFlags_PassthruCentralNode = 1 << 3,      //       // Enable passthru dockspace: 1) DockSpace() will render a ImGuiCol_WindowBg background covering everything excepted the Central Node when empty. Meaning the host window should probably use SetNextWindowBgAlpha(0.0f) prior to Begin() when using this. 2) When Central Node is empty: let inputs pass-through + won't display a DockingEmptyBg background. See demo for details.
    ImGuiDockNodeFlags_NoDockingSplit = 1 << 4,           //       // Disable other windows/nodes from splitting this node.
    ImGuiDockNodeFlags_NoResize = 1 << 5,                 // Saved // Disable resizing node using the splitter/separators. Useful with programmatically setup dockspaces.
    ImGuiDockNodeFlags_AutoHideTabBar = 1 << 6,           //       // Tab bar will automatically hide when there is a single window in the dock node.
    ImGuiDockNodeFlags_NoUndocking = 1 << 7,              //       // Disable undocking this node.

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiDockNodeFlags_NoSplit = ImGuiDockNodeFlags_NoDockingSplit,                          // Renamed in 1.90
    ImGuiDockNodeFlags_NoDockingInCentralNode = ImGuiDockNodeFlags_NoDockingOverCentralNode, // Renamed in 1.90
#endif
};

// Flags for ImGui::BeginDragDropSource(), ImGui::AcceptDragDropPayload()
enum ImGuiDragDropFlags_
{
    ImGuiDragDropFlags_None = 0,
    // BeginDragDropSource() flags
    ImGuiDragDropFlags_SourceNoPreviewTooltip = 1 << 0,   // Disable preview tooltip. By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disables this behavior.
    ImGuiDragDropFlags_SourceNoDisableHover = 1 << 1,     // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disables this behavior so you can still call IsItemHovered() on the source item.
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2, // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
    ImGuiDragDropFlags_SourceAllowNullID = 1 << 3,        // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear imgui ecosystem and so we made it explicit.
    ImGuiDragDropFlags_SourceExtern = 1 << 4,             // External source (from outside of dear imgui), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
    ImGuiDragDropFlags_PayloadAutoExpire = 1 << 5,        // Automatically expire the payload if the source cease to be submitted (otherwise payloads are persisting while being dragged)
    ImGuiDragDropFlags_PayloadNoCrossContext = 1 << 6,    // Hint to specify that the payload may not be copied outside current dear imgui context.
    ImGuiDragDropFlags_PayloadNoCrossProcess = 1 << 7,    // Hint to specify that the payload may not be copied outside current process.
    // AcceptDragDropPayload() flags
    ImGuiDragDropFlags_AcceptBeforeDelivery = 1 << 10,                                                                        // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11,                                                                     // Do not draw the default highlight rectangle when hovering over target.
    ImGuiDragDropFlags_AcceptNoPreviewTooltip = 1 << 12,                                                                      // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
    ImGuiDragDropFlags_AcceptPeekOnly = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect, // For peeking ahead and inspecting the payload before delivery.

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiDragDropFlags_SourceAutoExpirePayload = ImGuiDragDropFlags_PayloadAutoExpire, // Renamed in 1.90.9
#endif
};

// Standard Drag and Drop payload types. You can define you own payload types using short strings. Types starting with '_' are defined by Dear ImGui.
#define IMGUI_PAYLOAD_TYPE_COLOR_3F "_COL3F" // float[3]: Standard type for colors, without alpha. User code may use this type.
#define IMGUI_PAYLOAD_TYPE_COLOR_4F "_COL4F" // float[4]: Standard type for colors. User code may use this type.

// A primary data type
enum ImGuiDataType_
{
    ImGuiDataType_S8,     // signed char / char (with sensible compilers)
    ImGuiDataType_U8,     // unsigned char
    ImGuiDataType_S16,    // short
    ImGuiDataType_U16,    // unsigned short
    ImGuiDataType_S32,    // int
    ImGuiDataType_U32,    // unsigned int
    ImGuiDataType_S64,    // long long / __int64
    ImGuiDataType_U64,    // unsigned long long / unsigned __int64
    ImGuiDataType_Float,  // float
    ImGuiDataType_Double, // double
    ImGuiDataType_Bool,   // bool (provided for user convenience, not supported by scalar widgets)
    ImGuiDataType_COUNT
};

// A cardinal direction
enum ImGuiDir : int
{
    ImGuiDir_None = -1,
    ImGuiDir_Left = 0,
    ImGuiDir_Right = 1,
    ImGuiDir_Up = 2,
    ImGuiDir_Down = 3,
    ImGuiDir_COUNT
};

// A sorting direction
enum ImGuiSortDirection : ImU8
{
    ImGuiSortDirection_None = 0,
    ImGuiSortDirection_Ascending = 1, // Ascending = 0->9, A->Z etc.
    ImGuiSortDirection_Descending = 2 // Descending = 9->0, Z->A etc.
};

// Since 1.90, defining IMGUI_DISABLE_OBSOLETE_FUNCTIONS automatically defines IMGUI_DISABLE_OBSOLETE_KEYIO as well.
#if defined(IMGUI_DISABLE_OBSOLETE_FUNCTIONS) && !defined(IMGUI_DISABLE_OBSOLETE_KEYIO)
#define IMGUI_DISABLE_OBSOLETE_KEYIO
#endif

// A key identifier (ImGuiKey_XXX or ImGuiMod_XXX value): can represent Keyboard, Mouse and Gamepad values.
// All our named keys are >= 512. Keys value 0 to 511 are left unused as legacy native/opaque key values (< 1.87).
// Since >= 1.89 we increased typing (went from int to enum), some legacy code may need a cast to ImGuiKey.
// Read details about the 1.87 and 1.89 transition : https://github.com/ocornut/imgui/issues/4921
// Note that "Keys" related to physical keys and are not the same concept as input "Characters", the later are submitted via io.AddInputCharacter().
// The keyboard key enum values are named after the keys on a standard US keyboard, and on other keyboard types the keys reported may not match the keycaps.
enum ImGuiKey : int
{
    // Keyboard
    ImGuiKey_None = 0,
    ImGuiKey_Tab = 512, // == ImGuiKey_NamedKey_BEGIN
    ImGuiKey_LeftArrow,
    ImGuiKey_RightArrow,
    ImGuiKey_UpArrow,
    ImGuiKey_DownArrow,
    ImGuiKey_PageUp,
    ImGuiKey_PageDown,
    ImGuiKey_Home,
    ImGuiKey_End,
    ImGuiKey_Insert,
    ImGuiKey_Delete,
    ImGuiKey_Backspace,
    ImGuiKey_Space,
    ImGuiKey_Enter,
    ImGuiKey_Escape,
    ImGuiKey_LeftCtrl,
    ImGuiKey_LeftShift,
    ImGuiKey_LeftAlt,
    ImGuiKey_LeftSuper,
    ImGuiKey_RightCtrl,
    ImGuiKey_RightShift,
    ImGuiKey_RightAlt,
    ImGuiKey_RightSuper,
    ImGuiKey_Menu,
    ImGuiKey_0,
    ImGuiKey_1,
    ImGuiKey_2,
    ImGuiKey_3,
    ImGuiKey_4,
    ImGuiKey_5,
    ImGuiKey_6,
    ImGuiKey_7,
    ImGuiKey_8,
    ImGuiKey_9,
    ImGuiKey_A,
    ImGuiKey_B,
    ImGuiKey_C,
    ImGuiKey_D,
    ImGuiKey_E,
    ImGuiKey_F,
    ImGuiKey_G,
    ImGuiKey_H,
    ImGuiKey_I,
    ImGuiKey_J,
    ImGuiKey_K,
    ImGuiKey_L,
    ImGuiKey_M,
    ImGuiKey_N,
    ImGuiKey_O,
    ImGuiKey_P,
    ImGuiKey_Q,
    ImGuiKey_R,
    ImGuiKey_S,
    ImGuiKey_T,
    ImGuiKey_U,
    ImGuiKey_V,
    ImGuiKey_W,
    ImGuiKey_X,
    ImGuiKey_Y,
    ImGuiKey_Z,
    ImGuiKey_F1,
    ImGuiKey_F2,
    ImGuiKey_F3,
    ImGuiKey_F4,
    ImGuiKey_F5,
    ImGuiKey_F6,
    ImGuiKey_F7,
    ImGuiKey_F8,
    ImGuiKey_F9,
    ImGuiKey_F10,
    ImGuiKey_F11,
    ImGuiKey_F12,
    ImGuiKey_F13,
    ImGuiKey_F14,
    ImGuiKey_F15,
    ImGuiKey_F16,
    ImGuiKey_F17,
    ImGuiKey_F18,
    ImGuiKey_F19,
    ImGuiKey_F20,
    ImGuiKey_F21,
    ImGuiKey_F22,
    ImGuiKey_F23,
    ImGuiKey_F24,
    ImGuiKey_Apostrophe,   // '
    ImGuiKey_Comma,        // ,
    ImGuiKey_Minus,        // -
    ImGuiKey_Period,       // .
    ImGuiKey_Slash,        // /
    ImGuiKey_Semicolon,    // ;
    ImGuiKey_Equal,        // =
    ImGuiKey_LeftBracket,  // [
    ImGuiKey_Backslash,    // \ (this text inhibit multiline comment caused by backslash)
    ImGuiKey_RightBracket, // ]
    ImGuiKey_GraveAccent,  // `
    ImGuiKey_CapsLock,
    ImGuiKey_ScrollLock,
    ImGuiKey_NumLock,
    ImGuiKey_PrintScreen,
    ImGuiKey_Pause,
    ImGuiKey_Keypad0,
    ImGuiKey_Keypad1,
    ImGuiKey_Keypad2,
    ImGuiKey_Keypad3,
    ImGuiKey_Keypad4,
    ImGuiKey_Keypad5,
    ImGuiKey_Keypad6,
    ImGuiKey_Keypad7,
    ImGuiKey_Keypad8,
    ImGuiKey_Keypad9,
    ImGuiKey_KeypadDecimal,
    ImGuiKey_KeypadDivide,
    ImGuiKey_KeypadMultiply,
    ImGuiKey_KeypadSubtract,
    ImGuiKey_KeypadAdd,
    ImGuiKey_KeypadEnter,
    ImGuiKey_KeypadEqual,
    ImGuiKey_AppBack, // Available on some keyboard/mouses. Often referred as "Browser Back"
    ImGuiKey_AppForward,

    // Gamepad (some of those are analog values, 0.0f to 1.0f)                          // NAVIGATION ACTION
    // (download controller mapping PNG/PSD at http://dearimgui.com/controls_sheets)
    ImGuiKey_GamepadStart,       // Menu (Xbox)      + (Switch)   Start/Options (PS)
    ImGuiKey_GamepadBack,        // View (Xbox)      - (Switch)   Share (PS)
    ImGuiKey_GamepadFaceLeft,    // X (Xbox)         Y (Switch)   Square (PS)        // Tap: Toggle Menu. Hold: Windowing mode (Focus/Move/Resize windows)
    ImGuiKey_GamepadFaceRight,   // B (Xbox)         A (Switch)   Circle (PS)        // Cancel / Close / Exit
    ImGuiKey_GamepadFaceUp,      // Y (Xbox)         X (Switch)   Triangle (PS)      // Text Input / On-screen Keyboard
    ImGuiKey_GamepadFaceDown,    // A (Xbox)         B (Switch)   Cross (PS)         // Activate / Open / Toggle / Tweak
    ImGuiKey_GamepadDpadLeft,    // D-pad Left                                       // Move / Tweak / Resize Window (in Windowing mode)
    ImGuiKey_GamepadDpadRight,   // D-pad Right                                      // Move / Tweak / Resize Window (in Windowing mode)
    ImGuiKey_GamepadDpadUp,      // D-pad Up                                         // Move / Tweak / Resize Window (in Windowing mode)
    ImGuiKey_GamepadDpadDown,    // D-pad Down                                       // Move / Tweak / Resize Window (in Windowing mode)
    ImGuiKey_GamepadL1,          // L Bumper (Xbox)  L (Switch)   L1 (PS)            // Tweak Slower / Focus Previous (in Windowing mode)
    ImGuiKey_GamepadR1,          // R Bumper (Xbox)  R (Switch)   R1 (PS)            // Tweak Faster / Focus Next (in Windowing mode)
    ImGuiKey_GamepadL2,          // L Trig. (Xbox)   ZL (Switch)  L2 (PS) [Analog]
    ImGuiKey_GamepadR2,          // R Trig. (Xbox)   ZR (Switch)  R2 (PS) [Analog]
    ImGuiKey_GamepadL3,          // L Stick (Xbox)   L3 (Switch)  L3 (PS)
    ImGuiKey_GamepadR3,          // R Stick (Xbox)   R3 (Switch)  R3 (PS)
    ImGuiKey_GamepadLStickLeft,  // [Analog]                                         // Move Window (in Windowing mode)
    ImGuiKey_GamepadLStickRight, // [Analog]                                         // Move Window (in Windowing mode)
    ImGuiKey_GamepadLStickUp,    // [Analog]                                         // Move Window (in Windowing mode)
    ImGuiKey_GamepadLStickDown,  // [Analog]                                         // Move Window (in Windowing mode)
    ImGuiKey_GamepadRStickLeft,  // [Analog]
    ImGuiKey_GamepadRStickRight, // [Analog]
    ImGuiKey_GamepadRStickUp,    // [Analog]
    ImGuiKey_GamepadRStickDown,  // [Analog]

    // Aliases: Mouse Buttons (auto-submitted from AddMouseButtonEvent() calls)
    // - This is mirroring the data also written to io.MouseDown[], io.MouseWheel, in a format allowing them to be accessed via standard key API.
    ImGuiKey_MouseLeft,
    ImGuiKey_MouseRight,
    ImGuiKey_MouseMiddle,
    ImGuiKey_MouseX1,
    ImGuiKey_MouseX2,
    ImGuiKey_MouseWheelX,
    ImGuiKey_MouseWheelY,

    // [Internal] Reserved for mod storage
    ImGuiKey_ReservedForModCtrl,
    ImGuiKey_ReservedForModShift,
    ImGuiKey_ReservedForModAlt,
    ImGuiKey_ReservedForModSuper,
    ImGuiKey_COUNT,

    // Keyboard Modifiers (explicitly submitted by backend via AddKeyEvent() calls)
    // - This is mirroring the data also written to io.KeyCtrl, io.KeyShift, io.KeyAlt, io.KeySuper, in a format allowing
    //   them to be accessed via standard key API, allowing calls such as IsKeyPressed(), IsKeyReleased(), querying duration etc.
    // - Code polling every key (e.g. an interface to detect a key press for input mapping) might want to ignore those
    //   and prefer using the real keys (e.g. ImGuiKey_LeftCtrl, ImGuiKey_RightCtrl instead of ImGuiMod_Ctrl).
    // - In theory the value of keyboard modifiers should be roughly equivalent to a logical or of the equivalent left/right keys.
    //   In practice: it's complicated; mods are often provided from different sources. Keyboard layout, IME, sticky keys and
    //   backends tend to interfere and break that equivalence. The safer decision is to relay that ambiguity down to the end-user...
    // - On macOS, we swap Cmd(Super) and Ctrl keys at the time of the io.AddKeyEvent() call.
    ImGuiMod_None = 0,
    ImGuiMod_Ctrl = 1 << 12,  // Ctrl (non-macOS), Cmd (macOS)
    ImGuiMod_Shift = 1 << 13, // Shift
    ImGuiMod_Alt = 1 << 14,   // Option/Menu
    ImGuiMod_Super = 1 << 15, // Windows/Super (non-macOS), Ctrl (macOS)
    ImGuiMod_Mask_ = 0xF000,  // 4-bits

    // [Internal] Prior to 1.87 we required user to fill io.KeysDown[512] using their own native index + the io.KeyMap[] array.
    // We are ditching this method but keeping a legacy path for user code doing e.g. IsKeyPressed(MY_NATIVE_KEY_CODE)
    // If you need to iterate all keys (for e.g. an input mapper) you may use ImGuiKey_NamedKey_BEGIN..ImGuiKey_NamedKey_END.
    ImGuiKey_NamedKey_BEGIN = 512,
    ImGuiKey_NamedKey_END = ImGuiKey_COUNT,
    ImGuiKey_NamedKey_COUNT = ImGuiKey_NamedKey_END - ImGuiKey_NamedKey_BEGIN,
#ifdef IMGUI_DISABLE_OBSOLETE_KEYIO
    ImGuiKey_KeysData_SIZE = ImGuiKey_NamedKey_COUNT,   // Size of KeysData[]: only hold named keys
    ImGuiKey_KeysData_OFFSET = ImGuiKey_NamedKey_BEGIN, // Accesses to io.KeysData[] must use (key - ImGuiKey_KeysData_OFFSET) index.
#else
    ImGuiKey_KeysData_SIZE = ImGuiKey_COUNT, // Size of KeysData[]: hold legacy 0..512 keycodes + named keys
    ImGuiKey_KeysData_OFFSET = 0,            // Accesses to io.KeysData[] must use (key - ImGuiKey_KeysData_OFFSET) index.
#endif

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiMod_Shortcut = ImGuiMod_Ctrl, // Removed in 1.90.7, you can now simply use ImGuiMod_Ctrl
    ImGuiKey_ModCtrl = ImGuiMod_Ctrl,
    ImGuiKey_ModShift = ImGuiMod_Shift,
    ImGuiKey_ModAlt = ImGuiMod_Alt,
    ImGuiKey_ModSuper = ImGuiMod_Super, // Renamed in 1.89
                                        // ImGuiKey_KeyPadEnter = ImGuiKey_KeypadEnter,              // Renamed in 1.87
#endif
};

// Flags for Shortcut(), SetNextItemShortcut(),
// (and for upcoming extended versions of IsKeyPressed(), IsMouseClicked(), Shortcut(), SetKeyOwner(), SetItemKeyOwner() that are still in imgui_internal.h)
// Don't mistake with ImGuiInputTextFlags! (which is for ImGui::InputText() function)
enum ImGuiInputFlags_
{
    ImGuiInputFlags_None = 0,
    ImGuiInputFlags_Repeat = 1 << 0, // Enable repeat. Return true on successive repeats. Default for legacy IsKeyPressed(). NOT Default for legacy IsMouseClicked(). MUST BE == 1.

    // Flags for Shortcut(), SetNextItemShortcut()
    // - Routing policies: RouteGlobal+OverActive >> RouteActive or RouteFocused (if owner is active item) >> RouteGlobal+OverFocused >> RouteFocused (if in focused window stack) >> RouteGlobal.
    // - Default policy is RouteFocused. Can select only 1 policy among all available.
    ImGuiInputFlags_RouteActive = 1 << 10,  // Route to active item only.
    ImGuiInputFlags_RouteFocused = 1 << 11, // Route to windows in the focus stack (DEFAULT). Deep-most focused window takes inputs. Active item takes inputs over deep-most focused window.
    ImGuiInputFlags_RouteGlobal = 1 << 12,  // Global route (unless a focused window or active item registered the route).
    ImGuiInputFlags_RouteAlways = 1 << 13,  // Do not register route, poll keys directly.
    // - Routing options
    ImGuiInputFlags_RouteOverFocused = 1 << 14,     // Option: global route: higher priority than focused route (unless active item in focused route).
    ImGuiInputFlags_RouteOverActive = 1 << 15,      // Option: global route: higher priority than active item. Unlikely you need to use that: will interfere with every active items, e.g. CTRL+A registered by InputText will be overridden by this. May not be fully honored as user/internal code is likely to always assume they can access keys when active.
    ImGuiInputFlags_RouteUnlessBgFocused = 1 << 16, // Option: global route: will not be applied if underlying background/void is focused (== no Dear ImGui windows are focused). Useful for overlay applications.
    ImGuiInputFlags_RouteFromRootWindow = 1 << 17,  // Option: route evaluated from the point of view of root window rather than current window.

    // Flags for SetNextItemShortcut()
    ImGuiInputFlags_Tooltip = 1 << 18, // Automatically display a tooltip when hovering item [BETA] Unsure of right api (opt-in/opt-out)
};

#ifndef IMGUI_DISABLE_OBSOLETE_KEYIO
// OBSOLETED in 1.88 (from July 2022): ImGuiNavInput and io.NavInputs[].
// Official backends between 1.60 and 1.86: will keep working and feed gamepad inputs as long as IMGUI_DISABLE_OBSOLETE_KEYIO is not set.
// Custom backends: feed gamepad inputs via io.AddKeyEvent() and ImGuiKey_GamepadXXX enums.
enum ImGuiNavInput
{
    ImGuiNavInput_Activate,
    ImGuiNavInput_Cancel,
    ImGuiNavInput_Input,
    ImGuiNavInput_Menu,
    ImGuiNavInput_DpadLeft,
    ImGuiNavInput_DpadRight,
    ImGuiNavInput_DpadUp,
    ImGuiNavInput_DpadDown,
    ImGuiNavInput_LStickLeft,
    ImGuiNavInput_LStickRight,
    ImGuiNavInput_LStickUp,
    ImGuiNavInput_LStickDown,
    ImGuiNavInput_FocusPrev,
    ImGuiNavInput_FocusNext,
    ImGuiNavInput_TweakSlow,
    ImGuiNavInput_TweakFast,
    ImGuiNavInput_COUNT,
};
#endif

// Configuration flags stored in io.ConfigFlags. Set by user/application.
enum ImGuiConfigFlags_
{
    ImGuiConfigFlags_None = 0,
    ImGuiConfigFlags_NavEnableKeyboard = 1 << 0,    // Master keyboard navigation enable flag. Enable full Tabbing + directional arrows + space/enter to activate.
    ImGuiConfigFlags_NavEnableGamepad = 1 << 1,     // Master gamepad navigation enable flag. Backend also needs to set ImGuiBackendFlags_HasGamepad.
    ImGuiConfigFlags_NavEnableSetMousePos = 1 << 2, // Instruct navigation to move the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is awkward. Will update io.MousePos and set io.WantSetMousePos=true. If enabled you MUST honor io.WantSetMousePos requests in your backend, otherwise ImGui will react as if the mouse is jumping around back and forth.
    ImGuiConfigFlags_NavNoCaptureKeyboard = 1 << 3, // Instruct navigation to not set the io.WantCaptureKeyboard flag when io.NavActive is set.
    ImGuiConfigFlags_NoMouse = 1 << 4,              // Instruct dear imgui to disable mouse inputs and interactions.
    ImGuiConfigFlags_NoMouseCursorChange = 1 << 5,  // Instruct backend to not alter mouse cursor shape and visibility. Use if the backend cursor changes are interfering with yours and you don't want to use SetMouseCursor() to change mouse cursor. You may want to honor requests from imgui by reading GetMouseCursor() yourself instead.
    ImGuiConfigFlags_NoKeyboard = 1 << 6,           // Instruct dear imgui to disable keyboard inputs and interactions. This is done by ignoring keyboard events and clearing existing states.

    // [BETA] Docking
    ImGuiConfigFlags_DockingEnable = 1 << 7, // Docking enable flags.

    // [BETA] Viewports
    // When using viewports it is recommended that your default value for ImGuiCol_WindowBg is opaque (Alpha=1.0) so transition to a viewport won't be noticeable.
    ImGuiConfigFlags_ViewportsEnable = 1 << 10,         // Viewport enable flags (require both ImGuiBackendFlags_PlatformHasViewports + ImGuiBackendFlags_RendererHasViewports set by the respective backends)
    ImGuiConfigFlags_DpiEnableScaleViewports = 1 << 14, // [BETA: Don't use] FIXME-DPI: Reposition and resize imgui windows when the DpiScale of a viewport changed (mostly useful for the main viewport hosting other window). Note that resizing the main window itself is up to your application.
    ImGuiConfigFlags_DpiEnableScaleFonts = 1 << 15,     // [BETA: Don't use] FIXME-DPI: Request bitmap-scaled fonts to match DpiScale. This is a very low-quality workaround. The correct way to handle DPI is _currently_ to replace the atlas and/or fonts in the Platform_OnChangedViewport callback, but this is all early work in progress.

    // User storage (to allow your backend/engine to communicate to code that may be shared between multiple projects. Those flags are NOT used by core Dear ImGui)
    ImGuiConfigFlags_IsSRGB = 1 << 20,        // Application is SRGB-aware.
    ImGuiConfigFlags_IsTouchScreen = 1 << 21, // Application is using a touch screen instead of a mouse.
};

// Backend capabilities flags stored in io.BackendFlags. Set by imgui_impl_xxx or custom backend.
enum ImGuiBackendFlags_
{
    ImGuiBackendFlags_None = 0,
    ImGuiBackendFlags_HasGamepad = 1 << 0,           // Backend Platform supports gamepad and currently has one connected.
    ImGuiBackendFlags_HasMouseCursors = 1 << 1,      // Backend Platform supports honoring GetMouseCursor() value to change the OS cursor shape.
    ImGuiBackendFlags_HasSetMousePos = 1 << 2,       // Backend Platform supports io.WantSetMousePos requests to reposition the OS mouse position (only used if ImGuiConfigFlags_NavEnableSetMousePos is set).
    ImGuiBackendFlags_RendererHasVtxOffset = 1 << 3, // Backend Renderer supports ImDrawCmd::VtxOffset. This enables output of large meshes (64K+ vertices) while still using 16-bit indices.

    // [BETA] Viewports
    ImGuiBackendFlags_PlatformHasViewports = 1 << 10,    // Backend Platform supports multiple viewports.
    ImGuiBackendFlags_HasMouseHoveredViewport = 1 << 11, // Backend Platform supports calling io.AddMouseViewportEvent() with the viewport under the mouse. IF POSSIBLE, ignore viewports with the ImGuiViewportFlags_NoInputs flag (Win32 backend, GLFW 3.30+ backend can do this, SDL backend cannot). If this cannot be done, Dear ImGui needs to use a flawed heuristic to find the viewport under.
    ImGuiBackendFlags_RendererHasViewports = 1 << 12,    // Backend Renderer supports multiple viewports.
};

// Enumeration for PushStyleColor() / PopStyleColor()
enum ImGuiCol_
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg, // Background of normal windows
    ImGuiCol_ChildBg,  // Background of child windows
    ImGuiCol_PopupBg,  // Background of popups, menus, tooltips windows
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg, // Background of checkbox, radio button, plot, slider, text input
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,          // Title bar
    ImGuiCol_TitleBgActive,    // Title bar when focused
    ImGuiCol_TitleBgCollapsed, // Title bar when collapsed
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_CheckMark, // Checkbox tick and RadioButton circle
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header, // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Separator,
    ImGuiCol_SeparatorHovered,
    ImGuiCol_SeparatorActive,
    ImGuiCol_ResizeGrip, // Resize grip in lower-right and lower-left corners of windows.
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_TabHovered,                // Tab background, when hovered
    ImGuiCol_Tab,                       // Tab background, when tab-bar is focused & tab is unselected
    ImGuiCol_TabSelected,               // Tab background, when tab-bar is focused & tab is selected
    ImGuiCol_TabSelectedOverline,       // Tab horizontal overline, when tab-bar is focused & tab is selected
    ImGuiCol_TabDimmed,                 // Tab background, when tab-bar is unfocused & tab is unselected
    ImGuiCol_TabDimmedSelected,         // Tab background, when tab-bar is unfocused & tab is selected
    ImGuiCol_TabDimmedSelectedOverline, //..horizontal overline, when tab-bar is unfocused & tab is selected
    ImGuiCol_DockingPreview,            // Preview overlay color when about to docking something
    ImGuiCol_DockingEmptyBg,            // Background color for empty node (e.g. CentralNode with no window docked into it)
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TableHeaderBg,     // Table header background
    ImGuiCol_TableBorderStrong, // Table outer and header borders (prefer using Alpha=1.0 here)
    ImGuiCol_TableBorderLight,  // Table inner borders (prefer using Alpha=1.0 here)
    ImGuiCol_TableRowBg,        // Table row background (even rows)
    ImGuiCol_TableRowBgAlt,     // Table row background (odd rows)
    ImGuiCol_TextLink,          // Hyperlink color
    ImGuiCol_TextSelectedBg,
    ImGuiCol_DragDropTarget,        // Rectangle highlighting a drop target
    ImGuiCol_NavHighlight,          // Gamepad/keyboard: current highlighted item
    ImGuiCol_NavWindowingHighlight, // Highlight window when using CTRL+TAB
    ImGuiCol_NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    ImGuiCol_ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
    ImGuiCol_COUNT,

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiCol_TabActive = ImGuiCol_TabSelected,                // [renamed in 1.90.9]
    ImGuiCol_TabUnfocused = ImGuiCol_TabDimmed,               // [renamed in 1.90.9]
    ImGuiCol_TabUnfocusedActive = ImGuiCol_TabDimmedSelected, // [renamed in 1.90.9]
#endif
};

// Enumeration for PushStyleVar() / PopStyleVar() to temporarily modify the ImGuiStyle structure.
// - The enum only refers to fields of ImGuiStyle which makes sense to be pushed/popped inside UI code.
//   During initialization or between frames, feel free to just poke into ImGuiStyle directly.
// - Tip: Use your programming IDE navigation facilities on the names in the _second column_ below to find the actual members and their description.
//   - In Visual Studio: CTRL+comma ("Edit.GoToAll") can follow symbols inside comments, whereas CTRL+F12 ("Edit.GoToImplementation") cannot.
//   - In Visual Studio w/ Visual Assist installed: ALT+G ("VAssistX.GoToImplementation") can also follow symbols inside comments.
//   - In VS Code, CLion, etc.: CTRL+click can follow symbols inside comments.
// - When changing this enum, you need to update the associated internal table GStyleVarInfo[] accordingly. This is where we link enum values to members offset/type.
enum ImGuiStyleVar_
{
    // Enum name -------------------------- // Member in ImGuiStyle structure (see ImGuiStyle for descriptions)
    ImGuiStyleVar_Alpha,                       // float     Alpha
    ImGuiStyleVar_DisabledAlpha,               // float     DisabledAlpha
    ImGuiStyleVar_WindowPadding,               // ImVec2    WindowPadding
    ImGuiStyleVar_WindowRounding,              // float     WindowRounding
    ImGuiStyleVar_WindowBorderSize,            // float     WindowBorderSize
    ImGuiStyleVar_WindowMinSize,               // ImVec2    WindowMinSize
    ImGuiStyleVar_WindowTitleAlign,            // ImVec2    WindowTitleAlign
    ImGuiStyleVar_ChildRounding,               // float     ChildRounding
    ImGuiStyleVar_ChildBorderSize,             // float     ChildBorderSize
    ImGuiStyleVar_PopupRounding,               // float     PopupRounding
    ImGuiStyleVar_PopupBorderSize,             // float     PopupBorderSize
    ImGuiStyleVar_FramePadding,                // ImVec2    FramePadding
    ImGuiStyleVar_FrameRounding,               // float     FrameRounding
    ImGuiStyleVar_FrameBorderSize,             // float     FrameBorderSize
    ImGuiStyleVar_ItemSpacing,                 // ImVec2    ItemSpacing
    ImGuiStyleVar_ItemInnerSpacing,            // ImVec2    ItemInnerSpacing
    ImGuiStyleVar_IndentSpacing,               // float     IndentSpacing
    ImGuiStyleVar_CellPadding,                 // ImVec2    CellPadding
    ImGuiStyleVar_ScrollbarSize,               // float     ScrollbarSize
    ImGuiStyleVar_ScrollbarRounding,           // float     ScrollbarRounding
    ImGuiStyleVar_GrabMinSize,                 // float     GrabMinSize
    ImGuiStyleVar_GrabRounding,                // float     GrabRounding
    ImGuiStyleVar_TabRounding,                 // float     TabRounding
    ImGuiStyleVar_TabBorderSize,               // float     TabBorderSize
    ImGuiStyleVar_TabBarBorderSize,            // float     TabBarBorderSize
    ImGuiStyleVar_TabBarOverlineSize,          // float     TabBarOverlineSize
    ImGuiStyleVar_TableAngledHeadersAngle,     // float     TableAngledHeadersAngle
    ImGuiStyleVar_TableAngledHeadersTextAlign, // ImVec2  TableAngledHeadersTextAlign
    ImGuiStyleVar_ButtonTextAlign,             // ImVec2    ButtonTextAlign
    ImGuiStyleVar_SelectableTextAlign,         // ImVec2    SelectableTextAlign
    ImGuiStyleVar_SeparatorTextBorderSize,     // float     SeparatorTextBorderSize
    ImGuiStyleVar_SeparatorTextAlign,          // ImVec2    SeparatorTextAlign
    ImGuiStyleVar_SeparatorTextPadding,        // ImVec2    SeparatorTextPadding
    ImGuiStyleVar_DockingSeparatorSize,        // float     DockingSeparatorSize
    ImGuiStyleVar_COUNT
};

// Flags for InvisibleButton() [extended in imgui_internal.h]
enum ImGuiButtonFlags_
{
    ImGuiButtonFlags_None = 0,
    ImGuiButtonFlags_MouseButtonLeft = 1 << 0,                                                                                                     // React on left mouse button (default)
    ImGuiButtonFlags_MouseButtonRight = 1 << 1,                                                                                                    // React on right mouse button
    ImGuiButtonFlags_MouseButtonMiddle = 1 << 2,                                                                                                   // React on center mouse button
    ImGuiButtonFlags_MouseButtonMask_ = ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight | ImGuiButtonFlags_MouseButtonMiddle, // [Internal]
    // ImGuiButtonFlags_MouseButtonDefault_  = ImGuiButtonFlags_MouseButtonLeft,
};

// Flags for ColorEdit3() / ColorEdit4() / ColorPicker3() / ColorPicker4() / ColorButton()
enum ImGuiColorEditFlags_
{
    ImGuiColorEditFlags_None = 0,
    ImGuiColorEditFlags_NoAlpha = 1 << 1,        //              // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (will only read 3 components from the input pointer).
    ImGuiColorEditFlags_NoPicker = 1 << 2,       //              // ColorEdit: disable picker when clicking on color square.
    ImGuiColorEditFlags_NoOptions = 1 << 3,      //              // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
    ImGuiColorEditFlags_NoSmallPreview = 1 << 4, //              // ColorEdit, ColorPicker: disable color square preview next to the inputs. (e.g. to show only the inputs)
    ImGuiColorEditFlags_NoInputs = 1 << 5,       //              // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview color square).
    ImGuiColorEditFlags_NoTooltip = 1 << 6,      //              // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
    ImGuiColorEditFlags_NoLabel = 1 << 7,        //              // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
    ImGuiColorEditFlags_NoSidePreview = 1 << 8,  //              // ColorPicker: disable bigger color preview on right side of the picker, use small color square preview instead.
    ImGuiColorEditFlags_NoDragDrop = 1 << 9,     //              // ColorEdit: disable drag and drop target. ColorButton: disable drag and drop source.
    ImGuiColorEditFlags_NoBorder = 1 << 10,      //              // ColorButton: disable border (which is enforced by default)

    // User Options (right-click on widget to change some of them).
    ImGuiColorEditFlags_AlphaBar = 1 << 16,         //              // ColorEdit, ColorPicker: show vertical alpha bar/gradient in picker.
    ImGuiColorEditFlags_AlphaPreview = 1 << 17,     //              // ColorEdit, ColorPicker, ColorButton: display preview as a transparent color over a checkerboard, instead of opaque.
    ImGuiColorEditFlags_AlphaPreviewHalf = 1 << 18, //              // ColorEdit, ColorPicker, ColorButton: display half opaque / half checkerboard, instead of opaque.
    ImGuiColorEditFlags_HDR = 1 << 19,              //              // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use ImGuiColorEditFlags_Float flag as well).
    ImGuiColorEditFlags_DisplayRGB = 1 << 20,       // [Display]    // ColorEdit: override _display_ type among RGB/HSV/Hex. ColorPicker: select any combination using one or more of RGB/HSV/Hex.
    ImGuiColorEditFlags_DisplayHSV = 1 << 21,       // [Display]    // "
    ImGuiColorEditFlags_DisplayHex = 1 << 22,       // [Display]    // "
    ImGuiColorEditFlags_Uint8 = 1 << 23,            // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255.
    ImGuiColorEditFlags_Float = 1 << 24,            // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.
    ImGuiColorEditFlags_PickerHueBar = 1 << 25,     // [Picker]     // ColorPicker: bar for Hue, rectangle for Sat/Value.
    ImGuiColorEditFlags_PickerHueWheel = 1 << 26,   // [Picker]     // ColorPicker: wheel for Hue, triangle for Sat/Value.
    ImGuiColorEditFlags_InputRGB = 1 << 27,         // [Input]      // ColorEdit, ColorPicker: input and output data in RGB format.
    ImGuiColorEditFlags_InputHSV = 1 << 28,         // [Input]      // ColorEdit, ColorPicker: input and output data in HSV format.

    // Defaults Options. You can set application defaults using SetColorEditOptions(). The intent is that you probably don't want to
    // override them in most of your calls. Let the user choose via the option menu and/or call SetColorEditOptions() once during startup.
    ImGuiColorEditFlags_DefaultOptions_ = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,

    // [Internal] Masks
    ImGuiColorEditFlags_DisplayMask_ = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex,
    ImGuiColorEditFlags_DataTypeMask_ = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float,
    ImGuiColorEditFlags_PickerMask_ = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar,
    ImGuiColorEditFlags_InputMask_ = ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_InputHSV,

    // Obsolete names
    // ImGuiColorEditFlags_RGB = ImGuiColorEditFlags_DisplayRGB, ImGuiColorEditFlags_HSV = ImGuiColorEditFlags_DisplayHSV, ImGuiColorEditFlags_HEX = ImGuiColorEditFlags_DisplayHex  // [renamed in 1.69]
};

// Flags for DragFloat(), DragInt(), SliderFloat(), SliderInt() etc.
// We use the same sets of flags for DragXXX() and SliderXXX() functions as the features are the same and it makes it easier to swap them.
// (Those are per-item flags. There are shared flags in ImGuiIO: io.ConfigDragClickToInputText)
enum ImGuiSliderFlags_
{
    ImGuiSliderFlags_None = 0,
    ImGuiSliderFlags_AlwaysClamp = 1 << 4,      // Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.
    ImGuiSliderFlags_Logarithmic = 1 << 5,      // Make the widget logarithmic (linear otherwise). Consider using ImGuiSliderFlags_NoRoundToFormat with this if using a format-string with small amount of digits.
    ImGuiSliderFlags_NoRoundToFormat = 1 << 6,  // Disable rounding underlying value to match precision of the display format string (e.g. %.3f values are rounded to those 3 digits).
    ImGuiSliderFlags_NoInput = 1 << 7,          // Disable CTRL+Click or Enter key allowing to input text directly into the widget.
    ImGuiSliderFlags_WrapAround = 1 << 8,       // Enable wrapping around from max to min and from min to max (only supported by DragXXX() functions for now.
    ImGuiSliderFlags_InvalidMask_ = 0x7000000F, // [Internal] We treat using those bits as being potentially a 'float power' argument from the previous API that has got miscast to this enum, and will trigger an assert if needed.

    // Obsolete names
    // ImGuiSliderFlags_ClampOnInput = ImGuiSliderFlags_AlwaysClamp, // [renamed in 1.79]
};

// Identify a mouse button.
// Those values are guaranteed to be stable and we frequently use 0/1 directly. Named enums provided for convenience.
enum ImGuiMouseButton_
{
    ImGuiMouseButton_Left = 0,
    ImGuiMouseButton_Right = 1,
    ImGuiMouseButton_Middle = 2,
    ImGuiMouseButton_COUNT = 5
};

// Enumeration for GetMouseCursor()
// User code may request backend to display given cursor by calling SetMouseCursor(), which is why we have some cursors that are marked unused here
enum ImGuiMouseCursor_
{
    ImGuiMouseCursor_None = -1,
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,  // When hovering over InputText, etc.
    ImGuiMouseCursor_ResizeAll,  // (Unused by Dear ImGui functions)
    ImGuiMouseCursor_ResizeNS,   // When hovering over a horizontal border
    ImGuiMouseCursor_ResizeEW,   // When hovering over a vertical border or a column
    ImGuiMouseCursor_ResizeNESW, // When hovering over the bottom-left corner of a window
    ImGuiMouseCursor_ResizeNWSE, // When hovering over the bottom-right corner of a window
    ImGuiMouseCursor_Hand,       // (Unused by Dear ImGui functions. Use for e.g. hyperlinks)
    ImGuiMouseCursor_NotAllowed, // When hovering something with disallowed interaction. Usually a crossed circle.
    ImGuiMouseCursor_COUNT
};

// Enumeration for AddMouseSourceEvent() actual source of Mouse Input data.
// Historically we use "Mouse" terminology everywhere to indicate pointer data, e.g. MousePos, IsMousePressed(), io.AddMousePosEvent()
// But that "Mouse" data can come from different source which occasionally may be useful for application to know about.
// You can submit a change of pointer type using io.AddMouseSourceEvent().
enum ImGuiMouseSource : int
{
    ImGuiMouseSource_Mouse = 0,   // Input is coming from an actual mouse.
    ImGuiMouseSource_TouchScreen, // Input is coming from a touch screen (no hovering prior to initial press, less precise initial press aiming, dual-axis wheeling possible).
    ImGuiMouseSource_Pen,         // Input is coming from a pressure/magnetic pen (often used in conjunction with high-sampling rates).
    ImGuiMouseSource_COUNT
};

// Enumeration for ImGui::SetNextWindow***(), SetWindow***(), SetNextItem***() functions
// Represent a condition.
// Important: Treat as a regular enum! Do NOT combine multiple values using binary operators! All the functions above treat 0 as a shortcut to ImGuiCond_Always.
enum ImGuiCond_
{
    ImGuiCond_None = 0,              // No condition (always set the variable), same as _Always
    ImGuiCond_Always = 1 << 0,       // No condition (always set the variable), same as _None
    ImGuiCond_Once = 1 << 1,         // Set the variable once per runtime session (only the first call will succeed)
    ImGuiCond_FirstUseEver = 1 << 2, // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
    ImGuiCond_Appearing = 1 << 3,    // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
};

//-----------------------------------------------------------------------------
// [SECTION] Tables API flags and structures (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
//-----------------------------------------------------------------------------

// Flags for ImGui::BeginTable()
// - Important! Sizing policies have complex and subtle side effects, much more so than you would expect.
//   Read comments/demos carefully + experiment with live demos to get acquainted with them.
// - The DEFAULT sizing policies are:
//    - Default to ImGuiTableFlags_SizingFixedFit    if ScrollX is on, or if host window has ImGuiWindowFlags_AlwaysAutoResize.
//    - Default to ImGuiTableFlags_SizingStretchSame if ScrollX is off.
// - When ScrollX is off:
//    - Table defaults to ImGuiTableFlags_SizingStretchSame -> all Columns defaults to ImGuiTableColumnFlags_WidthStretch with same weight.
//    - Columns sizing policy allowed: Stretch (default), Fixed/Auto.
//    - Fixed Columns (if any) will generally obtain their requested width (unless the table cannot fit them all).
//    - Stretch Columns will share the remaining width according to their respective weight.
//    - Mixed Fixed/Stretch columns is possible but has various side-effects on resizing behaviors.
//      The typical use of mixing sizing policies is: any number of LEADING Fixed columns, followed by one or two TRAILING Stretch columns.
//      (this is because the visible order of columns have subtle but necessary effects on how they react to manual resizing).
// - When ScrollX is on:
//    - Table defaults to ImGuiTableFlags_SizingFixedFit -> all Columns defaults to ImGuiTableColumnFlags_WidthFixed
//    - Columns sizing policy allowed: Fixed/Auto mostly.
//    - Fixed Columns can be enlarged as needed. Table will show a horizontal scrollbar if needed.
//    - When using auto-resizing (non-resizable) fixed columns, querying the content width to use item right-alignment e.g. SetNextItemWidth(-FLT_MIN) doesn't make sense, would create a feedback loop.
//    - Using Stretch columns OFTEN DOES NOT MAKE SENSE if ScrollX is on, UNLESS you have specified a value for 'inner_width' in BeginTable().
//      If you specify a value for 'inner_width' then effectively the scrolling space is known and Stretch or mixed Fixed/Stretch columns become meaningful again.
// - Read on documentation at the top of imgui_tables.cpp for details.
enum ImGuiTableFlags_
{
    // Features
    ImGuiTableFlags_None = 0,
    ImGuiTableFlags_Resizable = 1 << 0,                                                           // Enable resizing columns.
    ImGuiTableFlags_Reorderable = 1 << 1,                                                         // Enable reordering columns in header row (need calling TableSetupColumn() + TableHeadersRow() to display headers)
    ImGuiTableFlags_Hideable = 1 << 2,                                                            // Enable hiding/disabling columns in context menu.
    ImGuiTableFlags_Sortable = 1 << 3,                                                            // Enable sorting. Call TableGetSortSpecs() to obtain sort specs. Also see ImGuiTableFlags_SortMulti and ImGuiTableFlags_SortTristate.
    ImGuiTableFlags_NoSavedSettings = 1 << 4,                                                     // Disable persisting columns order, width and sort settings in the .ini file.
    ImGuiTableFlags_ContextMenuInBody = 1 << 5,                                                   // Right-click on columns body/contents will display table context menu. By default it is available in TableHeadersRow().
                                                                                                  // Decorations
    ImGuiTableFlags_RowBg = 1 << 6,                                                               // Set each RowBg color with ImGuiCol_TableRowBg or ImGuiCol_TableRowBgAlt (equivalent of calling TableSetBgColor with ImGuiTableBgFlags_RowBg0 on each row manually)
    ImGuiTableFlags_BordersInnerH = 1 << 7,                                                       // Draw horizontal borders between rows.
    ImGuiTableFlags_BordersOuterH = 1 << 8,                                                       // Draw horizontal borders at the top and bottom.
    ImGuiTableFlags_BordersInnerV = 1 << 9,                                                       // Draw vertical borders between columns.
    ImGuiTableFlags_BordersOuterV = 1 << 10,                                                      // Draw vertical borders on the left and right sides.
    ImGuiTableFlags_BordersH = ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH,     // Draw horizontal borders.
    ImGuiTableFlags_BordersV = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV,     // Draw vertical borders.
    ImGuiTableFlags_BordersInner = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersInnerH, // Draw inner borders.
    ImGuiTableFlags_BordersOuter = ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH, // Draw outer borders.
    ImGuiTableFlags_Borders = ImGuiTableFlags_BordersInner | ImGuiTableFlags_BordersOuter,        // Draw all borders.
    ImGuiTableFlags_NoBordersInBody = 1 << 11,                                                    // [ALPHA] Disable vertical borders in columns Body (borders will always appear in Headers). -> May move to style
    ImGuiTableFlags_NoBordersInBodyUntilResize = 1 << 12,                                         // [ALPHA] Disable vertical borders in columns Body until hovered for resize (borders will always appear in Headers). -> May move to style
                                                                                                  // Sizing Policy (read above for defaults)
    ImGuiTableFlags_SizingFixedFit = 1 << 13,                                                     // Columns default to _WidthFixed or _WidthAuto (if resizable or not resizable), matching contents width.
    ImGuiTableFlags_SizingFixedSame = 2 << 13,                                                    // Columns default to _WidthFixed or _WidthAuto (if resizable or not resizable), matching the maximum contents width of all columns. Implicitly enable ImGuiTableFlags_NoKeepColumnsVisible.
    ImGuiTableFlags_SizingStretchProp = 3 << 13,                                                  // Columns default to _WidthStretch with default weights proportional to each columns contents widths.
    ImGuiTableFlags_SizingStretchSame = 4 << 13,                                                  // Columns default to _WidthStretch with default weights all equal, unless overridden by TableSetupColumn().
                                                                                                  // Sizing Extra Options
    ImGuiTableFlags_NoHostExtendX = 1 << 16,                                                      // Make outer width auto-fit to columns, overriding outer_size.x value. Only available when ScrollX/ScrollY are disabled and Stretch columns are not used.
    ImGuiTableFlags_NoHostExtendY = 1 << 17,                                                      // Make outer height stop exactly at outer_size.y (prevent auto-extending table past the limit). Only available when ScrollX/ScrollY are disabled. Data below the limit will be clipped and not visible.
    ImGuiTableFlags_NoKeepColumnsVisible = 1 << 18,                                               // Disable keeping column always minimally visible when ScrollX is off and table gets too small. Not recommended if columns are resizable.
    ImGuiTableFlags_PreciseWidths = 1 << 19,                                                      // Disable distributing remainder width to stretched columns (width allocation on a 100-wide table with 3 columns: Without this flag: 33,33,34. With this flag: 33,33,33). With larger number of columns, resizing will appear to be less smooth.
                                                                                                  // Clipping
    ImGuiTableFlags_NoClip = 1 << 20,                                                             // Disable clipping rectangle for every individual columns (reduce draw command count, items will be able to overflow into other columns). Generally incompatible with TableSetupScrollFreeze().
                                                                                                  // Padding
    ImGuiTableFlags_PadOuterX = 1 << 21,                                                          // Default if BordersOuterV is on. Enable outermost padding. Generally desirable if you have headers.
    ImGuiTableFlags_NoPadOuterX = 1 << 22,                                                        // Default if BordersOuterV is off. Disable outermost padding.
    ImGuiTableFlags_NoPadInnerX = 1 << 23,                                                        // Disable inner padding between columns (double inner padding if BordersOuterV is on, single inner padding if BordersOuterV is off).
                                                                                                  // Scrolling
    ImGuiTableFlags_ScrollX = 1 << 24,                                                            // Enable horizontal scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size. Changes default sizing policy. Because this creates a child window, ScrollY is currently generally recommended when using ScrollX.
    ImGuiTableFlags_ScrollY = 1 << 25,                                                            // Enable vertical scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size.
                                                                                                  // Sorting
    ImGuiTableFlags_SortMulti = 1 << 26,                                                          // Hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).
    ImGuiTableFlags_SortTristate = 1 << 27,                                                       // Allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).
                                                                                                  // Miscellaneous
    ImGuiTableFlags_HighlightHoveredColumn = 1 << 28,                                             // Highlight column headers when hovered (may evolve into a fuller highlight)

    // [Internal] Combinations and masks
    ImGuiTableFlags_SizingMask_ = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_SizingFixedSame | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_SizingStretchSame,
};

// Flags for ImGui::TableSetupColumn()
enum ImGuiTableColumnFlags_
{
    // Input configuration flags
    ImGuiTableColumnFlags_None = 0,
    ImGuiTableColumnFlags_Disabled = 1 << 0,              // Overriding/master disable flag: hide column, won't show in context menu (unlike calling TableSetColumnEnabled() which manipulates the user accessible state)
    ImGuiTableColumnFlags_DefaultHide = 1 << 1,           // Default as a hidden/disabled column.
    ImGuiTableColumnFlags_DefaultSort = 1 << 2,           // Default as a sorting column.
    ImGuiTableColumnFlags_WidthStretch = 1 << 3,          // Column will stretch. Preferable with horizontal scrolling disabled (default if table sizing policy is _SizingStretchSame or _SizingStretchProp).
    ImGuiTableColumnFlags_WidthFixed = 1 << 4,            // Column will not stretch. Preferable with horizontal scrolling enabled (default if table sizing policy is _SizingFixedFit and table is resizable).
    ImGuiTableColumnFlags_NoResize = 1 << 5,              // Disable manual resizing.
    ImGuiTableColumnFlags_NoReorder = 1 << 6,             // Disable manual reordering this column, this will also prevent other columns from crossing over this column.
    ImGuiTableColumnFlags_NoHide = 1 << 7,                // Disable ability to hide/disable this column.
    ImGuiTableColumnFlags_NoClip = 1 << 8,                // Disable clipping for this column (all NoClip columns will render in a same draw command).
    ImGuiTableColumnFlags_NoSort = 1 << 9,                // Disable ability to sort on this field (even if ImGuiTableFlags_Sortable is set on the table).
    ImGuiTableColumnFlags_NoSortAscending = 1 << 10,      // Disable ability to sort in the ascending direction.
    ImGuiTableColumnFlags_NoSortDescending = 1 << 11,     // Disable ability to sort in the descending direction.
    ImGuiTableColumnFlags_NoHeaderLabel = 1 << 12,        // TableHeadersRow() will submit an empty label for this column. Convenient for some small columns. Name will still appear in context menu or in angled headers. You may append into this cell by calling TableSetColumnIndex() right after the TableHeadersRow() call.
    ImGuiTableColumnFlags_NoHeaderWidth = 1 << 13,        // Disable header text width contribution to automatic column width.
    ImGuiTableColumnFlags_PreferSortAscending = 1 << 14,  // Make the initial sort direction Ascending when first sorting on this column (default).
    ImGuiTableColumnFlags_PreferSortDescending = 1 << 15, // Make the initial sort direction Descending when first sorting on this column.
    ImGuiTableColumnFlags_IndentEnable = 1 << 16,         // Use current Indent value when entering cell (default for column 0).
    ImGuiTableColumnFlags_IndentDisable = 1 << 17,        // Ignore current Indent value when entering cell (default for columns > 0). Indentation changes _within_ the cell will still be honored.
    ImGuiTableColumnFlags_AngledHeader = 1 << 18,         // TableHeadersRow() will submit an angled header row for this column. Note this will add an extra row.

    // Output status flags, read-only via TableGetColumnFlags()
    ImGuiTableColumnFlags_IsEnabled = 1 << 24, // Status: is enabled == not hidden by user/api (referred to as "Hide" in _DefaultHide and _NoHide) flags.
    ImGuiTableColumnFlags_IsVisible = 1 << 25, // Status: is visible == is enabled AND not clipped by scrolling.
    ImGuiTableColumnFlags_IsSorted = 1 << 26,  // Status: is currently part of the sort specs
    ImGuiTableColumnFlags_IsHovered = 1 << 27, // Status: is hovered by mouse

    // [Internal] Combinations and masks
    ImGuiTableColumnFlags_WidthMask_ = ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_WidthFixed,
    ImGuiTableColumnFlags_IndentMask_ = ImGuiTableColumnFlags_IndentEnable | ImGuiTableColumnFlags_IndentDisable,
    ImGuiTableColumnFlags_StatusMask_ = ImGuiTableColumnFlags_IsEnabled | ImGuiTableColumnFlags_IsVisible | ImGuiTableColumnFlags_IsSorted | ImGuiTableColumnFlags_IsHovered,
    ImGuiTableColumnFlags_NoDirectResize_ = 1 << 30, // [Internal] Disable user resizing this column directly (it may however we resized indirectly from its left edge)
};

// Flags for ImGui::TableNextRow()
enum ImGuiTableRowFlags_
{
    ImGuiTableRowFlags_None = 0,
    ImGuiTableRowFlags_Headers = 1 << 0, // Identify header row (set default background color + width of its contents accounted differently for auto column width)
};

// Enum for ImGui::TableSetBgColor()
// Background colors are rendering in 3 layers:
//  - Layer 0: draw with RowBg0 color if set, otherwise draw with ColumnBg0 if set.
//  - Layer 1: draw with RowBg1 color if set, otherwise draw with ColumnBg1 if set.
//  - Layer 2: draw with CellBg color if set.
// The purpose of the two row/columns layers is to let you decide if a background color change should override or blend with the existing color.
// When using ImGuiTableFlags_RowBg on the table, each row has the RowBg0 color automatically set for odd/even rows.
// If you set the color of RowBg0 target, your color will override the existing RowBg0 color.
// If you set the color of RowBg1 or ColumnBg1 target, your color will blend over the RowBg0 color.
enum ImGuiTableBgTarget_
{
    ImGuiTableBgTarget_None = 0,
    ImGuiTableBgTarget_RowBg0 = 1, // Set row background color 0 (generally used for background, automatically set when ImGuiTableFlags_RowBg is used)
    ImGuiTableBgTarget_RowBg1 = 2, // Set row background color 1 (generally used for selection marking)
    ImGuiTableBgTarget_CellBg = 3, // Set cell background color (top-most color)
};