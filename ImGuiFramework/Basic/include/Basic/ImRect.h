#pragma once

#include "ImTypes.h"
#include "ImVec2.h"
#include "ImVec4.h"

// Helper: ImRect (2D axis aligned bounding-box)
// NB: we can't rely on ImVec2 math operators being available here!
struct IMGUI_API ImRect {
    ImVec2 Min; // Upper-left
    ImVec2 Max; // Lower-right

    constexpr ImRect() : Min(0.0f, 0.0f), Max(0.0f, 0.0f) {}

    constexpr ImRect(const ImVec2& min, const ImVec2& max) : Min(min), Max(max) {}

    constexpr ImRect(const ImVec4& v) : Min(v.x, v.y), Max(v.z, v.w) {}

    constexpr ImRect(float x1, float y1, float x2, float y2) : Min(x1, y1), Max(x2, y2) {}

    ImVec2 GetCenter() const;
    ImVec2 GetSize() const;
    float GetWidth() const;
    float GetHeight() const;
    float GetArea() const;
    ImVec2 GetTL() const;
    ImVec2 GetTR() const;
    ImVec2 GetBL() const;
    ImVec2 GetBR() const;
    bool Contains(const ImVec2& p) const;
    bool Contains(const ImRect& r) const;
    bool ContainsWithPad(const ImVec2& p, const ImVec2& pad) const;
    bool Overlaps(const ImRect& r) const;
    void Add(const ImVec2& p);
    void Add(const ImRect& r);
    void Expand(const float amount);
    void Expand(const ImVec2& amount);
    void Translate(const ImVec2& d);
    void TranslateX(float dx);
    void TranslateY(float dy);
    void ClipWith(const ImRect& r);
    void ClipWithFull(const ImRect& r);
    void Floor();
    bool IsInverted() const;
    ImVec4 ToVec4() const;
};