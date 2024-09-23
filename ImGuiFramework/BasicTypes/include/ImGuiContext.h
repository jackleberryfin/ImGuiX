#pragma once

#include "ImTypeDefs.h"
#include "ImVector.h"
#include "ImVec2.h"
#include "ImGuiIO.h"
#include "ImGuiPlatformIO.h"
#include "ImGuiStyle.h"

struct ImGuiContext
{
    bool Initialized;
    bool FontAtlasOwnedByContext; // IO.Fonts-> is owned by the ImGuiContext and will be destructed along with it.
    ImGuiIO IO;
    ImGuiPlatformIO PlatformIO;
    ImGuiStyle Style;
    ImGuiConfigFlags ConfigFlagsCurrFrame; // = g.IO.ConfigFlags at the time of NewFrame()
    ImGuiConfigFlags ConfigFlagsLastFrame;
    ImFont *Font;          // (Shortcut) == FontStack.empty() ? IO.Font : FontStack.back()
    float FontSize;        // (Shortcut) == FontBaseSize * g.CurrentWindow->FontWindowScale == window->FontSize(). Text height for current window.
    float FontBaseSize;    // (Shortcut) == IO.FontGlobalScale * Font->Scale * Font->FontSize. Base text height.
    float FontScale;       // == FontSize / Font->FontSize
    float CurrentDpiScale; // Current window/viewport DpiScale == CurrentViewport->DpiScale
    ImDrawListSharedData DrawListSharedData;
    double Time;
    int FrameCount;
    int FrameCountEnded;
    int FrameCountPlatformEnded;
    int FrameCountRendered;
    bool WithinFrameScope;                   // Set by NewFrame(), cleared by EndFrame()
    bool WithinFrameScopeWithImplicitWindow; // Set by NewFrame(), cleared by EndFrame() when the implicit debug window has been pushed
    bool WithinEndChild;                     // Set within EndChild()
    bool GcCompactAll;                       // Request full GC
    bool TestEngineHookItems;                // Will call test engine hooks: ImGuiTestEngineHook_ItemAdd(), ImGuiTestEngineHook_ItemInfo(), ImGuiTestEngineHook_Log()
    void *TestEngine;                        // Test engine user data
    char ContextName[16];                    // Storage for a context name (to facilitate debugging multi-context setups)

    // Inputs
    ImVector<ImGuiInputEvent> InputEventsQueue; // Input events which will be trickled/written into IO structure.
    ImVector<ImGuiInputEvent> InputEventsTrail; // Past input events processed in NewFrame(). This is to allow domain-specific application to access e.g mouse/pen trail.
    ImGuiMouseSource InputEventsNextMouseSource;
    ImU32 InputEventsNextEventId;

    // Windows state
    ImVector<ImGuiWindow *> Windows;               // Windows, sorted in display order, back to front
    ImVector<ImGuiWindow *> WindowsFocusOrder;     // Root windows, sorted in focus order, back to front.
    ImVector<ImGuiWindow *> WindowsTempSortBuffer; // Temporary buffer used in EndFrame() to reorder windows so parents are kept before their child
    ImVector<ImGuiWindowStackData> CurrentWindowStack;
    ImGuiStorage WindowsById;                    // Map window's ImGuiID to ImGuiWindow*
    int WindowsActiveCount;                      // Number of unique windows submitted by frame
    ImVec2 WindowsHoverPadding;                  // Padding around resizable windows for which hovering on counts as hovering the window == ImMax(style.TouchExtraPadding, WINDOWS_HOVER_PADDING).
    ImGuiID DebugBreakInWindow;                  // Set to break in Begin() call.
    ImGuiWindow *CurrentWindow;                  // Window being drawn into
    ImGuiWindow *HoveredWindow;                  // Window the mouse is hovering. Will typically catch mouse inputs.
    ImGuiWindow *HoveredWindowUnderMovingWindow; // Hovered window ignoring MovingWindow. Only set if MovingWindow is set.
    ImGuiWindow *HoveredWindowBeforeClear;       // Window the mouse is hovering. Filled even with _NoMouse. This is currently useful for multi-context compositors.
    ImGuiWindow *MovingWindow;                   // Track the window we clicked on (in order to preserve focus). The actual window that is moved is generally MovingWindow->RootWindowDockTree.
    ImGuiWindow *WheelingWindow;                 // Track the window we started mouse-wheeling on. Until a timer elapse or mouse has moved, generally keep scrolling the same window even if during the course of scrolling the mouse ends up hovering a child window.
    ImVec2 WheelingWindowRefMousePos;
    int WheelingWindowStartFrame; // This may be set one frame before WheelingWindow is != NULL
    int WheelingWindowScrolledFrame;
    float WheelingWindowReleaseTimer;
    ImVec2 WheelingWindowWheelRemainder;
    ImVec2 WheelingAxisAvg;

