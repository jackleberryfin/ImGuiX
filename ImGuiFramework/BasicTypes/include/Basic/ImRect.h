#pragma once

#include "ImVec2.h"
#include "ImVec4.h"
#include "ImMathHelpers.h"
#include "ImTypeDefs.h"

// Helper: ImRect (2D axis aligned bounding-box)
// NB: we can't rely on ImVec2 math operators being available here!
struct IMGUI_API ImRect
{
    ImVec2 Min; // Upper-left
    ImVec2 Max; // Lower-right

    constexpr ImRect() : Min(0.0f, 0.0f), Max(0.0f, 0.0f) {}
    constexpr ImRect(const ImVec2 &min, const ImVec2 &max) : Min(min), Max(max) {}
    constexpr ImRect(const ImVec4 &v) : Min(v.x, v.y), Max(v.z, v.w) {}
    constexpr ImRect(float x1, float y1, float x2, float y2) : Min(x1, y1), Max(x2, y2) {}

    ImVec2 GetCenter() const { return ImVec2((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f); }
    ImVec2 GetSize() const { return ImVec2(Max.x - Min.x, Max.y - Min.y); }
    float GetWidth() const { return Max.x - Min.x; }
    float GetHeight() const { return Max.y - Min.y; }
    float GetArea() const { return (Max.x - Min.x) * (Max.y - Min.y); }
    ImVec2 GetTL() const { return Min; }                  // Top-left
    ImVec2 GetTR() const { return ImVec2(Max.x, Min.y); } // Top-right
    ImVec2 GetBL() const { return ImVec2(Min.x, Max.y); } // Bottom-left
    ImVec2 GetBR() const { return Max; }                  // Bottom-right
    bool Contains(const ImVec2 &p) const { return p.x >= Min.x && p.y >= Min.y && p.x < Max.x && p.y < Max.y; }
    bool Contains(const ImRect &r) const { return r.Min.x >= Min.x && r.Min.y >= Min.y && r.Max.x <= Max.x && r.Max.y <= Max.y; }
    bool ContainsWithPad(const ImVec2 &p, const ImVec2 &pad) const { return p.x >= Min.x - pad.x && p.y >= Min.y - pad.y && p.x < Max.x + pad.x && p.y < Max.y + pad.y; }
    bool Overlaps(const ImRect &r) const { return r.Min.y < Max.y && r.Max.y > Min.y && r.Min.x < Max.x && r.Max.x > Min.x; }
    void Add(const ImVec2 &p)
    {
        if (Min.x > p.x)
            Min.x = p.x;
        if (Min.y > p.y)
            Min.y = p.y;
        if (Max.x < p.x)
            Max.x = p.x;
        if (Max.y < p.y)
            Max.y = p.y;
    }
    void Add(const ImRect &r)
    {
        if (Min.x > r.Min.x)
            Min.x = r.Min.x;
        if (Min.y > r.Min.y)
            Min.y = r.Min.y;
        if (Max.x < r.Max.x)
            Max.x = r.Max.x;
        if (Max.y < r.Max.y)
            Max.y = r.Max.y;
    }
    void Expand(const float amount)
    {
        Min.x -= amount;
        Min.y -= amount;
        Max.x += amount;
        Max.y += amount;
    }
    void Expand(const ImVec2 &amount)
    {
        Min.x -= amount.x;
        Min.y -= amount.y;
        Max.x += amount.x;
        Max.y += amount.y;
    }
    void Translate(const ImVec2 &d)
    {
        Min.x += d.x;
        Min.y += d.y;
        Max.x += d.x;
        Max.y += d.y;
    }
    void TranslateX(float dx)
    {
        Min.x += dx;
        Max.x += dx;
    }
    void TranslateY(float dy)
    {
        Min.y += dy;
        Max.y += dy;
    }
    void ClipWith(const ImRect &r)
    {
        Min = ImMax(Min, r.Min);
        Max = ImMin(Max, r.Max);
    } // Simple version, may lead to an inverted rectangle, which is fine for Contains/Overlaps test but not for display.
    void ClipWithFull(const ImRect &r)
    {
        Min = ImClamp(Min, r.Min, r.Max);
        Max = ImClamp(Max, r.Min, r.Max);
    } // Full version, ensure both points are fully clipped.
    void Floor()
    {
        Min.x = IM_TRUNC(Min.x);
        Min.y = IM_TRUNC(Min.y);
        Max.x = IM_TRUNC(Max.x);
        Max.y = IM_TRUNC(Max.y);
    }
    bool IsInverted() const { return Min.x > Max.x || Min.y > Max.y; }
    ImVec4 ToVec4() const { return ImVec4(Min.x, Min.y, Max.x, Max.y); }
};