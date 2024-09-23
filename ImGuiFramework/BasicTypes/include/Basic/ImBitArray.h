#pragma once

// #include "Basic/ImTypeDefs.h"
typedef unsigned int
    ImU32; // 32-bit unsigned integer (often used to store packed colors)

// Store 1-bit per value.
template <int BITCOUNT, int OFFSET = 0> class ImBitArray {
    ImU32 Storage[(BITCOUNT + 31) >> 5];

    ImBitArray();
    void ClearAllBits();
    void SetAllBits();
    bool TestBit(int n) const;
    void SetBit(int n);
    void ClearBit(int n);
    void SetBitRange(int n, int n2);
    bool operator[](int n) const;
};