    // Item/widgets state and tracking information
    ImGuiID DebugDrawIdConflicts; // Set when we detect multiple items with the same identifier
    ImGuiID DebugHookIdInfo;      // Will call core hooks: DebugHookIdInfo() from GetID functions, used by ID Stack Tool [next HoveredId/ActiveId to not pull in an extra cache-line]
    ImGuiID HoveredId;            // Hovered widget, filled during the frame
    ImGuiID HoveredIdPreviousFrame;
    int HoveredIdPreviousFrameItemCount; // Count numbers of items using the same ID as last frame's hovered id
    float HoveredIdTimer;                // Measure contiguous hovering time
    float HoveredIdNotActiveTimer;       // Measure contiguous hovering time where the item has not been active
    bool HoveredIdAllowOverlap;
    bool HoveredIdIsDisabled; // At least one widget passed the rect test, but has been discarded by disabled flag or popup inhibit. May be true even if HoveredId == 0.
    bool ItemUnclipByLog;     // Disable ItemAdd() clipping, essentially a memory-locality friendly copy of LogEnabled
    ImGuiID ActiveId;         // Active widget
    ImGuiID ActiveIdIsAlive;  // Active widget has been seen this frame (we can't use a bool as the ActiveId may change within the frame)
    float ActiveIdTimer;
    bool ActiveIdIsJustActivated;      // Set at the time of activation for one frame
    bool ActiveIdAllowOverlap;         // Active widget allows another widget to steal active id (generally for overlapping widgets, but not always)
    bool ActiveIdNoClearOnFocusLoss;   // Disable losing active id if the active id window gets unfocused.
    bool ActiveIdHasBeenPressedBefore; // Track whether the active id led to a press (this is to allow changing between PressOnClick and PressOnRelease without pressing twice). Used by range_select branch.
    bool ActiveIdHasBeenEditedBefore;  // Was the value associated to the widget Edited over the course of the Active state.
    bool ActiveIdHasBeenEditedThisFrame;
    bool ActiveIdFromShortcut;
    int ActiveIdMouseButton : 8;
    ImVec2 ActiveIdClickOffset; // Clicked offset from upper-left corner, if applicable (currently only set by ButtonBehavior)
    ImGuiWindow *ActiveIdWindow;
    ImGuiInputSource ActiveIdSource; // Activating source: ImGuiInputSource_Mouse OR ImGuiInputSource_Keyboard OR ImGuiInputSource_Gamepad
    ImGuiID ActiveIdPreviousFrame;
    bool ActiveIdPreviousFrameIsAlive;
    bool ActiveIdPreviousFrameHasBeenEditedBefore;
    ImGuiWindow *ActiveIdPreviousFrameWindow;
    ImGuiID LastActiveId;    // Store the last non-zero ActiveId, useful for animation.
    float LastActiveIdTimer; // Store the last non-zero ActiveId timer since the beginning of activation, useful for animation.

    // Key/Input Ownership + Shortcut Routing system
    // - The idea is that instead of "eating" a given key, we can link to an owner.
    // - Input query can then read input by specifying ImGuiKeyOwner_Any (== 0), ImGuiKeyOwner_NoOwner (== -1) or a custom ID.
    // - Routing is requested ahead of time for a given chord (Key + Mods) and granted in NewFrame().
    double LastKeyModsChangeTime;              // Record the last time key mods changed (affect repeat delay when using shortcut logic)
    double LastKeyModsChangeFromNoneTime;      // Record the last time key mods changed away from being 0 (affect repeat delay when using shortcut logic)
    double LastKeyboardKeyPressTime;           // Record the last time a keyboard key (ignore mouse/gamepad ones) was pressed.
    ImBitArrayForNamedKeys KeysMayBeCharInput; // Lookup to tell if a key can emit char input, see IsKeyChordPotentiallyCharInput(). sizeof() = 20 bytes
    ImGuiKeyOwnerData KeysOwnerData[ImGuiKey_NamedKey_COUNT];
    ImGuiKeyRoutingTable KeysRoutingTable;
    ImU32 ActiveIdUsingNavDirMask;             // Active widget will want to read those nav move requests (e.g. can activate a button and move away from it)
    bool ActiveIdUsingAllKeyboardKeys;         // Active widget will want to read all keyboard keys inputs. (this is a shortcut for not taking ownership of 100+ keys, frequently used by drag operations)
    ImGuiKeyChord DebugBreakInShortcutRouting; // Set to break in SetShortcutRouting()/Shortcut() calls.
    // ImU32                 ActiveIdUsingNavInputMask;          // [OBSOLETE] Since (IMGUI_VERSION_NUM >= 18804) : 'g.ActiveIdUsingNavInputMask |= (1 << ImGuiNavInput_Cancel);' becomes --> 'SetKeyOwner(ImGuiKey_Escape, g.ActiveId) and/or SetKeyOwner(ImGuiKey_NavGamepadCancel, g.ActiveId);'

    // Next window/item data
    ImGuiID CurrentFocusScopeId;        // Value for currently appending items == g.FocusScopeStack.back(). Not to be mistaken with g.NavFocusScopeId.
    ImGuiItemFlags CurrentItemFlags;    // Value for currently appending items == g.ItemFlagsStack.back()
    ImGuiID DebugLocateId;              // Storage for DebugLocateItemOnHover() feature: this is read by ItemAdd() so we keep it in a hot/cached location
    ImGuiNextItemData NextItemData;     // Storage for SetNextItem** functions
    ImGuiLastItemData LastItemData;     // Storage for last submitted item (setup by ItemAdd)
    ImGuiNextWindowData NextWindowData; // Storage for SetNextWindow** functions
    bool DebugShowGroupRects;

