#pragma once

class ImVec2
{
    float x, y;
    constexpr ImVec2() : x(0.0f), y(0.0f) {}
    constexpr ImVec2(float _x, float _y) : x(_x), y(_y) {}

    float& operator[](size_t idx);
    float operator[](size_t idx) const;
};