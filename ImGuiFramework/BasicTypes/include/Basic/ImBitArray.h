#pragma once

// Helper: ImBitArray class (wrapper over ImBitArray functions)
// Store 1-bit per value.
template <int BITCOUNT, int OFFSET = 0> class ImBitArray
{
    ImU32 Storage[(BITCOUNT + 31) >> 5];
    ImBitArray() { ClearAllBits(); }
    void ClearAllBits() { memset(Storage, 0, sizeof(Storage)); }
    void SetAllBits() { memset(Storage, 255, sizeof(Storage)); }
    bool TestBit(int n) const;
    void SetBit(int n);
    void ClearBit(int n);
    void SetBitRange(int n, int n2);
    bool operator[](int n) const;
};