    // Shared stacks
    ImGuiCol DebugFlashStyleColorIdx;               // (Keep close to ColorStack to share cache line)
    ImVector<ImGuiColorMod> ColorStack;             // Stack for PushStyleColor()/PopStyleColor() - inherited by Begin()
    ImVector<ImGuiStyleMod> StyleVarStack;          // Stack for PushStyleVar()/PopStyleVar() - inherited by Begin()
    ImVector<ImFont *> FontStack;                   // Stack for PushFont()/PopFont() - inherited by Begin()
    ImVector<ImGuiFocusScopeData> FocusScopeStack;  // Stack for PushFocusScope()/PopFocusScope() - inherited by BeginChild(), pushed into by Begin()
    ImVector<ImGuiItemFlags> ItemFlagsStack;        // Stack for PushItemFlag()/PopItemFlag() - inherited by Begin()
    ImVector<ImGuiGroupData> GroupStack;            // Stack for BeginGroup()/EndGroup() - not inherited by Begin()
    ImVector<ImGuiPopupData> OpenPopupStack;        // Which popups are open (persistent)
    ImVector<ImGuiPopupData> BeginPopupStack;       // Which level of BeginPopup() we are in (reset every frame)
    ImVector<ImGuiTreeNodeStackData> TreeNodeStack; // Stack for TreeNode()

    // Viewports
    ImVector<ImGuiViewportP *> Viewports; // Active viewports (always 1+, and generally 1 unless multi-viewports are enabled). Each viewports hold their copy of ImDrawData.
    ImGuiViewportP *CurrentViewport;      // We track changes of viewport (happening in Begin) so we can call Platform_OnChangedViewport()
    ImGuiViewportP *MouseViewport;
    ImGuiViewportP *MouseLastHoveredViewport; // Last known viewport that was hovered by mouse (even if we are not hovering any viewport any more) + honoring the _NoInputs flag.
    ImGuiID PlatformLastFocusedViewportId;
    ImGuiPlatformMonitor FallbackMonitor; // Virtual monitor used as fallback if backend doesn't provide monitor information.
    ImRect PlatformMonitorsFullWorkRect;  // Bounding box of all platform monitors
    int ViewportCreatedCount;             // Unique sequential creation counter (mostly for testing/debugging)
    int PlatformWindowsCreatedCount;      // Unique sequential creation counter (mostly for testing/debugging)
    int ViewportFocusedStampCount;        // Every time the front-most window changes, we stamp its viewport with an incrementing counter

    // Gamepad/keyboard Navigation
    ImGuiWindow *NavWindow;       // Focused window for navigation. Could be called 'FocusedWindow'
    ImGuiID NavId;                // Focused item for navigation
    ImGuiID NavFocusScopeId;      // Focused focus scope (e.g. selection code often wants to "clear other items" when landing on an item of the same scope)
    ImGuiNavLayer NavLayer;       // Focused layer (main scrolling layer, or menu/title bar layer)
    ImGuiID NavActivateId;        // ~~ (g.ActiveId == 0) && (IsKeyPressed(ImGuiKey_Space) || IsKeyDown(ImGuiKey_Enter) || IsKeyPressed(ImGuiKey_NavGamepadActivate)) ? NavId : 0, also set when calling ActivateItem()
    ImGuiID NavActivateDownId;    // ~~ IsKeyDown(ImGuiKey_Space) || IsKeyDown(ImGuiKey_Enter) || IsKeyDown(ImGuiKey_NavGamepadActivate) ? NavId : 0
    ImGuiID NavActivatePressedId; // ~~ IsKeyPressed(ImGuiKey_Space) || IsKeyPressed(ImGuiKey_Enter) || IsKeyPressed(ImGuiKey_NavGamepadActivate) ? NavId : 0 (no repeat)
    ImGuiActivateFlags NavActivateFlags;
    ImVector<ImGuiFocusScopeData> NavFocusRoute; // Reversed copy focus scope stack for NavId (should contains NavFocusScopeId). This essentially follow the window->ParentWindowForFocusRoute chain.
    ImGuiID NavHighlightActivatedId;
    float NavHighlightActivatedTimer;
    ImGuiID NavNextActivateId; // Set by ActivateItem(), queued until next frame.
    ImGuiActivateFlags NavNextActivateFlags;
    ImGuiInputSource NavInputSource;                      // Keyboard or Gamepad mode? THIS CAN ONLY BE ImGuiInputSource_Keyboard or ImGuiInputSource_Mouse
    ImGuiSelectionUserData NavLastValidSelectionUserData; // Last valid data passed to SetNextItemSelectionUser(), or -1. For current window. Not reset when focusing an item that doesn't have selection data.
    bool NavIdIsAlive;                                    // Nav widget has been seen this frame ~~ NavRectRel is valid
    bool NavMousePosDirty;                                // When set we will update mouse position if (io.ConfigFlags & ImGuiConfigFlags_NavEnableSetMousePos) if set (NB: this not enabled by default)
    bool NavDisableHighlight;                             // When user starts using mouse, we hide gamepad/keyboard highlight (NB: but they are still available, which is why NavDisableHighlight isn't always != NavDisableMouseHover)
    bool NavDisableMouseHover;                            // When user starts using gamepad/keyboard, we hide mouse hovering highlight until mouse is touched again.

