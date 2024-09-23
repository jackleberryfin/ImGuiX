#pragma once

#include "ImMathHelpers.h"

class ImVec2 {
    float x, y;

    constexpr ImVec2() : x(0.0f), y(0.0f) {}

    constexpr ImVec2(float _x, float _y) : x(_x), y(_y) {}

    float& operator[](size_t idx);
    float operator[](size_t idx) const;

    static inline ImVec2 ImMin(const ImVec2& lhs, const ImVec2& rhs) {
        return ImVec2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y);
    }

    static inline ImVec2 ImMax(const ImVec2& lhs, const ImVec2& rhs) {
        return ImVec2(lhs.x >= rhs.x ? lhs.x : rhs.x, lhs.y >= rhs.y ? lhs.y : rhs.y);
    }

    static inline ImVec2 ImClamp(const ImVec2& v, const ImVec2& mn, const ImVec2& mx) {
        return ImVec2((v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x : v.x, (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y : v.y);
    }

    static inline ImVec2 ImLerp(const ImVec2& a, const ImVec2& b, float t) {
        return ImVec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
    }

    static inline ImVec2 ImLerp(const ImVec2& a, const ImVec2& b, const ImVec2& t) {
        return ImVec2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y);
    }

    static inline float ImLengthSqr(const ImVec2& lhs) { return (lhs.x * lhs.x) + (lhs.y * lhs.y); }

    static inline float ImInvLength(const ImVec2& lhs, float fail_value) {
        float d = (lhs.x * lhs.x) + (lhs.y * lhs.y);
        if (d > 0.0f)
            return ImRsqrt(d);
        return fail_value;
    }

    static inline ImVec2 ImTrunc(const ImVec2& v) { return ImVec2((float)(int)(v.x), (float)(int)(v.y)); }

    static inline float ImFloor(float f) {
        return (float)((f >= 0 || (float)(int)f == f) ? (int)f : (int)f - 1);
    } // Decent replacement for floorf()

    static inline ImVec2 ImFloor(const ImVec2& v) { return ImVec2(ImFloor(v.x), ImFloor(v.y)); }

    static inline ImVec2 ImRotate(const ImVec2& v, float cos_a, float sin_a) {
        return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a);
    }

    static inline float ImDot(const ImVec2& a, const ImVec2& b) { return a.x * b.x + a.y * b.y; }

    static inline ImVec2 ImMul(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
};
