#pragma once

#include "ImGuiViewport.h"
#include "ImGuiContext.h"
#include "ImGuiPlatformImeData.h"

struct ImGuiPlatformIO
{
    IMGUI_API ImGuiPlatformIO();

    //------------------------------------------------------------------
    // Input - Interface with OS/backends (basic)
    //------------------------------------------------------------------

    // Optional: Access OS clipboard
    // (default to use native Win32 clipboard on Windows, otherwise uses a private clipboard. Override to access OS clipboard on other architectures)
    const char *(*Platform_GetClipboardTextFn)(ImGuiContext *ctx);
    void (*Platform_SetClipboardTextFn)(ImGuiContext *ctx, const char *text);
    void *Platform_ClipboardUserData;

    // Optional: Open link/folder/file in OS Shell
    // (default to use ShellExecuteA() on Windows, system() on Linux/Mac)
    bool (*Platform_OpenInShellFn)(ImGuiContext *ctx, const char *path);
    void *Platform_OpenInShellUserData;

    // Optional: Notify OS Input Method Editor of the screen position of your cursor for text input position (e.g. when using Japanese/Chinese IME on Windows)
    // (default to use native imm32 api on Windows)
    void (*Platform_SetImeDataFn)(ImGuiContext *ctx, ImGuiViewport *viewport, ImGuiPlatformImeData *data);
    void *Platform_ImeUserData;
    // void      (*SetPlatformImeDataFn)(ImGuiViewport* viewport, ImGuiPlatformImeData* data); // [Renamed to platform_io.PlatformSetImeDataFn in 1.91.1]

    // Optional: Platform locale
    // [Experimental] Configure decimal point e.g. '.' or ',' useful for some languages (e.g. German), generally pulled from *localeconv()->decimal_point
    ImWchar Platform_LocaleDecimalPoint; // '.'

    //------------------------------------------------------------------
    // Input - Interface with OS/backends (Multi-Viewport support!)
    //------------------------------------------------------------------

    // For reference, the second column shows which function are generally calling the Platform Functions:
    //   N = ImGui::NewFrame()                        ~ beginning of the dear imgui frame: read info from platform/OS windows (latest size/position)
    //   F = ImGui::Begin(), ImGui::EndFrame()        ~ during the dear imgui frame
    //   U = ImGui::UpdatePlatformWindows()           ~ after the dear imgui frame: create and update all platform/OS windows
    //   R = ImGui::RenderPlatformWindowsDefault()    ~ render
    //   D = ImGui::DestroyPlatformWindows()          ~ shutdown
    // The general idea is that NewFrame() we will read the current Platform/OS state, and UpdatePlatformWindows() will write to it.

    // The handlers are designed so we can mix and match two imgui_impl_xxxx files, one Platform backend and one Renderer backend.
    // Custom engine backends will often provide both Platform and Renderer interfaces together and so may not need to use all functions.
    // Platform functions are typically called _before_ their Renderer counterpart, apart from Destroy which are called the other way.

