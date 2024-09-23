#pragma once

#ifndef IMGUI_API
#define IMGUI_API
#endif
#ifndef IMGUI_IMPL_API
#define IMGUI_IMPL_API IMGUI_API
#endif

// Helper: Unicode defines
#define IM_UNICODE_CODEPOINT_INVALID 0xFFFD // Invalid Unicode code point (standard value).
#ifdef IMGUI_USE_WCHAR32
#define IM_UNICODE_CODEPOINT_MAX 0x10FFFF // Maximum Unicode code point supported by this build.
#else
#define IM_UNICODE_CODEPOINT_MAX 0xFFFF // Maximum Unicode code point supported by this build.
#endif

class ImDrawList;
class ImDrawCmd;
class ImGuiInputTextCallbackData;
class ImGuiSizeCallbackData;

// Misc Macros
#define IM_PI 3.14159265358979323846f
#ifdef _WIN32
#define IM_NEWLINE "\r\n" // Play it nice with Windows users (Update: since 2018-05, Notepad finally appears to support Unix-style carriage returns!)
#else
#define IM_NEWLINE "\n"
#endif
#ifndef IM_TABSIZE // Until we move this to runtime and/or add proper tab support, at least allow users to compile-time override
#define IM_TABSIZE (4)
#endif
#define IM_MEMALIGN(_OFF, _ALIGN) (((_OFF) + ((_ALIGN) - 1)) & ~((_ALIGN) - 1))              // Memory align e.g. IM_ALIGN(0,4)=0, IM_ALIGN(1,4)=4, IM_ALIGN(4,4)=4, IM_ALIGN(5,4)=8
#define IM_F32_TO_INT8_UNBOUND(_VAL) ((int)((_VAL) * 255.0f + ((_VAL) >= 0 ? 0.5f : -0.5f))) // Unsaturated, for display purpose
#define IM_F32_TO_INT8_SAT(_VAL) ((int)(ImSaturate(_VAL) * 255.0f + 0.5f))                   // Saturated, always output 0..255
#define IM_TRUNC(_VAL) ((float)(int)(_VAL))                                                  // ImTrunc() is not inlined in MSVC debug builds
#define IM_ROUND(_VAL) ((float)(int)((_VAL) + 0.5f))                                         //
#define IM_STRINGIFY_HELPER(_X) #_X
#define IM_STRINGIFY(_X) IM_STRINGIFY_HELPER(_X) // Preprocessor idiom to stringify e.g. an integer.
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#define IM_FLOOR IM_TRUNC
#endif

#ifndef IM_DRAWLIST_TEX_LINES_WIDTH_MAX
#define IM_DRAWLIST_TEX_LINES_WIDTH_MAX (63)
#endif

typedef unsigned short ImDrawIdx;
typedef void *ImTextureID;
typedef void (*ImDrawCallback)(const ImDrawList *parent_list, const ImDrawCmd *cmd);
typedef __SIZE_TYPE__ size_t;

#ifndef ImTextureID
typedef void *ImTextureID; // Default: store a pointer or an integer fitting in a pointer (most renderer backends are ok with that)
#endif

// ImDrawIdx: vertex index. [Compile-time configurable type]
// - To use 16-bit indices + allow large meshes: backend need to set 'io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset' and handle ImDrawCmd::VtxOffset (recommended).
// - To use 32-bit indices: override with '#define ImDrawIdx unsigned int' in your imconfig.h file.
#ifndef ImDrawIdx
typedef unsigned short ImDrawIdx; // Default: 16-bit (for maximum compatibility with renderer backends)
#endif

// Character types
// (we generally use UTF-8 encoded string in the API. This is storage specifically for a decoded character used for keyboard input and display)
typedef unsigned int ImWchar32;   // A single decoded U32 character/code point. We encode them as multi bytes UTF-8 when used in strings.
typedef unsigned short ImWchar16; // A single decoded U16 character/code point. We encode them as multi bytes UTF-8 when used in strings.
#ifdef IMGUI_USE_WCHAR32          // ImWchar [configurable type: override in imconfig.h with '#define IMGUI_USE_WCHAR32' to support Unicode planes 1-16]
typedef ImWchar32 ImWchar;
#else
typedef ImWchar16 ImWchar;
#endif

