#pragma once

#include <cmath>

#include "ImVec2.h"
#include "ImVec4.h"

// - Wrapper for standard libs functions. (Note that imgui_demo.cpp does _not_ use them to keep the code easy to copy)
#ifndef IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS
#define ImFabs(X) fabsf(X)
#define ImSqrt(X) sqrtf(X)
#define ImFmod(X, Y) fmodf((X), (Y))
#define ImCos(X) cosf(X)
#define ImSin(X) sinf(X)
#define ImAcos(X) acosf(X)
#define ImAtan2(Y, X) atan2f((Y), (X))
#define ImAtof(STR) atof(STR)
#define ImCeil(X) ceilf(X)
static inline float ImPow(float x, float y) { return powf(x, y); } // DragBehaviorT/SliderBehaviorT uses ImPow with either float/double and need the precision
static inline double ImPow(double x, double y) { return pow(x, y); }
static inline float ImLog(float x) { return logf(x); } // DragBehaviorT/SliderBehaviorT uses ImLog with either float/double and need the precision
static inline double ImLog(double x) { return log(x); }
static inline int ImAbs(int x) { return x < 0 ? -x : x; }
static inline float ImAbs(float x) { return fabsf(x); }
static inline double ImAbs(double x) { return fabs(x); }
static inline float ImSign(float x) { return (x < 0.0f) ? -1.0f : (x > 0.0f) ? 1.0f
                                                                             : 0.0f; } // Sign operator - returns -1, 0 or 1 based on sign of argument
static inline double ImSign(double x) { return (x < 0.0) ? -1.0 : (x > 0.0) ? 1.0
                                                                            : 0.0; }
#ifdef IMGUI_ENABLE_SSE
static inline float ImRsqrt(float x) { return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x))); }
#else
static inline float ImRsqrt(float x) { return 1.0f / sqrtf(x); }
#endif
static inline double ImRsqrt(double x) { return 1.0 / sqrt(x); }
#endif
// - ImMin/ImMax/ImClamp/ImLerp/ImSwap are used by widgets which support variety of types: signed/unsigned int/long long float/double
// (Exceptionally using templates here but we could also redefine them for those types)
template <typename T>
static inline T ImMin(T lhs, T rhs) { return lhs < rhs ? lhs : rhs; }
template <typename T>
static inline T ImMax(T lhs, T rhs) { return lhs >= rhs ? lhs : rhs; }
template <typename T>
static inline T ImClamp(T v, T mn, T mx) { return (v < mn) ? mn : (v > mx) ? mx
                                                                           : v; }
template <typename T>
static inline T ImLerp(T a, T b, float t) { return (T)(a + (b - a) * t); }
template <typename T>
static inline void ImSwap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}
template <typename T>
static inline T ImAddClampOverflow(T a, T b, T mn, T mx)
{
    if (b < 0 && (a < mn - b))
        return mn;
    if (b > 0 && (a > mx - b))
        return mx;
    return a + b;
}
template <typename T>
static inline T ImSubClampOverflow(T a, T b, T mn, T mx)
{
    if (b > 0 && (a < mn + b))
        return mn;
    if (b < 0 && (a > mx + b))
        return mx;
    return a - b;
}
// - Misc maths helpers
static inline ImVec2 ImMin(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y); }
static inline ImVec2 ImMax(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x >= rhs.x ? lhs.x : rhs.x, lhs.y >= rhs.y ? lhs.y : rhs.y); }
static inline ImVec2 ImClamp(const ImVec2 &v, const ImVec2 &mn, const ImVec2 &mx) { return ImVec2((v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x
                                                                                                                                     : v.x,
                                                                                                  (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y
                                                                                                                                     : v.y); }
static inline ImVec2 ImLerp(const ImVec2 &a, const ImVec2 &b, float t) { return ImVec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); }
static inline ImVec2 ImLerp(const ImVec2 &a, const ImVec2 &b, const ImVec2 &t) { return ImVec2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y); }
static inline ImVec4 ImLerp(const ImVec4 &a, const ImVec4 &b, float t) { return ImVec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }
static inline float ImSaturate(float f) { return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f
                                                                                : f; }
static inline float ImLengthSqr(const ImVec2 &lhs) { return (lhs.x * lhs.x) + (lhs.y * lhs.y); }
static inline float ImLengthSqr(const ImVec4 &lhs) { return (lhs.x * lhs.x) + (lhs.y * lhs.y) + (lhs.z * lhs.z) + (lhs.w * lhs.w); }
static inline float ImInvLength(const ImVec2 &lhs, float fail_value)
{
    float d = (lhs.x * lhs.x) + (lhs.y * lhs.y);
    if (d > 0.0f)
        return ImRsqrt(d);
    return fail_value;
}
static inline float ImTrunc(float f) { return (float)(int)(f); }
static inline ImVec2 ImTrunc(const ImVec2 &v) { return ImVec2((float)(int)(v.x), (float)(int)(v.y)); }
static inline float ImFloor(float f) { return (float)((f >= 0 || (float)(int)f == f) ? (int)f : (int)f - 1); } // Decent replacement for floorf()
static inline ImVec2 ImFloor(const ImVec2 &v) { return ImVec2(ImFloor(v.x), ImFloor(v.y)); }
static inline int ImModPositive(int a, int b) { return (a + b) % b; }
static inline float ImDot(const ImVec2 &a, const ImVec2 &b) { return a.x * b.x + a.y * b.y; }
static inline ImVec2 ImRotate(const ImVec2 &v, float cos_a, float sin_a) { return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a); }
static inline float ImLinearSweep(float current, float target, float speed)
{
    if (current < target)
        return ImMin(current + speed, target);
    if (current > target)
        return ImMax(current - speed, target);
    return current;
}
static inline float ImLinearRemapClamp(float s0, float s1, float d0, float d1, float x) { return ImSaturate((x - s0) / (s1 - s0)) * (d1 - d0) + d0; }
static inline ImVec2 ImMul(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline bool ImIsFloatAboveGuaranteedIntegerPrecision(float f) { return f <= -16777216 || f >= 16777216; }
static inline float ImExponentialMovingAverage(float avg, float sample, int n)
{
    avg -= avg / n;
    avg += sample / n;
    return avg;
}