    // Platform Backend functions (e.g. Win32, GLFW, SDL) ------------------- Called by -----
    void (*Platform_CreateWindow)(ImGuiViewport *vp);                                                                    // . . U . .  // Create a new platform window for the given viewport
    void (*Platform_DestroyWindow)(ImGuiViewport *vp);                                                                   // N . U . D  //
    void (*Platform_ShowWindow)(ImGuiViewport *vp);                                                                      // . . U . .  // Newly created windows are initially hidden so SetWindowPos/Size/Title can be called on them before showing the window
    void (*Platform_SetWindowPos)(ImGuiViewport *vp, ImVec2 pos);                                                        // . . U . .  // Set platform window position (given the upper-left corner of client area)
    ImVec2 (*Platform_GetWindowPos)(ImGuiViewport *vp);                                                                  // N . . . .  //
    void (*Platform_SetWindowSize)(ImGuiViewport *vp, ImVec2 size);                                                      // . . U . .  // Set platform window client area size (ignoring OS decorations such as OS title bar etc.)
    ImVec2 (*Platform_GetWindowSize)(ImGuiViewport *vp);                                                                 // N . . . .  // Get platform window client area size
    void (*Platform_SetWindowFocus)(ImGuiViewport *vp);                                                                  // N . . . .  // Move window to front and set input focus
    bool (*Platform_GetWindowFocus)(ImGuiViewport *vp);                                                                  // . . U . .  //
    bool (*Platform_GetWindowMinimized)(ImGuiViewport *vp);                                                              // N . . . .  // Get platform window minimized state. When minimized, we generally won't attempt to get/set size and contents will be culled more easily
    void (*Platform_SetWindowTitle)(ImGuiViewport *vp, const char *str);                                                 // . . U . .  // Set platform window title (given an UTF-8 string)
    void (*Platform_SetWindowAlpha)(ImGuiViewport *vp, float alpha);                                                     // . . U . .  // (Optional) Setup global transparency (not per-pixel transparency)
    void (*Platform_UpdateWindow)(ImGuiViewport *vp);                                                                    // . . U . .  // (Optional) Called by UpdatePlatformWindows(). Optional hook to allow the platform backend from doing general book-keeping every frame.
    void (*Platform_RenderWindow)(ImGuiViewport *vp, void *render_arg);                                                  // . . . R .  // (Optional) Main rendering (platform side! This is often unused, or just setting a "current" context for OpenGL bindings). 'render_arg' is the value passed to RenderPlatformWindowsDefault().
    void (*Platform_SwapBuffers)(ImGuiViewport *vp, void *render_arg);                                                   // . . . R .  // (Optional) Call Present/SwapBuffers (platform side! This is often unused!). 'render_arg' is the value passed to RenderPlatformWindowsDefault().
    float (*Platform_GetWindowDpiScale)(ImGuiViewport *vp);                                                              // N . . . .  // (Optional) [BETA] FIXME-DPI: DPI handling: Return DPI scale for this viewport. 1.0f = 96 DPI.
    void (*Platform_OnChangedViewport)(ImGuiViewport *vp);                                                               // . F . . .  // (Optional) [BETA] FIXME-DPI: DPI handling: Called during Begin() every time the viewport we are outputting into changes, so backend has a chance to swap fonts to adjust style.
    ImVec4 (*Platform_GetWindowWorkAreaInsets)(ImGuiViewport *vp);                                                       // N . . . .  // (Optional) [BETA] Get initial work area inset for the viewport (won't be covered by main menu bar, dockspace over viewport etc.). Default to (0,0),(0,0). 'safeAreaInsets' in iOS land, 'DisplayCutout' in Android land.
    int (*Platform_CreateVkSurface)(ImGuiViewport *vp, ImU64 vk_inst, const void *vk_allocators, ImU64 *out_vk_surface); // (Optional) For a Vulkan Renderer to call into Platform code (since the surface creation needs to tie them both).

    // Renderer Backend functions (e.g. DirectX, OpenGL, Vulkan) ------------ Called by -----
    void (*Renderer_CreateWindow)(ImGuiViewport *vp);                   // . . U . .  // Create swap chain, frame buffers etc. (called after Platform_CreateWindow)
    void (*Renderer_DestroyWindow)(ImGuiViewport *vp);                  // N . U . D  // Destroy swap chain, frame buffers etc. (called before Platform_DestroyWindow)
    void (*Renderer_SetWindowSize)(ImGuiViewport *vp, ImVec2 size);     // . . U . .  // Resize swap chain, frame buffers etc. (called after Platform_SetWindowSize)
    void (*Renderer_RenderWindow)(ImGuiViewport *vp, void *render_arg); // . . . R .  // (Optional) Clear framebuffer, setup render target, then render the viewport->DrawData. 'render_arg' is the value passed to RenderPlatformWindowsDefault().
    void (*Renderer_SwapBuffers)(ImGuiViewport *vp, void *render_arg);  // . . . R .  // (Optional) Call Present/SwapBuffers. 'render_arg' is the value passed to RenderPlatformWindowsDefault().

    // (Optional) Monitor list
    // - Updated by: app/backend. Update every frame to dynamically support changing monitor or DPI configuration.
    // - Used by: dear imgui to query DPI info, clamp popups/tooltips within same monitor and not have them straddle monitors.
    ImVector<ImGuiPlatformMonitor> Monitors;

    //------------------------------------------------------------------
    // Output - List of viewports to render into platform windows
    //------------------------------------------------------------------

    // Viewports list (the list is updated by calling ImGui::EndFrame or ImGui::Render)
    // (in the future we will attempt to organize this feature to remove the need for a "main viewport")
    ImVector<ImGuiViewport *> Viewports; // Main viewports, followed by all secondary viewports.
};