    // Navigation: Init & Move Requests
    bool NavAnyRequest;  // ~~ NavMoveRequest || NavInitRequest this is to perform early out in ItemAdd()
    bool NavInitRequest; // Init request for appearing window to select first item
    bool NavInitRequestFromMove;
    ImGuiNavItemData NavInitResult; // Init request result (first item of the window, or one for which SetItemDefaultFocus() was called)
    bool NavMoveSubmitted;          // Move request submitted, will process result on next NewFrame()
    bool NavMoveScoringItems;       // Move request submitted, still scoring incoming items
    bool NavMoveForwardToNextFrame;
    ImGuiNavMoveFlags NavMoveFlags;
    ImGuiScrollFlags NavMoveScrollFlags;
    ImGuiKeyChord NavMoveKeyMods;
    ImGuiDir NavMoveDir; // Direction of the move request (left/right/up/down)
    ImGuiDir NavMoveDirForDebug;
    ImGuiDir NavMoveClipDir;                    // FIXME-NAV: Describe the purpose of this better. Might want to rename?
    ImRect NavScoringRect;                      // Rectangle used for scoring, in screen space. Based of window->NavRectRel[], modified for directional navigation scoring.
    ImRect NavScoringNoClipRect;                // Some nav operations (such as PageUp/PageDown) enforce a region which clipper will attempt to always keep submitted
    int NavScoringDebugCount;                   // Metrics for debugging
    int NavTabbingDir;                          // Generally -1 or +1, 0 when tabbing without a nav id
    int NavTabbingCounter;                      // >0 when counting items for tabbing
    ImGuiNavItemData NavMoveResultLocal;        // Best move request candidate within NavWindow
    ImGuiNavItemData NavMoveResultLocalVisible; // Best move request candidate within NavWindow that are mostly visible (when using ImGuiNavMoveFlags_AlsoScoreVisibleSet flag)
    ImGuiNavItemData NavMoveResultOther;        // Best move request candidate within NavWindow's flattened hierarchy (when using ImGuiWindowFlags_NavFlattened flag)
    ImGuiNavItemData NavTabbingResultFirst;     // First tabbing request candidate within NavWindow and flattened hierarchy

    // Navigation: record of last move request
    ImGuiID NavJustMovedFromFocusScopeId; // Just navigated from this focus scope id (result of a successfully MoveRequest).
    ImGuiID NavJustMovedToId;             // Just navigated to this id (result of a successfully MoveRequest).
    ImGuiID NavJustMovedToFocusScopeId;   // Just navigated to this focus scope id (result of a successfully MoveRequest).
    ImGuiKeyChord NavJustMovedToKeyMods;
    bool NavJustMovedToIsTabbing;        // Copy of ImGuiNavMoveFlags_IsTabbing. Maybe we should store whole flags.
    bool NavJustMovedToHasSelectionData; // Copy of move result's InFlags & ImGuiItemFlags_HasSelectionUserData). Maybe we should just store ImGuiNavItemData.

    // Navigation: Windowing (CTRL+TAB for list, or Menu button + keys or directional pads to move/resize)
    ImGuiKeyChord ConfigNavWindowingKeyNext; // = ImGuiMod_Ctrl | ImGuiKey_Tab (or ImGuiMod_Super | ImGuiKey_Tab on OS X). For reconfiguration (see #4828)
    ImGuiKeyChord ConfigNavWindowingKeyPrev; // = ImGuiMod_Ctrl | ImGuiMod_Shift | ImGuiKey_Tab (or ImGuiMod_Super | ImGuiMod_Shift | ImGuiKey_Tab on OS X)
    ImGuiWindow *NavWindowingTarget;         // Target window when doing CTRL+Tab (or Pad Menu + FocusPrev/Next), this window is temporarily displayed top-most!
    ImGuiWindow *NavWindowingTargetAnim;     // Record of last valid NavWindowingTarget until DimBgRatio and NavWindowingHighlightAlpha becomes 0.0f, so the fade-out can stay on it.
    ImGuiWindow *NavWindowingListWindow;     // Internal window actually listing the CTRL+Tab contents
    float NavWindowingTimer;
    float NavWindowingHighlightAlpha;
    bool NavWindowingToggleLayer;
    ImGuiKey NavWindowingToggleKey;
    ImVec2 NavWindowingAccumDeltaPos;
    ImVec2 NavWindowingAccumDeltaSize;

    // Render
    float DimBgRatio; // 0.0..1.0 animation when fading in a dimming background (for modal window and CTRL+TAB list)

