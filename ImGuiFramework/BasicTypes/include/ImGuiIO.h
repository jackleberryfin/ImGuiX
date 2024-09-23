#pragma once

#include "ImTypeDefs.h"
#include "ImVec2.h"
#include "ImFont.h"

struct ImGuiIO
{
    //------------------------------------------------------------------
    // Configuration                            // Default value
    //------------------------------------------------------------------

    ImGuiConfigFlags ConfigFlags;   // = 0              // See ImGuiConfigFlags_ enum. Set by user/application. Gamepad/keyboard navigation options, etc.
    ImGuiBackendFlags BackendFlags; // = 0              // See ImGuiBackendFlags_ enum. Set by backend (imgui_impl_xxx files or custom backend) to communicate features supported by the backend.
    ImVec2 DisplaySize;             // <unset>          // Main display size, in pixels (generally == GetMainViewport()->Size). May change every frame.
    float DeltaTime;                // = 1.0f/60.0f     // Time elapsed since last frame, in seconds. May change every frame.
    float IniSavingRate;            // = 5.0f           // Minimum time between saving positions/sizes to .ini file, in seconds.
    const char *IniFilename;        // = "imgui.ini"    // Path to .ini file (important: default "imgui.ini" is relative to current working dir!). Set NULL to disable automatic .ini loading/saving or if you want to manually call LoadIniSettingsXXX() / SaveIniSettingsXXX() functions.
    const char *LogFilename;        // = "imgui_log.txt"// Path to .log file (default parameter to ImGui::LogToFile when no file is specified).
    void *UserData;                 // = NULL           // Store your own data.

    // Font system
    ImFontAtlas *Fonts;             // <auto>           // Font atlas: load, rasterize and pack one or more fonts into a single texture.
    float FontGlobalScale;          // = 1.0f           // Global scale all fonts
    bool FontAllowUserScaling;      // = false          // Allow user scaling text of individual window with CTRL+Wheel.
    ImFont *FontDefault;            // = NULL           // Font to use on NewFrame(). Use NULL to uses Fonts->Fonts[0].
    ImVec2 DisplayFramebufferScale; // = (1, 1)         // For retina display or other situations where window coordinates are different from framebuffer coordinates. This generally ends up in ImDrawData::FramebufferScale.

    // Docking options (when ImGuiConfigFlags_DockingEnable is set)
    bool ConfigDockingNoSplit;            // = false          // Simplified docking mode: disable window splitting, so docking is limited to merging multiple windows together into tab-bars.
    bool ConfigDockingWithShift;          // = false          // Enable docking with holding Shift key (reduce visual noise, allows dropping in wider space)
    bool ConfigDockingAlwaysTabBar;       // = false          // [BETA] [FIXME: This currently creates regression with auto-sizing and general overhead] Make every single floating window display within a docking node.
    bool ConfigDockingTransparentPayload; // = false          // [BETA] Make window or viewport transparent when docking and only display docking boxes on the target viewport. Useful if rendering of multiple viewport cannot be synced. Best used with ConfigViewportsNoAutoMerge.

    // Viewport options (when ImGuiConfigFlags_ViewportsEnable is set)
    bool ConfigViewportsNoAutoMerge;     // = false;         // Set to make all floating imgui windows always create their own viewport. Otherwise, they are merged into the main host viewports when overlapping it. May also set ImGuiViewportFlags_NoAutoMerge on individual viewport.
    bool ConfigViewportsNoTaskBarIcon;   // = false          // Disable default OS task bar icon flag for secondary viewports. When a viewport doesn't want a task bar icon, ImGuiViewportFlags_NoTaskBarIcon will be set on it.
    bool ConfigViewportsNoDecoration;    // = true           // Disable default OS window decoration flag for secondary viewports. When a viewport doesn't want window decorations, ImGuiViewportFlags_NoDecoration will be set on it. Enabling decoration can create subsequent issues at OS levels (e.g. minimum window size).
    bool ConfigViewportsNoDefaultParent; // = false          // Disable default OS parenting to main viewport for secondary viewports. By default, viewports are marked with ParentViewportId = <main_viewport>, expecting the platform backend to setup a parent/child relationship between the OS windows (some backend may ignore this). Set to true if you want the default to be 0, then all viewports will be top-level OS windows.

