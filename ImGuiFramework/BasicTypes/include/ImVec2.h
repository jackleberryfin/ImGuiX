#pragma once

#include "ImTypeDefs.h"
#include <assert.h>

#define IM_ASSERT(_EXPR) assert(_EXPR)

struct ImVec2
{
    float x, y;
    constexpr ImVec2() : x(0.0f), y(0.0f) {}
    constexpr ImVec2(float _x, float _y) : x(_x), y(_y) {}

    float &operator[](size_t idx)
    {
        IM_ASSERT(idx == 0 || idx == 1);
        return ((float *)(void *)(char *)this)[idx];
    } // We very rarely use this [] operator, so the assert overhead is fine.

    float operator[](size_t idx) const
    {
        IM_ASSERT(idx == 0 || idx == 1);
        return ((const float *)(const void *)(const char *)this)[idx];
    }
};