#pragma once

#include <cmath>

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

static inline float ImPow(float x, float y) {
    return powf(x, y);
} // DragBehaviorT/SliderBehaviorT uses ImPow with either float/double and need the precision

static inline double ImPow(double x, double y) {
    return pow(x, y);
}

static inline float ImLog(float x) {
    return logf(x);
} // DragBehaviorT/SliderBehaviorT uses ImLog with either float/double and need the precision

static inline double ImLog(double x) {
    return log(x);
}

static inline int ImAbs(int x) {
    return x < 0 ? -x : x;
}

static inline float ImAbs(float x) {
    return fabsf(x);
}

static inline double ImAbs(double x) {
    return fabs(x);
}

static inline float ImSign(float x) {
    return (x < 0.0f) ? -1.0f : (x > 0.0f) ? 1.0f : 0.0f;
} // Sign operator - returns -1, 0 or 1 based on sign of argument

static inline double ImSign(double x) {
    return (x < 0.0) ? -1.0 : (x > 0.0) ? 1.0 : 0.0;
}
#ifdef IMGUI_ENABLE_SSE
static inline float ImRsqrt(float x) {
    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
}
#else
static inline float ImRsqrt(float x) {
    return 1.0f / sqrtf(x);
}
#endif
static inline double ImRsqrt(double x) {
    return 1.0 / sqrt(x);
}
#endif
// - ImMin/ImMax/ImClamp/ImLerp/ImSwap are used by widgets which support variety of types: signed/unsigned int/long long
// float/double (Exceptionally using templates here but we could also redefine them for those types)
template <typename T> static inline T ImMin(T lhs, T rhs) {
    return lhs < rhs ? lhs : rhs;
}

template <typename T> static inline T ImMax(T lhs, T rhs) {
    return lhs >= rhs ? lhs : rhs;
}

template <typename T> static inline T ImClamp(T v, T mn, T mx) {
    return (v < mn) ? mn : (v > mx) ? mx : v;
}

template <typename T> static inline T ImLerp(T a, T b, float t) {
    return (T)(a + (b - a) * t);
}

template <typename T> static inline void ImSwap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T> static inline T ImAddClampOverflow(T a, T b, T mn, T mx) {
    if (b < 0 && (a < mn - b))
        return mn;
    if (b > 0 && (a > mx - b))
        return mx;
    return a + b;
}

template <typename T> static inline T ImSubClampOverflow(T a, T b, T mn, T mx) {
    if (b > 0 && (a < mn + b))
        return mn;
    if (b < 0 && (a > mx + b))
        return mx;
    return a - b;
}

// - Misc maths helpers

static inline float ImSaturate(float f) {
    return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f;
}

static inline float ImTrunc(float f) {
    return (float)(int)(f);
}

static inline float ImFloor(float f) {
    return (float)((f >= 0 || (float)(int)f == f) ? (int)f : (int)f - 1);
} // Decent replacement for floorf()

static inline int ImModPositive(int a, int b) {
    return (a + b) % b;
}

static inline float ImLinearSweep(float current, float target, float speed) {
    if (current < target)
        return ImMin(current + speed, target);
    if (current > target)
        return ImMax(current - speed, target);
    return current;
}

static inline float ImLinearRemapClamp(float s0, float s1, float d0, float d1, float x) {
    return ImSaturate((x - s0) / (s1 - s0)) * (d1 - d0) + d0;
}

static inline bool ImIsFloatAboveGuaranteedIntegerPrecision(float f) {
    return f <= -16777216 || f >= 16777216;
}

static inline float ImExponentialMovingAverage(float avg, float sample, int n) {
    avg -= avg / n;
    avg += sample / n;
    return avg;
}