// Multi-Selection item index or identifier when using BeginMultiSelect()
// - Used by SetNextItemSelectionUserData() + and inside ImGuiMultiSelectIO structure.
// - Most users are likely to use this store an item INDEX but this may be used to store a POINTER/ID as well. Read comments near ImGuiMultiSelectIO for details.
typedef ImS64 ImGuiSelectionUserData;

// Callback and functions types
typedef int (*ImGuiInputTextCallback)(ImGuiInputTextCallbackData *data); // Callback function for ImGui::InputText()
typedef void (*ImGuiSizeCallback)(ImGuiSizeCallbackData *data);          // Callback function for ImGui::SetNextWindowSizeConstraints()
typedef void *(*ImGuiMemAllocFunc)(size_t sz, void *user_data);          // Function signature for ImGui::SetAllocatorFunctions()
typedef void (*ImGuiMemFreeFunc)(void *ptr, void *user_data);

typedef unsigned int ImGuiID;     // A unique ID used by widgets (typically the result of hashing a stack of string)
typedef signed char ImS8;         // 8-bit signed integer
typedef unsigned char ImU8;       // 8-bit unsigned integer
typedef signed short ImS16;       // 16-bit signed integer
typedef unsigned short ImU16;     // 16-bit unsigned integer
typedef signed int ImS32;         // 32-bit signed integer == int
typedef unsigned int ImU32;       // 32-bit unsigned integer (often used to store packed colors)
typedef signed long long ImS64;   // 64-bit signed integer
typedef unsigned long long ImU64; // 64-bit unsigned integer

enum ImGuiDir : int;            // -> enum ImGuiDir              // Enum: A cardinal direction (Left, Right, Up, Down)
enum ImGuiKey : int;            // -> enum ImGuiKey              // Enum: A key identifier (ImGuiKey_XXX or ImGuiMod_XXX value)
enum ImGuiMouseSource : int;    // -> enum ImGuiMouseSource      // Enum; A mouse input source identifier (Mouse, TouchScreen, Pen)
enum ImGuiSortDirection : ImU8; // -> enum ImGuiSortDirection    // Enum: A sorting direction (ascending or descending)
typedef int ImGuiCol;           // -> enum ImGuiCol_             // Enum: A color identifier for styling
typedef int ImGuiCond;          // -> enum ImGuiCond_            // Enum: A condition for many Set*() functions
typedef int ImGuiDataType;      // -> enum ImGuiDataType_        // Enum: A primary data type
typedef int ImGuiMouseButton;   // -> enum ImGuiMouseButton_     // Enum: A mouse button identifier (0=left, 1=right, 2=middle)
typedef int ImGuiMouseCursor;   // -> enum ImGuiMouseCursor_     // Enum: A mouse cursor shape
typedef int ImGuiStyleVar;      // -> enum ImGuiStyleVar_        // Enum: A variable identifier for styling
typedef int ImGuiTableBgTarget; // -> enum ImGuiTableBgTarget_   // Enum: A color target for TableSetBgColor()

