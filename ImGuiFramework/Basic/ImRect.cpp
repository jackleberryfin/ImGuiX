#include "ImRect.h"

#include "ImMathHelpers.h"

ImVec2 ImRect::GetCenter() const {
    return ImVec2((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f);
}

ImVec2 ImRect::GetSize() const {
    return ImVec2(Max.x - Min.x, Max.y - Min.y);
}

float ImRect::GetWidth() const {
    return Max.x - Min.x;
}

float ImRect::GetHeight() const {
    return Max.y - Min.y;
}

float ImRect::GetArea() const {
    return (Max.x - Min.x) * (Max.y - Min.y);
}

ImVec2 ImRect::GetTL() const {
    return Min;
} // Top-left

ImVec2 ImRect::GetTR() const {
    return ImVec2(Max.x, Min.y);
} // Top-right

ImVec2 ImRect::GetBL() const {
    return ImVec2(Min.x, Max.y);
} // Bottom-left

ImVec2 ImRect::GetBR() const {
    return Max;
} // Bottom-right

bool ImRect::Contains(const ImVec2& p) const {
    return p.x >= Min.x && p.y >= Min.y && p.x < Max.x && p.y < Max.y;
}

bool ImRect::Contains(const ImRect& r) const {
    return r.Min.x >= Min.x && r.Min.y >= Min.y && r.Max.x <= Max.x && r.Max.y <= Max.y;
}

bool ImRect::ContainsWithPad(const ImVec2& p, const ImVec2& pad) const {
    return p.x >= Min.x - pad.x && p.y >= Min.y - pad.y && p.x < Max.x + pad.x && p.y < Max.y + pad.y;
}

bool ImRect::Overlaps(const ImRect& r) const {
    return r.Min.y < Max.y && r.Max.y > Min.y && r.Min.x < Max.x && r.Max.x > Min.x;
}

void ImRect::Add(const ImVec2& p) {
    if (Min.x > p.x)
        Min.x = p.x;
    if (Min.y > p.y)
        Min.y = p.y;
    if (Max.x < p.x)
        Max.x = p.x;
    if (Max.y < p.y)
        Max.y = p.y;
}

void ImRect::Add(const ImRect& r) {
    if (Min.x > r.Min.x)
        Min.x = r.Min.x;
    if (Min.y > r.Min.y)
        Min.y = r.Min.y;
    if (Max.x < r.Max.x)
        Max.x = r.Max.x;
    if (Max.y < r.Max.y)
        Max.y = r.Max.y;
}

void ImRect::Expand(const float amount) {
    Min.x -= amount;
    Min.y -= amount;
    Max.x += amount;
    Max.y += amount;
}

void ImRect::Expand(const ImVec2& amount) {
    Min.x -= amount.x;
    Min.y -= amount.y;
    Max.x += amount.x;
    Max.y += amount.y;
}

void ImRect::Translate(const ImVec2& d) {
    Min.x += d.x;
    Min.y += d.y;
    Max.x += d.x;
    Max.y += d.y;
}

void ImRect::TranslateX(float dx) {
    Min.x += dx;
    Max.x += dx;
}

void ImRect::TranslateY(float dy) {
    Min.y += dy;
    Max.y += dy;
}

void ImRect::ClipWith(const ImRect& r) {
    Min = ImMax(Min, r.Min);
    Max = ImMin(Max, r.Max);
} // Simple version, may lead to an inverted rectangle, which is fine for Contains/Overlaps test but not for display.

void ImRect::ClipWithFull(const ImRect& r) {
    Min = ImClamp(Min, r.Min, r.Max);
    Max = ImClamp(Max, r.Min, r.Max);
} // Full version, ensure both points are fully clipped.

void ImRect::Floor() {
    Min.x = IM_TRUNC(Min.x);
    Min.y = IM_TRUNC(Min.y);
    Max.x = IM_TRUNC(Max.x);
    Max.y = IM_TRUNC(Max.y);
}

bool ImRect::IsInverted() const {
    return Min.x > Max.x || Min.y > Max.y;
}

ImVec4 ImRect::ToVec4() const {
    return ImVec4(Min.x, Min.y, Max.x, Max.y);
}