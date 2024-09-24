#pragma once

#include "Basic/ImVec2.h"
#include "Basic/ImVec4.h"
#include "Basic/ImTypeDefs.h"
#include "Basic/ImEnum.h"

struct ImGuiStyle
{
    float Alpha;                        // Global alpha applies to everything in Dear ImGui.
    float DisabledAlpha;                // Additional alpha multiplier applied by BeginDisabled(). Multiply over current value of Alpha.
    ImVec2 WindowPadding;               // Padding within a window.
    float WindowRounding;               // Radius of window corners rounding. Set to 0.0f to have rectangular windows. Large values tend to lead to variety of artifacts and are not recommended.
    float WindowBorderSize;             // Thickness of border around windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2 WindowMinSize;               // Minimum window size. This is a global setting. If you want to constrain individual windows, use SetNextWindowSizeConstraints().
    ImVec2 WindowTitleAlign;            // Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
    ImGuiDir WindowMenuButtonPosition;  // Side of the collapsing/docking button in the title bar (None/Left/Right). Defaults to ImGuiDir_Left.
    float ChildRounding;                // Radius of child window corners rounding. Set to 0.0f to have rectangular windows.
    float ChildBorderSize;              // Thickness of border around child windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    float PopupRounding;                // Radius of popup window corners rounding. (Note that tooltip windows use WindowRounding)
    float PopupBorderSize;              // Thickness of border around popup/tooltip windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2 FramePadding;                // Padding within a framed rectangle (used by most widgets).
    float FrameRounding;                // Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
    float FrameBorderSize;              // Thickness of border around frames. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2 ItemSpacing;                 // Horizontal and vertical spacing between widgets/lines.
    ImVec2 ItemInnerSpacing;            // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label).
    ImVec2 CellPadding;                 // Padding within a table cell. Cellpadding.x is locked for entire table. CellPadding.y may be altered between different rows.
    ImVec2 TouchExtraPadding;           // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
    float IndentSpacing;                // Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
    float ColumnsMinSpacing;            // Minimum horizontal spacing between two columns. Preferably > (FramePadding.x + 1).
    float ScrollbarSize;                // Width of the vertical scrollbar, Height of the horizontal scrollbar.
    float ScrollbarRounding;            // Radius of grab corners for scrollbar.
    float GrabMinSize;                  // Minimum width/height of a grab box for slider/scrollbar.
    float GrabRounding;                 // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    float LogSliderDeadzone;            // The size in pixels of the dead-zone around zero on logarithmic sliders that cross zero.
    float TabRounding;                  // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
    float TabBorderSize;                // Thickness of border around tabs.
    float TabMinWidthForCloseButton;    // Minimum width for close button to appear on an unselected tab when hovered. Set to 0.0f to always show when hovering, set to FLT_MAX to never show close button unless selected.
    float TabBarBorderSize;             // Thickness of tab-bar separator, which takes on the tab active color to denote focus.
    float TabBarOverlineSize;           // Thickness of tab-bar overline, which highlights the selected tab-bar.
    float TableAngledHeadersAngle;      // Angle of angled headers (supported values range from -50.0f degrees to +50.0f degrees).
    ImVec2 TableAngledHeadersTextAlign; // Alignment of angled headers within the cell
    ImGuiDir ColorButtonPosition;       // Side of the color button in the ColorEdit4 widget (left/right). Defaults to ImGuiDir_Right.
    ImVec2 ButtonTextAlign;             // Alignment of button text when button is larger than text. Defaults to (0.5f, 0.5f) (centered).
    ImVec2 SelectableTextAlign;         // Alignment of selectable text. Defaults to (0.0f, 0.0f) (top-left aligned). It's generally important to keep this left-aligned if you want to lay multiple items on a same line.
    float SeparatorTextBorderSize;      // Thickness of border in SeparatorText()
    ImVec2 SeparatorTextAlign;          // Alignment of text within the separator. Defaults to (0.0f, 0.5f) (left aligned, center).
    ImVec2 SeparatorTextPadding;        // Horizontal offset of text from each edge of the separator + spacing on other axis. Generally small values. .y is recommended to be == FramePadding.y.
    ImVec2 DisplayWindowPadding;        // Apply to regular windows: amount which we enforce to keep visible when moving near edges of your screen.
    ImVec2 DisplaySafeAreaPadding;      // Apply to every windows, menus, popups, tooltips: amount where we avoid displaying contents. Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).
    float DockingSeparatorSize;         // Thickness of resizing border between docked windows
    float MouseCursorScale;             // Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). We apply per-monitor DPI scaling over this scale. May be removed later.
    bool AntiAliasedLines;              // Enable anti-aliased lines/borders. Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
    bool AntiAliasedLinesUseTex;        // Enable anti-aliased lines/borders using textures where possible. Require backend to render with bilinear filtering (NOT point/nearest filtering). Latched at the beginning of the frame (copied to ImDrawList).
    bool AntiAliasedFill;               // Enable anti-aliased edges around filled shapes (rounded rectangles, circles, etc.). Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
    float CurveTessellationTol;         // Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
    float CircleTessellationMaxError;   // Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled() or drawing rounded corner rectangles with no explicit segment count specified. Decrease for higher quality but more geometry.
    ImVec4 Colors[ImGuiCol_COUNT];

    // Behaviors
    // (It is possible to modify those fields mid-frame if specific behavior need it, unlike e.g. configuration fields in ImGuiIO)
    float HoverStationaryDelay;                  // Delay for IsItemHovered(ImGuiHoveredFlags_Stationary). Time required to consider mouse stationary.
    float HoverDelayShort;                       // Delay for IsItemHovered(ImGuiHoveredFlags_DelayShort). Usually used along with HoverStationaryDelay.
    float HoverDelayNormal;                      // Delay for IsItemHovered(ImGuiHoveredFlags_DelayNormal). "
    ImGuiHoveredFlags HoverFlagsForTooltipMouse; // Default flags when using IsItemHovered(ImGuiHoveredFlags_ForTooltip) or BeginItemTooltip()/SetItemTooltip() while using mouse.
    ImGuiHoveredFlags HoverFlagsForTooltipNav;   // Default flags when using IsItemHovered(ImGuiHoveredFlags_ForTooltip) or BeginItemTooltip()/SetItemTooltip() while using keyboard/gamepad.

    IMGUI_API ImGuiStyle();
    IMGUI_API void ScaleAllSizes(float scale_factor);
};