// Flags (declared as int to allow using as flags without overhead, and to not pollute the top of this file)
// - Tip: Use your programming IDE navigation facilities on the names in the _central column_ below to find the actual flags/enum lists!
//   - In Visual Studio: CTRL+comma ("Edit.GoToAll") can follow symbols inside comments, whereas CTRL+F12 ("Edit.GoToImplementation") cannot.
//   - In Visual Studio w/ Visual Assist installed: ALT+G ("VAssistX.GoToImplementation") can also follow symbols inside comments.
//   - In VS Code, CLion, etc.: CTRL+click can follow symbols inside comments.
typedef int ImDrawFlags;           // -> enum ImDrawFlags_          // Flags: for ImDrawList functions
typedef int ImDrawListFlags;       // -> enum ImDrawListFlags_      // Flags: for ImDrawList instance
typedef int ImFontAtlasFlags;      // -> enum ImFontAtlasFlags_     // Flags: for ImFontAtlas build
typedef int ImGuiBackendFlags;     // -> enum ImGuiBackendFlags_    // Flags: for io.BackendFlags
typedef int ImGuiButtonFlags;      // -> enum ImGuiButtonFlags_     // Flags: for InvisibleButton()
typedef int ImGuiChildFlags;       // -> enum ImGuiChildFlags_      // Flags: for BeginChild()
typedef int ImGuiColorEditFlags;   // -> enum ImGuiColorEditFlags_  // Flags: for ColorEdit4(), ColorPicker4() etc.
typedef int ImGuiConfigFlags;      // -> enum ImGuiConfigFlags_     // Flags: for io.ConfigFlags
typedef int ImGuiComboFlags;       // -> enum ImGuiComboFlags_      // Flags: for BeginCombo()
typedef int ImGuiDockNodeFlags;    // -> enum ImGuiDockNodeFlags_   // Flags: for DockSpace()
typedef int ImGuiDragDropFlags;    // -> enum ImGuiDragDropFlags_   // Flags: for BeginDragDropSource(), AcceptDragDropPayload()
typedef int ImGuiFocusedFlags;     // -> enum ImGuiFocusedFlags_    // Flags: for IsWindowFocused()
typedef int ImGuiHoveredFlags;     // -> enum ImGuiHoveredFlags_    // Flags: for IsItemHovered(), IsWindowHovered() etc.
typedef int ImGuiInputFlags;       // -> enum ImGuiInputFlags_      // Flags: for Shortcut(), SetNextItemShortcut()
typedef int ImGuiInputTextFlags;   // -> enum ImGuiInputTextFlags_  // Flags: for InputText(), InputTextMultiline()
typedef int ImGuiItemFlags;        // -> enum ImGuiItemFlags_       // Flags: for PushItemFlag(), shared by all items
typedef int ImGuiKeyChord;         // -> ImGuiKey | ImGuiMod_XXX    // Flags: for IsKeyChordPressed(), Shortcut() etc. an ImGuiKey optionally OR-ed with one or more ImGuiMod_XXX values.
typedef int ImGuiPopupFlags;       // -> enum ImGuiPopupFlags_      // Flags: for OpenPopup*(), BeginPopupContext*(), IsPopupOpen()
typedef int ImGuiMultiSelectFlags; // -> enum ImGuiMultiSelectFlags_// Flags: for BeginMultiSelect()
typedef int ImGuiSelectableFlags;  // -> enum ImGuiSelectableFlags_ // Flags: for Selectable()
typedef int ImGuiSliderFlags;      // -> enum ImGuiSliderFlags_     // Flags: for DragFloat(), DragInt(), SliderFloat(), SliderInt() etc.
typedef int ImGuiTabBarFlags;      // -> enum ImGuiTabBarFlags_     // Flags: for BeginTabBar()
typedef int ImGuiTabItemFlags;     // -> enum ImGuiTabItemFlags_    // Flags: for BeginTabItem()
typedef int ImGuiTableFlags;       // -> enum ImGuiTableFlags_      // Flags: For BeginTable()
typedef int ImGuiTableColumnFlags; // -> enum ImGuiTableColumnFlags_// Flags: For TableSetupColumn()
typedef int ImGuiTableRowFlags;    // -> enum ImGuiTableRowFlags_   // Flags: For TableNextRow()
typedef int ImGuiTreeNodeFlags;    // -> enum ImGuiTreeNodeFlags_   // Flags: for TreeNode(), TreeNodeEx(), CollapsingHeader()
typedef int ImGuiViewportFlags;    // -> enum ImGuiViewportFlags_   // Flags: for ImGuiViewport
typedef int ImGuiWindowFlags;      // -> enum ImGuiWindowFlags_     // Flags: for Begin(), BeginChild()

