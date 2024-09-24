#pragma once

#include <memory>

#include "Basic/ImTypeDefs.h"

// FIXME: Structures in the union below need to be declared as anonymous unions appears to be an extension?
// Using ImVec2() would fail on Clang 'union member 'MousePos' has a non-trivial default constructor'
struct ImGuiInputEventMousePos
{
    float PosX, PosY;
    ImGuiMouseSource MouseSource;
};
struct ImGuiInputEventMouseWheel
{
    float WheelX, WheelY;
    ImGuiMouseSource MouseSource;
};
struct ImGuiInputEventMouseButton
{
    int Button;
    bool Down;
    ImGuiMouseSource MouseSource;
};
struct ImGuiInputEventMouseViewport
{
    ImGuiID HoveredViewportID;
};
struct ImGuiInputEventKey
{
    ImGuiKey Key;
    bool Down;
    float AnalogValue;
};
struct ImGuiInputEventText
{
    unsigned int Char;
};
struct ImGuiInputEventAppFocused
{
    bool Focused;
};

struct ImGuiInputEvent
{
    ImGuiInputEventType Type;
    ImGuiInputSource Source;
    ImU32 EventId; // Unique, sequential increasing integer to identify an event (if you need to correlate them to other data).
    union
    {
        ImGuiInputEventMousePos MousePos;           // if Type == ImGuiInputEventType_MousePos
        ImGuiInputEventMouseWheel MouseWheel;       // if Type == ImGuiInputEventType_MouseWheel
        ImGuiInputEventMouseButton MouseButton;     // if Type == ImGuiInputEventType_MouseButton
        ImGuiInputEventMouseViewport MouseViewport; // if Type == ImGuiInputEventType_MouseViewport
        ImGuiInputEventKey Key;                     // if Type == ImGuiInputEventType_Key
        ImGuiInputEventText Text;                   // if Type == ImGuiInputEventType_Text
        ImGuiInputEventAppFocused AppFocused;       // if Type == ImGuiInputEventType_Focus
    };
    bool AddedByTestEngine;

    ImGuiInputEvent() { memset(this, 0, sizeof(*this)); }
};