    // Drag and Drop
    bool DragDropActive;
    bool DragDropWithinSource; // Set when within a BeginDragDropXXX/EndDragDropXXX block for a drag source.
    bool DragDropWithinTarget; // Set when within a BeginDragDropXXX/EndDragDropXXX block for a drag target.
    ImGuiDragDropFlags DragDropSourceFlags;
    int DragDropSourceFrameCount;
    int DragDropMouseButton;
    ImGuiPayload DragDropPayload;
    ImRect DragDropTargetRect;     // Store rectangle of current target candidate (we favor small targets when overlapping)
    ImRect DragDropTargetClipRect; // Store ClipRect at the time of item's drawing
    ImGuiID DragDropTargetId;
    ImGuiDragDropFlags DragDropAcceptFlags;
    float DragDropAcceptIdCurrRectSurface;          // Target item surface (we resolve overlapping targets by prioritizing the smaller surface)
    ImGuiID DragDropAcceptIdCurr;                   // Target item id (set at the time of accepting the payload)
    ImGuiID DragDropAcceptIdPrev;                   // Target item id from previous frame (we need to store this to allow for overlapping drag and drop targets)
    int DragDropAcceptFrameCount;                   // Last time a target expressed a desire to accept the source
    ImGuiID DragDropHoldJustPressedId;              // Set when holding a payload just made ButtonBehavior() return a press.
    ImVector<unsigned char> DragDropPayloadBufHeap; // We don't expose the ImVector<> directly, ImGuiPayload only holds pointer+size
    unsigned char DragDropPayloadBufLocal[16];      // Local buffer for small payloads

    // Clipper
    int ClipperTempDataStacked;
    ImVector<ImGuiListClipperData> ClipperTempData;

    // Tables
    ImGuiTable *CurrentTable;
    ImGuiID DebugBreakInTable;                   // Set to break in BeginTable() call.
    int TablesTempDataStacked;                   // Temporary table data size (because we leave previous instances undestructed, we generally don't use TablesTempData.Size)
    ImVector<ImGuiTableTempData> TablesTempData; // Temporary table data (buffers reused/shared across instances, support nesting)
    ImPool<ImGuiTable> Tables;                   // Persistent table data
    ImVector<float> TablesLastTimeActive;        // Last used timestamp of each tables (SOA, for efficient GC)
    ImVector<ImDrawChannel> DrawChannelsTempMergeBuffer;

    // Tab bars
    ImGuiTabBar *CurrentTabBar;
    ImPool<ImGuiTabBar> TabBars;
    ImVector<ImGuiPtrOrIndex> CurrentTabBarStack;
    ImVector<ImGuiShrinkWidthItem> ShrinkWidthBuffer;

    // Multi-Select state
    ImGuiBoxSelectState BoxSelectState;
    ImGuiMultiSelectTempData *CurrentMultiSelect;
    int MultiSelectTempDataStacked; // Temporary multi-select data size (because we leave previous instances undestructed, we generally don't use MultiSelectTempData.Size)
    ImVector<ImGuiMultiSelectTempData> MultiSelectTempData;
    ImPool<ImGuiMultiSelectState> MultiSelectStorage;

    // Hover Delay system
    ImGuiID HoverItemDelayId;
    ImGuiID HoverItemDelayIdPreviousFrame;
    float HoverItemDelayTimer;               // Currently used by IsItemHovered()
    float HoverItemDelayClearTimer;          // Currently used by IsItemHovered(): grace time before g.TooltipHoverTimer gets cleared.
    ImGuiID HoverItemUnlockedStationaryId;   // Mouse has once been stationary on this item. Only reset after departing the item.
    ImGuiID HoverWindowUnlockedStationaryId; // Mouse has once been stationary on this window. Only reset after departing the window.

    // Mouse state
    ImGuiMouseCursor MouseCursor;
    float MouseStationaryTimer; // Time the mouse has been stationary (with some loose heuristic)
    ImVec2 MouseLastValidPos;

    // Widget state
    ImGuiInputTextState InputTextState;
    ImGuiInputTextDeactivatedState InputTextDeactivatedState;
    ImFont InputTextPasswordFont;
    ImGuiID TempInputId;                    // Temporary text input when CTRL+clicking on a slider, etc.
    ImGuiDataTypeStorage DataTypeZeroValue; // 0 for all data types
    int BeginMenuDepth;
    int BeginComboDepth;
    ImGuiColorEditFlags ColorEditOptions; // Store user options for color edit widgets
    ImGuiID ColorEditCurrentID;           // Set temporarily while inside of the parent-most ColorEdit4/ColorPicker4 (because they call each others).
    ImGuiID ColorEditSavedID;             // ID we are saving/restoring HS for
    float ColorEditSavedHue;              // Backup of last Hue associated to LastColor, so we can restore Hue in lossy RGB<>HSV round trips
    float ColorEditSavedSat;              // Backup of last Saturation associated to LastColor, so we can restore Saturation in lossy RGB<>HSV round trips
    ImU32 ColorEditSavedColor;            // RGB value with alpha set to 0.
    ImVec4 ColorPickerRef;                // Initial/reference color at the time of opening the color picker.
    ImGuiComboPreviewData ComboPreviewData;
    ImRect WindowResizeBorderExpectedRect; // Expected border rect, switch to relative edit if moving
    bool WindowResizeRelativeMode;
    short ScrollbarSeekMode;               // 0: scroll to clicked location, -1/+1: prev/next page.
    float ScrollbarClickDeltaToGrabCenter; // When scrolling to mouse location: distance between mouse and center of grab box, normalized in parent space.
    float SliderGrabClickOffset;
    float SliderCurrentAccum;     // Accumulated slider delta when using navigation controls.
    bool SliderCurrentAccumDirty; // Has the accumulated slider delta changed since last time we tried to apply it?
    bool DragCurrentAccumDirty;
    float DragCurrentAccum;      // Accumulator for dragging modification. Always high-precision, not rounded by end-user precision settings
    float DragSpeedDefaultRatio; // If speed == 0.0f, uses (max-min) * DragSpeedDefaultRatio
    float DisabledAlphaBackup;   // Backup for style.Alpha for BeginDisabled()
    short DisabledStackSize;
    short LockMarkEdited;
    short TooltipOverrideCount;
    ImVector<char> ClipboardHandlerData;         // If no custom clipboard handler is defined
    ImVector<ImGuiID> MenusIdSubmittedThisFrame; // A list of menu IDs that were rendered at least once
    ImGuiTypingSelectState TypingSelectState;    // State for GetTypingSelectRequest()