// Enumerations
// Use your programming IDE "Go to definition" facility on the names of the center columns to find the actual flags/enum lists.
enum ImGuiLocKey : int;         // -> enum ImGuiLocKey              // Enum: a localization entry for translation.
typedef int ImGuiDataAuthority; // -> enum ImGuiDataAuthority_      // Enum: for storing the source authority (dock node vs window) of a field
typedef int ImGuiLayoutType;    // -> enum ImGuiLayoutType_         // Enum: Horizontal or vertical

// Flags
typedef int ImGuiActivateFlags;       // -> enum ImGuiActivateFlags_      // Flags: for navigation/focus function (will be for ActivateItem() later)
typedef int ImGuiDebugLogFlags;       // -> enum ImGuiDebugLogFlags_      // Flags: for ShowDebugLogWindow(), g.DebugLogFlags
typedef int ImGuiFocusRequestFlags;   // -> enum ImGuiFocusRequestFlags_  // Flags: for FocusWindow();
typedef int ImGuiItemStatusFlags;     // -> enum ImGuiItemStatusFlags_    // Flags: for g.LastItemData.StatusFlags
typedef int ImGuiOldColumnFlags;      // -> enum ImGuiOldColumnFlags_     // Flags: for BeginColumns()
typedef int ImGuiNavHighlightFlags;   // -> enum ImGuiNavHighlightFlags_  // Flags: for RenderNavHighlight()
typedef int ImGuiNavMoveFlags;        // -> enum ImGuiNavMoveFlags_       // Flags: for navigation requests
typedef int ImGuiNextItemDataFlags;   // -> enum ImGuiNextItemDataFlags_  // Flags: for SetNextItemXXX() functions
typedef int ImGuiNextWindowDataFlags; // -> enum ImGuiNextWindowDataFlags_// Flags: for SetNextWindowXXX() functions
typedef int ImGuiScrollFlags;         // -> enum ImGuiScrollFlags_        // Flags: for ScrollToItem() and navigation requests
typedef int ImGuiSeparatorFlags;      // -> enum ImGuiSeparatorFlags_     // Flags: for SeparatorEx()
typedef int ImGuiTextFlags;           // -> enum ImGuiTextFlags_          // Flags: for TextEx()
typedef int ImGuiTooltipFlags;        // -> enum ImGuiTooltipFlags_       // Flags: for BeginTooltipEx()
typedef int ImGuiTypingSelectFlags;   // -> enum ImGuiTypingSelectFlags_  // Flags: for GetTypingSelectRequest()
typedef int ImGuiWindowRefreshFlags;  // -> enum ImGuiWindowRefreshFlags_ // Flags: for SetNextWindowRefreshPolicy()

typedef void (*ImGuiErrorLogCallback)(void *user_data, const char *fmt, ...);