    // Miscellaneous options
    // (you can visualize and interact with all options in 'Demo->Configuration')
    bool MouseDrawCursor;                   // = false          // Request ImGui to draw a mouse cursor for you (if you are on a platform without a mouse cursor). Cannot be easily renamed to 'io.ConfigXXX' because this is frequently used by backend implementations.
    bool ConfigMacOSXBehaviors;             // = defined(__APPLE__) // Swap Cmd<>Ctrl keys + OS X style text editing cursor movement using Alt instead of Ctrl, Shortcuts using Cmd/Super instead of Ctrl, Line/Text Start and End using Cmd+Arrows instead of Home/End, Double click selects by word instead of selecting whole text, Multi-selection in lists uses Cmd/Super instead of Ctrl.
    bool ConfigNavSwapGamepadButtons;       // = false          // Swap Activate<>Cancel (A<>B) buttons, matching typical "Nintendo/Japanese style" gamepad layout.
    bool ConfigInputTrickleEventQueue;      // = true           // Enable input queue trickling: some types of events submitted during the same frame (e.g. button down + up) will be spread over multiple frames, improving interactions with low framerates.
    bool ConfigInputTextCursorBlink;        // = true           // Enable blinking cursor (optional as some users consider it to be distracting).
    bool ConfigInputTextEnterKeepActive;    // = false          // [BETA] Pressing Enter will keep item active and select contents (single-line only).
    bool ConfigDragClickToInputText;        // = false          // [BETA] Enable turning DragXXX widgets into text input with a simple mouse click-release (without moving). Not desirable on devices without a keyboard.
    bool ConfigWindowsResizeFromEdges;      // = true           // Enable resizing of windows from their edges and from the lower-left corner. This requires (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors) because it needs mouse cursor feedback. (This used to be a per-window ImGuiWindowFlags_ResizeFromAnySide flag)
    bool ConfigWindowsMoveFromTitleBarOnly; // = false       // Enable allowing to move windows only when clicking on their title bar. Does not apply to windows without a title bar.
    bool ConfigScrollbarScrollByPage;       // = true           // Enable scrolling page by page when clicking outside the scrollbar grab. When disabled, always scroll to clicked location. When enabled, Shift+Click scrolls to clicked location.
    float ConfigMemoryCompactTimer;         // = 60.0f          // Timer (in seconds) to free transient windows/tables memory buffers when unused. Set to -1.0f to disable.

    // Inputs Behaviors
    // (other variables, ones which are expected to be tweaked within UI code, are exposed in ImGuiStyle)
    float MouseDoubleClickTime;    // = 0.30f          // Time for a double-click, in seconds.
    float MouseDoubleClickMaxDist; // = 6.0f           // Distance threshold to stay in to validate a double-click, in pixels.
    float MouseDragThreshold;      // = 6.0f           // Distance threshold before considering we are dragging.
    float KeyRepeatDelay;          // = 0.275f         // When holding a key/button, time before it starts repeating, in seconds (for buttons in Repeat mode, etc.).
    float KeyRepeatRate;           // = 0.050f         // When holding a key/button, rate at which it repeats, in seconds.

    //------------------------------------------------------------------
    // Debug options
    //------------------------------------------------------------------

    // Option to enable various debug tools showing buttons that will call the IM_DEBUG_BREAK() macro.
    // - The Item Picker tool will be available regardless of this being enabled, in order to maximize its discoverability.
    // - Requires a debugger being attached, otherwise IM_DEBUG_BREAK() options will appear to crash your application.
    //   e.g. io.ConfigDebugIsDebuggerPresent = ::IsDebuggerPresent() on Win32, or refer to ImOsIsDebuggerPresent() imgui_test_engine/imgui_te_utils.cpp for a Unix compatible version).
    bool ConfigDebugIsDebuggerPresent; // = false          // Enable various tools calling IM_DEBUG_BREAK().