    // Platform support
    ImGuiPlatformImeData PlatformImeData;     // Data updated by current frame
    ImGuiPlatformImeData PlatformImeDataPrev; // Previous frame data. When changed we call the platform_io.Platform_SetImeDataFn() handler.
    ImGuiID PlatformImeViewport;

    // Extensions
    // FIXME: We could provide an API to register one slot in an array held in ImGuiContext?
    ImGuiDockContext DockContext;
    void (*DockNodeWindowMenuHandler)(ImGuiContext *ctx, ImGuiDockNode *node, ImGuiTabBar *tab_bar);

    // Settings
    bool SettingsLoaded;
    float SettingsDirtyTimer;                           // Save .ini Settings to memory when time reaches zero
    ImGuiTextBuffer SettingsIniData;                    // In memory .ini settings
    ImVector<ImGuiSettingsHandler> SettingsHandlers;    // List of .ini settings handlers
    ImChunkStream<ImGuiWindowSettings> SettingsWindows; // ImGuiWindow .ini settings entries
    ImChunkStream<ImGuiTableSettings> SettingsTables;   // ImGuiTable .ini settings entries
    ImVector<ImGuiContextHook> Hooks;                   // Hooks for extensions (e.g. test engine)
    ImGuiID HookIdNext;                                 // Next available HookId

    // Localization
    const char *LocalizationTable[ImGuiLocKey_COUNT];

    // Capture/Logging
    bool LogEnabled;           // Currently capturing
    ImGuiLogType LogType;      // Capture target
    ImFileHandle LogFile;      // If != NULL log to stdout/ file
    ImGuiTextBuffer LogBuffer; // Accumulation buffer when log to clipboard. This is pointer so our GImGui static constructor doesn't call heap allocators.
    const char *LogNextPrefix;
    const char *LogNextSuffix;
    float LogLinePosY;
    bool LogLineFirstItem;
    int LogDepthRef;
    int LogDepthToExpand;
    int LogDepthToExpandDefault; // Default/stored value for LogDepthMaxExpand if not specified in the LogXXX function call.

    // Debug Tools
    // (some of the highly frequently used data are interleaved in other structures above: DebugBreakXXX fields, DebugHookIdInfo, DebugLocateId etc.)
    ImGuiDebugLogFlags DebugLogFlags;
    ImGuiTextBuffer DebugLogBuf;
    ImGuiTextIndex DebugLogIndex;
    ImGuiDebugLogFlags DebugLogAutoDisableFlags;
    ImU8 DebugLogAutoDisableFrames;
    ImU8 DebugLocateFrames;              // For DebugLocateItemOnHover(). This is used together with DebugLocateId which is in a hot/cached spot above.
    bool DebugBreakInLocateId;           // Debug break in ItemAdd() call for g.DebugLocateId.
    ImGuiKeyChord DebugBreakKeyChord;    // = ImGuiKey_Pause
    ImS8 DebugBeginReturnValueCullDepth; // Cycle between 0..9 then wrap around.
    bool DebugItemPickerActive;          // Item picker is active (started with DebugStartItemPicker())
    ImU8 DebugItemPickerMouseButton;
    ImGuiID DebugItemPickerBreakId; // Will call IM_DEBUG_BREAK() when encountering this ID
    float DebugFlashStyleColorTime;
    ImVec4 DebugFlashStyleColorBackup;
    ImGuiMetricsConfig DebugMetricsConfig;
    ImGuiIDStackTool DebugIDStackTool;
    ImGuiDebugAllocInfo DebugAllocInfo;
    ImGuiDockNode *DebugHoveredDockNode; // Hovered dock node.

    // Misc
    float FramerateSecPerFrame[60]; // Calculate estimate of framerate for user over the last 60 frames..
    int FramerateSecPerFrameIdx;
    int FramerateSecPerFrameCount;
    float FramerateSecPerFrameAccum;
    int WantCaptureMouseNextFrame;    // Explicit capture override via SetNextFrameWantCaptureMouse()/SetNextFrameWantCaptureKeyboard(). Default to -1.
    int WantCaptureKeyboardNextFrame; // "
    int WantTextInputNextFrame;
    ImVector<char> TempBuffer; // Temporary text buffer
    char TempKeychordName[64];

