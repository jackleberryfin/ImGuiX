#pragma once

#include "ImVec2.h"
#include "ImDrawData.h"
#include "ImTypeDefs.h"
#include <memory>

struct ImGuiViewport
{
    ImGuiID ID;               // Unique identifier for the viewport
    ImGuiViewportFlags Flags; // See ImGuiViewportFlags_
    ImVec2 Pos;               // Main Area: Position of the viewport (Dear ImGui coordinates are the same as OS desktop/native coordinates)
    ImVec2 Size;              // Main Area: Size of the viewport.
    ImVec2 WorkPos;           // Work Area: Position of the viewport minus task bars, menus bars, status bars (>= Pos)
    ImVec2 WorkSize;          // Work Area: Size of the viewport minus task bars, menu bars, status bars (<= Size)
    float DpiScale;           // 1.0f = 96 DPI = No extra scale.
    ImGuiID ParentViewportId; // (Advanced) 0: no parent. Instruct the platform backend to setup a parent/child relationship between platform windows.
    ImDrawData *DrawData;     // The ImDrawData corresponding to this viewport. Valid after Render() and until the next call to NewFrame().

    // Platform/Backend Dependent Data
    // Our design separate the Renderer and Platform backends to facilitate combining default backends with each others.
    // When our create your own backend for a custom engine, it is possible that both Renderer and Platform will be handled
    // by the same system and you may not need to use all the UserData/Handle fields.
    // The library never uses those fields, they are merely storage to facilitate backend implementation.
    void *RendererUserData;     // void* to hold custom data structure for the renderer (e.g. swap chain, framebuffers etc.). generally set by your Renderer_CreateWindow function.
    void *PlatformUserData;     // void* to hold custom data structure for the OS / platform (e.g. windowing info, render context). generally set by your Platform_CreateWindow function.
    void *PlatformHandle;       // void* to hold higher-level, platform window handle (e.g. HWND, GLFWWindow*, SDL_Window*), for FindViewportByPlatformHandle().
    void *PlatformHandleRaw;    // void* to hold lower-level, platform-native window handle (under Win32 this is expected to be a HWND, unused for other platforms), when using an abstraction layer like GLFW or SDL (where PlatformHandle would be a SDL_Window*)
    bool PlatformWindowCreated; // Platform window has been created (Platform_CreateWindow() has been called). This is false during the first frame where a viewport is being created.
    bool PlatformRequestMove;   // Platform window requested move (e.g. window was moved by the OS / host window manager, authoritative position will be OS window position)
    bool PlatformRequestResize; // Platform window requested resize (e.g. window was resized by the OS / host window manager, authoritative size will be OS window size)
    bool PlatformRequestClose;  // Platform window requested closure (e.g. window was moved by the OS / host window manager, e.g. pressing ALT-F4)

    ImGuiViewport() { memset(this, 0, sizeof(*this)); }
    ~ImGuiViewport() { IM_ASSERT(PlatformUserData == NULL && RendererUserData == NULL); }

    // Helpers
    ImVec2 GetCenter() const { return ImVec2(Pos.x + Size.x * 0.5f, Pos.y + Size.y * 0.5f); }
    ImVec2 GetWorkCenter() const { return ImVec2(WorkPos.x + WorkSize.x * 0.5f, WorkPos.y + WorkSize.y * 0.5f); }
};