    // Tools to detect code submitting items with conflicting/duplicate IDs
    // - Code should use PushID()/PopID() in loops, or append "##xx" to same-label identifiers.
    // - Empty label e.g. Button("") == same ID as parent widget/node. Use Button("##xx") instead!
    // - See FAQ https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-about-the-id-stack-system
    bool ConfigDebugHighlightIdConflicts; // = true           // Highlight and show an error message when multiple items have conflicting identifiers.

    // Tools to test correct Begin/End and BeginChild/EndChild behaviors.
    // - Presently Begin()/End() and BeginChild()/EndChild() needs to ALWAYS be called in tandem, regardless of return value of BeginXXX()
    // - This is inconsistent with other BeginXXX functions and create confusion for many users.
    // - We expect to update the API eventually. In the meanwhile we provide tools to facilitate checking user-code behavior.
    bool ConfigDebugBeginReturnValueOnce; // = false          // First-time calls to Begin()/BeginChild() will return false. NEEDS TO BE SET AT APPLICATION BOOT TIME if you don't want to miss windows.
    bool ConfigDebugBeginReturnValueLoop; // = false          // Some calls to Begin()/BeginChild() will return false. Will cycle through window depths then repeat. Suggested use: add "io.ConfigDebugBeginReturnValue = io.KeyShift" in your main loop then occasionally press SHIFT. Windows should be flickering while running.

    // Option to deactivate io.AddFocusEvent(false) handling.
    // - May facilitate interactions with a debugger when focus loss leads to clearing inputs data.
    // - Backends may have other side-effects on focus loss, so this will reduce side-effects but not necessary remove all of them.
    bool ConfigDebugIgnoreFocusLoss; // = false          // Ignore io.AddFocusEvent(false), consequently not calling io.ClearInputKeys()/io.ClearInputMouse() in input processing.

    // Option to audit .ini data
    bool ConfigDebugIniSettings; // = false          // Save .ini data with extra comments (particularly helpful for Docking, but makes saving slower)

    //------------------------------------------------------------------
    // Platform Functions
    // (the imgui_impl_xxxx backend files are setting those up for you)
    //------------------------------------------------------------------

    // Optional: Platform/Renderer backend name (informational only! will be displayed in About Window) + User data for backend/wrappers to store their own stuff.
    const char *BackendPlatformName; // = NULL
    const char *BackendRendererName; // = NULL
    void *BackendPlatformUserData;   // = NULL           // User data for platform backend
    void *BackendRendererUserData;   // = NULL           // User data for renderer backend
    void *BackendLanguageUserData;   // = NULL           // User data for non C++ programming language backend

    //------------------------------------------------------------------
    // Input - Call before calling NewFrame()
    //------------------------------------------------------------------

    // Input Functions
    IMGUI_API void AddKeyEvent(ImGuiKey key, bool down);                // Queue a new key down/up event. Key should be "translated" (as in, generally ImGuiKey_A matches the key end-user would use to emit an 'A' character)
    IMGUI_API void AddKeyAnalogEvent(ImGuiKey key, bool down, float v); // Queue a new key down/up event for analog values (e.g. ImGuiKey_Gamepad_ values). Dead-zones should be handled by the backend.
    IMGUI_API void AddMousePosEvent(float x, float y);                  // Queue a mouse position update. Use -FLT_MAX,-FLT_MAX to signify no mouse (e.g. app not focused and not hovered)
    IMGUI_API void AddMouseButtonEvent(int button, bool down);          // Queue a mouse button change
    IMGUI_API void AddMouseWheelEvent(float wheel_x, float wheel_y);    // Queue a mouse wheel update. wheel_y<0: scroll down, wheel_y>0: scroll up, wheel_x<0: scroll right, wheel_x>0: scroll left.
    IMGUI_API void AddMouseSourceEvent(ImGuiMouseSource source);        // Queue a mouse source change (Mouse/TouchScreen/Pen)
    IMGUI_API void AddMouseViewportEvent(ImGuiID id);                   // Queue a mouse hovered viewport. Requires backend to set ImGuiBackendFlags_HasMouseHoveredViewport to call this (for multi-viewport support).
    IMGUI_API void AddFocusEvent(bool focused);                         // Queue a gain/loss of focus for the application (generally based on OS/platform focus of your window)
    IMGUI_API void AddInputCharacter(unsigned int c);                   // Queue a new character input
    IMGUI_API void AddInputCharacterUTF16(ImWchar16 c);                 // Queue a new character input from a UTF-16 character, it can be a surrogate
    IMGUI_API void AddInputCharactersUTF8(const char *str);             // Queue a new characters input from a UTF-8 string