    ImGuiContext(ImFontAtlas *shared_font_atlas)
    {
        IO.Ctx = this;
        InputTextState.Ctx = this;

        Initialized = false;
        ConfigFlagsCurrFrame = ConfigFlagsLastFrame = ImGuiConfigFlags_None;
        FontAtlasOwnedByContext = shared_font_atlas ? false : true;
        Font = NULL;
        FontSize = FontBaseSize = FontScale = CurrentDpiScale = 0.0f;
        IO.Fonts = shared_font_atlas ? shared_font_atlas : IM_NEW(ImFontAtlas)();
        Time = 0.0f;
        FrameCount = 0;
        FrameCountEnded = FrameCountPlatformEnded = FrameCountRendered = -1;
        WithinFrameScope = WithinFrameScopeWithImplicitWindow = WithinEndChild = false;
        GcCompactAll = false;
        TestEngineHookItems = false;
        TestEngine = NULL;
        memset(ContextName, 0, sizeof(ContextName));

        InputEventsNextMouseSource = ImGuiMouseSource_Mouse;
        InputEventsNextEventId = 1;

        WindowsActiveCount = 0;
        CurrentWindow = NULL;
        HoveredWindow = NULL;
        HoveredWindowUnderMovingWindow = NULL;
        HoveredWindowBeforeClear = NULL;
        MovingWindow = NULL;
        WheelingWindow = NULL;
        WheelingWindowStartFrame = WheelingWindowScrolledFrame = -1;
        WheelingWindowReleaseTimer = 0.0f;

        DebugDrawIdConflicts = 0;
        DebugHookIdInfo = 0;
        HoveredId = HoveredIdPreviousFrame = 0;
        HoveredIdPreviousFrameItemCount = 0;
        HoveredIdAllowOverlap = false;
        HoveredIdIsDisabled = false;
        HoveredIdTimer = HoveredIdNotActiveTimer = 0.0f;
        ItemUnclipByLog = false;
        ActiveId = 0;
        ActiveIdIsAlive = 0;
        ActiveIdTimer = 0.0f;
        ActiveIdIsJustActivated = false;
        ActiveIdAllowOverlap = false;
        ActiveIdNoClearOnFocusLoss = false;
        ActiveIdHasBeenPressedBefore = false;
        ActiveIdHasBeenEditedBefore = false;
        ActiveIdHasBeenEditedThisFrame = false;
        ActiveIdFromShortcut = false;
        ActiveIdClickOffset = ImVec2(-1, -1);
        ActiveIdWindow = NULL;
        ActiveIdSource = ImGuiInputSource_None;
        ActiveIdMouseButton = -1;
        ActiveIdPreviousFrame = 0;
        ActiveIdPreviousFrameIsAlive = false;
        ActiveIdPreviousFrameHasBeenEditedBefore = false;
        ActiveIdPreviousFrameWindow = NULL;
        LastActiveId = 0;
        LastActiveIdTimer = 0.0f;

        LastKeyboardKeyPressTime = LastKeyModsChangeTime = LastKeyModsChangeFromNoneTime = -1.0;

        ActiveIdUsingNavDirMask = 0x00;
        ActiveIdUsingAllKeyboardKeys = false;

        CurrentFocusScopeId = 0;
        CurrentItemFlags = ImGuiItemFlags_None;
        DebugShowGroupRects = false;

        CurrentViewport = NULL;
        MouseViewport = MouseLastHoveredViewport = NULL;
        PlatformLastFocusedViewportId = 0;
        ViewportCreatedCount = PlatformWindowsCreatedCount = 0;
        ViewportFocusedStampCount = 0;

        NavWindow = NULL;
        NavId = NavFocusScopeId = NavActivateId = NavActivateDownId = NavActivatePressedId = 0;
        NavLayer = ImGuiNavLayer_Main;
        NavNextActivateId = 0;
        NavActivateFlags = NavNextActivateFlags = ImGuiActivateFlags_None;
        NavHighlightActivatedId = 0;
        NavHighlightActivatedTimer = 0.0f;
        NavInputSource = ImGuiInputSource_Keyboard;
        NavLastValidSelectionUserData = ImGuiSelectionUserData_Invalid;
        NavIdIsAlive = false;
        NavMousePosDirty = false;
        NavDisableHighlight = true;
        NavDisableMouseHover = false;

        NavAnyRequest = false;
        NavInitRequest = false;
        NavInitRequestFromMove = false;
        NavMoveSubmitted = false;
        NavMoveScoringItems = false;
        NavMoveForwardToNextFrame = false;
        NavMoveFlags = ImGuiNavMoveFlags_None;
        NavMoveScrollFlags = ImGuiScrollFlags_None;
        NavMoveKeyMods = ImGuiMod_None;
        NavMoveDir = NavMoveDirForDebug = NavMoveClipDir = ImGuiDir_None;
        NavScoringDebugCount = 0;
        NavTabbingDir = 0;
        NavTabbingCounter = 0;

        NavJustMovedFromFocusScopeId = NavJustMovedToId = NavJustMovedToFocusScopeId = 0;
        NavJustMovedToKeyMods = ImGuiMod_None;
        NavJustMovedToIsTabbing = false;
        NavJustMovedToHasSelectionData = false;

        // All platforms use Ctrl+Tab but Ctrl<>Super are swapped on Mac...
        // FIXME: Because this value is stored, it annoyingly interfere with toggling io.ConfigMacOSXBehaviors updating this..
        ConfigNavWindowingKeyNext = IO.ConfigMacOSXBehaviors ? (ImGuiMod_Super | ImGuiKey_Tab) : (ImGuiMod_Ctrl | ImGuiKey_Tab);
        ConfigNavWindowingKeyPrev = IO.ConfigMacOSXBehaviors ? (ImGuiMod_Super | ImGuiMod_Shift | ImGuiKey_Tab) : (ImGuiMod_Ctrl | ImGuiMod_Shift | ImGuiKey_Tab);
        NavWindowingTarget = NavWindowingTargetAnim = NavWindowingListWindow = NULL;
        NavWindowingTimer = NavWindowingHighlightAlpha = 0.0f;
        NavWindowingToggleLayer = false;
        NavWindowingToggleKey = ImGuiKey_None;

        DimBgRatio = 0.0f;

        DragDropActive = DragDropWithinSource = DragDropWithinTarget = false;
        DragDropSourceFlags = ImGuiDragDropFlags_None;
        DragDropSourceFrameCount = -1;
        DragDropMouseButton = -1;
        DragDropTargetId = 0;
        DragDropAcceptFlags = ImGuiDragDropFlags_None;
        DragDropAcceptIdCurrRectSurface = 0.0f;
        DragDropAcceptIdPrev = DragDropAcceptIdCurr = 0;
        DragDropAcceptFrameCount = -1;
        DragDropHoldJustPressedId = 0;
        memset(DragDropPayloadBufLocal, 0, sizeof(DragDropPayloadBufLocal));

        ClipperTempDataStacked = 0;

        CurrentTable = NULL;
        TablesTempDataStacked = 0;
        CurrentTabBar = NULL;
        CurrentMultiSelect = NULL;
        MultiSelectTempDataStacked = 0;

        HoverItemDelayId = HoverItemDelayIdPreviousFrame = HoverItemUnlockedStationaryId = HoverWindowUnlockedStationaryId = 0;
        HoverItemDelayTimer = HoverItemDelayClearTimer = 0.0f;

        MouseCursor = ImGuiMouseCursor_Arrow;
        MouseStationaryTimer = 0.0f;

        TempInputId = 0;
        memset(&DataTypeZeroValue, 0, sizeof(DataTypeZeroValue));
        BeginMenuDepth = BeginComboDepth = 0;
        ColorEditOptions = ImGuiColorEditFlags_DefaultOptions_;
        ColorEditCurrentID = ColorEditSavedID = 0;
        ColorEditSavedHue = ColorEditSavedSat = 0.0f;
        ColorEditSavedColor = 0;
        WindowResizeRelativeMode = false;
        ScrollbarSeekMode = 0;
        ScrollbarClickDeltaToGrabCenter = 0.0f;
        SliderGrabClickOffset = 0.0f;
        SliderCurrentAccum = 0.0f;
        SliderCurrentAccumDirty = false;
        DragCurrentAccumDirty = false;
        DragCurrentAccum = 0.0f;
        DragSpeedDefaultRatio = 1.0f / 100.0f;
        DisabledAlphaBackup = 0.0f;
        DisabledStackSize = 0;
        LockMarkEdited = 0;
        TooltipOverrideCount = 0;

        PlatformImeData.InputPos = ImVec2(0.0f, 0.0f);
        PlatformImeDataPrev.InputPos = ImVec2(-1.0f, -1.0f); // Different to ensure initial submission
        PlatformImeViewport = 0;

        DockNodeWindowMenuHandler = NULL;

        SettingsLoaded = false;
        SettingsDirtyTimer = 0.0f;
        HookIdNext = 0;

        memset(LocalizationTable, 0, sizeof(LocalizationTable));

        LogEnabled = false;
        LogType = ImGuiLogType_None;
        LogNextPrefix = LogNextSuffix = NULL;
        LogFile = NULL;
        LogLinePosY = FLT_MAX;
        LogLineFirstItem = false;
        LogDepthRef = 0;
        LogDepthToExpand = LogDepthToExpandDefault = 2;

        DebugLogFlags = ImGuiDebugLogFlags_OutputToTTY;
        DebugLocateId = 0;
        DebugLogAutoDisableFlags = ImGuiDebugLogFlags_None;
        DebugLogAutoDisableFrames = 0;
        DebugLocateFrames = 0;
        DebugBeginReturnValueCullDepth = -1;
        DebugItemPickerActive = false;
        DebugItemPickerMouseButton = ImGuiMouseButton_Left;
        DebugItemPickerBreakId = 0;
        DebugFlashStyleColorTime = 0.0f;
        DebugFlashStyleColorIdx = ImGuiCol_COUNT;
        DebugHoveredDockNode = NULL;

        // Same as DebugBreakClearData(). Those fields are scattered in their respective subsystem to stay in hot-data locations
        DebugBreakInWindow = 0;
        DebugBreakInTable = 0;
        DebugBreakInLocateId = false;
        DebugBreakKeyChord = ImGuiKey_Pause;
        DebugBreakInShortcutRouting = ImGuiKey_None;

        memset(FramerateSecPerFrame, 0, sizeof(FramerateSecPerFrame));
        FramerateSecPerFrameIdx = FramerateSecPerFrameCount = 0;
        FramerateSecPerFrameAccum = 0.0f;
        WantCaptureMouseNextFrame = WantCaptureKeyboardNextFrame = WantTextInputNextFrame = -1;
        memset(TempKeychordName, 0, sizeof(TempKeychordName));
    }
};