// Helpers: ImVec2/ImVec4 operators
// - It is important that we are keeping those disabled by default so they don't leak in user space.
// - This is in order to allow user enabling implicit cast operators between ImVec2/ImVec4 and their own types (using IM_VEC2_CLASS_EXTRA in imconfig.h)
// - Add '#define IMGUI_DEFINE_MATH_OPERATORS' before including this file (or in imconfig.h) to access courtesy maths operators for ImVec2 and ImVec4.
#ifdef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS_IMPLEMENTED
IM_MSVC_RUNTIME_CHECKS_OFF
static inline ImVec2 operator*(const ImVec2 &lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2 operator/(const ImVec2 &lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2 operator+(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2 operator*(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2 operator/(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2 operator-(const ImVec2 &lhs) { return ImVec2(-lhs.x, -lhs.y); }
static inline ImVec2 &operator*=(ImVec2 &lhs, const float rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}
static inline ImVec2 &operator/=(ImVec2 &lhs, const float rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}
static inline ImVec2 &operator+=(ImVec2 &lhs, const ImVec2 &rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
static inline ImVec2 &operator-=(ImVec2 &lhs, const ImVec2 &rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}
static inline ImVec2 &operator*=(ImVec2 &lhs, const ImVec2 &rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs;
}
static inline ImVec2 &operator/=(ImVec2 &lhs, const ImVec2 &rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    return lhs;
}
static inline bool operator==(const ImVec2 &lhs, const ImVec2 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
static inline bool operator!=(const ImVec2 &lhs, const ImVec2 &rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }
static inline ImVec4 operator+(const ImVec4 &lhs, const ImVec4 &rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4 operator-(const ImVec4 &lhs, const ImVec4 &rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4 operator*(const ImVec4 &lhs, const ImVec4 &rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }
static inline bool operator==(const ImVec4 &lhs, const ImVec4 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
static inline bool operator!=(const ImVec4 &lhs, const ImVec4 &rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }
IM_MSVC_RUNTIME_CHECKS_RESTORE
#endif

// Helpers macros to generate 32-bit encoded colors
// User can declare their own format by #defining the 5 _SHIFT/_MASK macros in their imconfig file.
#ifndef IM_COL32_R_SHIFT
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
#define IM_COL32_R_SHIFT 16
#define IM_COL32_G_SHIFT 8
#define IM_COL32_B_SHIFT 0
#define IM_COL32_A_SHIFT 24
#define IM_COL32_A_MASK 0xFF000000
#else
#define IM_COL32_R_SHIFT 0
#define IM_COL32_G_SHIFT 8
#define IM_COL32_B_SHIFT 16
#define IM_COL32_A_SHIFT 24
#define IM_COL32_A_MASK 0xFF000000
#endif
#endif
#define IM_COL32(R, G, B, A) (((ImU32)(A) << IM_COL32_A_SHIFT) | ((ImU32)(B) << IM_COL32_B_SHIFT) | ((ImU32)(G) << IM_COL32_G_SHIFT) | ((ImU32)(R) << IM_COL32_R_SHIFT))
#define IM_COL32_WHITE IM_COL32(255, 255, 255, 255) // Opaque white = 0xFFFFFFFF
#define IM_COL32_BLACK IM_COL32(0, 0, 0, 255)       // Opaque black
#define IM_COL32_BLACK_TRANS IM_COL32(0, 0, 0, 0)   // Transparent black = 0x00000000

// ImDrawList: Lookup table size for adaptive arc drawing, cover full circle.
#ifndef IM_DRAWLIST_ARCFAST_TABLE_SIZE
#define IM_DRAWLIST_ARCFAST_TABLE_SIZE 48 // Number of samples in lookup table.
#endif
#define IM_DRAWLIST_ARCFAST_SAMPLE_MAX IM_DRAWLIST_ARCFAST_TABLE_SIZE // Sample index _PathArcToFastEx() for 360 angle.

// Input function taking an 'ImGuiID owner_id' argument defaults to (ImGuiKeyOwner_Any == 0) aka don't test ownership, which matches legacy behavior.
#define ImGuiKeyOwner_Any ((ImGuiID)0)        // Accept key that have an owner, UNLESS a call to SetKeyOwner() explicitly used ImGuiInputFlags_LockThisFrame or ImGuiInputFlags_LockUntilRelease.
#define ImGuiKeyOwner_NoOwner ((ImGuiID) - 1) // Require key to have no owner.
// #define ImGuiKeyOwner_None ImGuiKeyOwner_NoOwner  // We previously called this 'ImGuiKeyOwner_None' but it was inconsistent with our pattern that _None values == 0 and quite dangerous. Also using _NoOwner makes the IsKeyPressed() calls more explicit.

// Helper Macros
#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR) assert(_EXPR) // You can override the default assert handler by editing imconfig.h
#endif
#define IM_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR) / sizeof(*(_ARR)))) // Size of a static C-style array. Don't use on pointers!
#define IM_UNUSED(_VAR) ((void)(_VAR))                             // Used to silence "unused variable warnings". Often useful as asserts may be stripped out from final builds.

typedef ImS16 ImGuiKeyRoutingIndex;

#include "ImBitArray.h"
#include "ImEnum.h"

// Bit array for named keys
typedef ImBitArray<ImGuiKey_NamedKey_COUNT, -ImGuiKey_NamedKey_BEGIN> ImBitArrayForNamedKeys;