    IMGUI_API void SetKeyEventNativeData(ImGuiKey key, int native_keycode, int native_scancode, int native_legacy_index = -1); // [Optional] Specify index for legacy <1.87 IsKeyXXX() functions with native indices + specify native keycode, scancode.
    IMGUI_API void SetAppAcceptingEvents(bool accepting_events);                                                               // Set master flag for accepting key/mouse/text events (default to true). Useful if you have native dialog boxes that are interrupting your application loop/refresh, and you want to disable events being queued while your app is frozen.
    IMGUI_API void ClearEventsQueue();                                                                                         // Clear all incoming events.
    IMGUI_API void ClearInputKeys();                                                                                           // Clear current keyboard/gamepad state + current frame text input buffer. Equivalent to releasing all keys/buttons.
    IMGUI_API void ClearInputMouse();                                                                                          // Clear current mouse state.
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    IMGUI_API void ClearInputCharacters(); // [Obsoleted in 1.89.8] Clear the current frame text input buffer. Now included within ClearInputKeys().
#endif

    //------------------------------------------------------------------
    // Output - Updated by NewFrame() or EndFrame()/Render()
    // (when reading from the io.WantCaptureMouse, io.WantCaptureKeyboard flags to dispatch your inputs, it is
    //  generally easier and more correct to use their state BEFORE calling NewFrame(). See FAQ for details!)
    //------------------------------------------------------------------

    bool WantCaptureMouse;     // Set when Dear ImGui will use mouse inputs, in this case do not dispatch them to your main game/application (either way, always pass on mouse inputs to imgui). (e.g. unclicked mouse is hovering over an imgui window, widget is active, mouse was clicked over an imgui window, etc.).
    bool WantCaptureKeyboard;  // Set when Dear ImGui will use keyboard inputs, in this case do not dispatch them to your main game/application (either way, always pass keyboard inputs to imgui). (e.g. InputText active, or an imgui window is focused and navigation is enabled, etc.).
    bool WantTextInput;        // Mobile/console: when set, you may display an on-screen keyboard. This is set by Dear ImGui when it wants textual keyboard input to happen (e.g. when a InputText widget is active).
    bool WantSetMousePos;      // MousePos has been altered, backend should reposition mouse on next frame. Rarely used! Set only when ImGuiConfigFlags_NavEnableSetMousePos flag is enabled.
    bool WantSaveIniSettings;  // When manual .ini load/save is active (io.IniFilename == NULL), this will be set to notify your application that you can call SaveIniSettingsToMemory() and save yourself. Important: clear io.WantSaveIniSettings yourself after saving!
    bool NavActive;            // Keyboard/Gamepad navigation is currently allowed (will handle ImGuiKey_NavXXX events) = a window is focused and it doesn't use the ImGuiWindowFlags_NoNavInputs flag.
    bool NavVisible;           // Keyboard/Gamepad navigation is visible and allowed (will handle ImGuiKey_NavXXX events).
    float Framerate;           // Estimate of application framerate (rolling average over 60 frames, based on io.DeltaTime), in frame per second. Solely for convenience. Slow applications may not want to use a moving average or may want to reset underlying buffers occasionally.
    int MetricsRenderVertices; // Vertices output during last call to Render()
    int MetricsRenderIndices;  // Indices output during last call to Render() = number of triangles * 3
    int MetricsRenderWindows;  // Number of visible windows
    int MetricsActiveWindows;  // Number of active windows
    ImVec2 MouseDelta;         // Mouse delta. Note that this is zero if either current or previous position are invalid (-FLT_MAX,-FLT_MAX), so a disappearing/reappearing mouse won't have a huge delta.

