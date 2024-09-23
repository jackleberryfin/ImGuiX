#pragma once

struct ImVec1
{
    float x;
    constexpr ImVec1() : x(0.0f) {}
    constexpr ImVec1(float _x) : x(_x) {}
};