    //------------------------------------------------------------------
    // [Internal] Dear ImGui will maintain those fields. Forward compatibility not guaranteed!
    //------------------------------------------------------------------

    ImGuiContext *Ctx; // Parent UI context (needs to be set explicitly by parent).

    // Main Input State
    // (this block used to be written by backend, since 1.87 it is best to NOT write to those directly, call the AddXXX functions above instead)
    // (reading from those variables is fair game, as they are extremely unlikely to be moving anywhere)
    ImVec2 MousePos;              // Mouse position, in pixels. Set to ImVec2(-FLT_MAX, -FLT_MAX) if mouse is unavailable (on another screen, etc.)
    bool MouseDown[5];            // Mouse buttons: 0=left, 1=right, 2=middle + extras (ImGuiMouseButton_COUNT == 5). Dear ImGui mostly uses left and right buttons. Other buttons allow us to track if the mouse is being used by your application + available to user as a convenience via IsMouse** API.
    float MouseWheel;             // Mouse wheel Vertical: 1 unit scrolls about 5 lines text. >0 scrolls Up, <0 scrolls Down. Hold SHIFT to turn vertical scroll into horizontal scroll.
    float MouseWheelH;            // Mouse wheel Horizontal. >0 scrolls Left, <0 scrolls Right. Most users don't have a mouse with a horizontal wheel, may not be filled by all backends.
    ImGuiMouseSource MouseSource; // Mouse actual input peripheral (Mouse/TouchScreen/Pen).
    ImGuiID MouseHoveredViewport; // (Optional) Modify using io.AddMouseViewportEvent(). With multi-viewports: viewport the OS mouse is hovering. If possible _IGNORING_ viewports with the ImGuiViewportFlags_NoInputs flag is much better (few backends can handle that). Set io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport if you can provide this info. If you don't imgui will infer the value using the rectangles and last focused time of the viewports it knows about (ignoring other OS windows).
    bool KeyCtrl;                 // Keyboard modifier down: Control
    bool KeyShift;                // Keyboard modifier down: Shift
    bool KeyAlt;                  // Keyboard modifier down: Alt
    bool KeySuper;                // Keyboard modifier down: Cmd/Super/Windows

    // Other state maintained from data above + IO function calls
    ImGuiKeyChord KeyMods;                         // Key mods flags (any of ImGuiMod_Ctrl/ImGuiMod_Shift/ImGuiMod_Alt/ImGuiMod_Super flags, same as io.KeyCtrl/KeyShift/KeyAlt/KeySuper but merged into flags. Read-only, updated by NewFrame()
    ImGuiKeyData KeysData[ImGuiKey_KeysData_SIZE]; // Key state for all known keys. Use IsKeyXXX() functions to access this.
    bool WantCaptureMouseUnlessPopupClose;         // Alternative to WantCaptureMouse: (WantCaptureMouse == true && WantCaptureMouseUnlessPopupClose == false) when a click over void is expected to close a popup.
    ImVec2 MousePosPrev;                           // Previous mouse position (note that MouseDelta is not necessary == MousePos-MousePosPrev, in case either position is invalid)
    ImVec2 MouseClickedPos[5];                     // Position at time of clicking
    double MouseClickedTime[5];                    // Time of last click (used to figure out double-click)
    bool MouseClicked[5];                          // Mouse button went from !Down to Down (same as MouseClickedCount[x] != 0)
    bool MouseDoubleClicked[5];                    // Has mouse button been double-clicked? (same as MouseClickedCount[x] == 2)
    ImU16 MouseClickedCount[5];                    // == 0 (not clicked), == 1 (same as MouseClicked[]), == 2 (double-clicked), == 3 (triple-clicked) etc. when going from !Down to Down
    ImU16 MouseClickedLastCount[5];                // Count successive number of clicks. Stays valid after mouse release. Reset after another click is done.
    bool MouseReleased[5];                         // Mouse button went from Down to !Down
    bool MouseDownOwned[5];                        // Track if button was clicked inside a dear imgui window or over void blocked by a popup. We don't request mouse capture from the application if click started outside ImGui bounds.
    bool MouseDownOwnedUnlessPopupClose[5];        // Track if button was clicked inside a dear imgui window.
    bool MouseWheelRequestAxisSwap;                // On a non-Mac system, holding SHIFT requests WheelY to perform the equivalent of a WheelX event. On a Mac system this is already enforced by the system.
    bool MouseCtrlLeftAsRightClick;                // (OSX) Set to true when the current click was a ctrl-click that spawned a simulated right click
    float MouseDownDuration[5];                    // Duration the mouse button has been down (0.0f == just clicked)
    float MouseDownDurationPrev[5];                // Previous time the mouse button has been down
    ImVec2 MouseDragMaxDistanceAbs[5];             // Maximum distance, absolute, on each axis, of how much mouse has traveled from the clicking point
    float MouseDragMaxDistanceSqr[5];              // Squared maximum distance of how much mouse has traveled from the clicking point (used for moving thresholds)
    float PenPressure;                             // Touch/Pen pressure (0.0f to 1.0f, should be >0.0f only when MouseDown[0] == true). Helper storage currently unused by Dear ImGui.
    bool AppFocusLost;                             // Only modify via AddFocusEvent()
    bool AppAcceptingEvents;                       // Only modify via SetAppAcceptingEvents()
    ImS8 BackendUsingLegacyKeyArrays;              // -1: unknown, 0: using AddKeyEvent(), 1: using legacy io.KeysDown[]
    bool BackendUsingLegacyNavInputArray;          // 0: using AddKeyAnalogEvent(), 1: writing to legacy io.NavInputs[] directly
    ImWchar16 InputQueueSurrogate;                 // For AddInputCharacterUTF16()
    ImVector<ImWchar> InputQueueCharacters;        // Queue of _characters_ input (obtained by platform backend). Fill using AddInputCharacter() helper.

    // Legacy: before 1.87, we required backend to fill io.KeyMap[] (imgui->native map) during initialization and io.KeysDown[] (native indices) every frame.
    // This is still temporarily supported as a legacy feature. However the new preferred scheme is for backend to call io.AddKeyEvent().
    //   Old (<1.87):  ImGui::IsKeyPressed(ImGui::GetIO().KeyMap[ImGuiKey_Space]) --> New (1.87+) ImGui::IsKeyPressed(ImGuiKey_Space)
#ifndef IMGUI_DISABLE_OBSOLETE_KEYIO
    int KeyMap[ImGuiKey_COUNT];           // [LEGACY] Input: map of indices into the KeysDown[512] entries array which represent your "native" keyboard state. The first 512 are now unused and should be kept zero. Legacy backend will write into KeyMap[] using ImGuiKey_ indices which are always >512.
    bool KeysDown[ImGuiKey_COUNT];        // [LEGACY] Input: Keyboard keys that are pressed (ideally left in the "native" order your engine has access to keyboard keys, so you can use your own defines/enums for keys). This used to be [512] sized. It is now ImGuiKey_COUNT to allow legacy io.KeysDown[GetKeyIndex(...)] to work without an overflow.
    float NavInputs[ImGuiNavInput_COUNT]; // [LEGACY] Since 1.88, NavInputs[] was removed. Backends from 1.60 to 1.86 won't build. Feed gamepad inputs via io.AddKeyEvent() and ImGuiKey_GamepadXXX enums.
    // void*     ImeWindowHandle;                    // [Obsoleted in 1.87] Set ImGuiViewport::PlatformHandleRaw instead. Set this to your HWND to get automatic IME cursor positioning.
#endif

    // Legacy: before 1.91.1, clipboard functions were stored in ImGuiIO instead of ImGuiPlatformIO.
    // As this is will affect all users of custom engines/backends, we are providing proper legacy redirection (will obsolete).
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    const char *(*GetClipboardTextFn)(void *user_data);
    void (*SetClipboardTextFn)(void *user_data, const char *text);
    void *ClipboardUserData;
#endif

    IMGUI_API ImGuiIO();
};