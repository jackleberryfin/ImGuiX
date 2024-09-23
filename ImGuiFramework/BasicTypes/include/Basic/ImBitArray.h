#pragma once

// Helper: ImBitArray class (wrapper over ImBitArray functions)
// Store 1-bit per value.
template <int BITCOUNT, int OFFSET = 0>
struct ImBitArray
{
    ImU32 Storage[(BITCOUNT + 31) >> 5];
    ImBitArray() { ClearAllBits(); }
    void ClearAllBits() { memset(Storage, 0, sizeof(Storage)); }
    void SetAllBits() { memset(Storage, 255, sizeof(Storage)); }
    bool TestBit(int n) const
    {
        n += OFFSET;
        IM_ASSERT(n >= 0 && n < BITCOUNT);
        return IM_BITARRAY_TESTBIT(Storage, n);
    }
    void SetBit(int n)
    {
        n += OFFSET;
        IM_ASSERT(n >= 0 && n < BITCOUNT);
        ImBitArraySetBit(Storage, n);
    }
    void ClearBit(int n)
    {
        n += OFFSET;
        IM_ASSERT(n >= 0 && n < BITCOUNT);
        ImBitArrayClearBit(Storage, n);
    }
    void SetBitRange(int n, int n2)
    {
        n += OFFSET;
        n2 += OFFSET;
        IM_ASSERT(n >= 0 && n < BITCOUNT && n2 > n && n2 <= BITCOUNT);
        ImBitArraySetBitRange(Storage, n, n2);
    } // Works on range [n..n2)
    bool operator[](int n) const
    {
        n += OFFSET;
        IM_ASSERT(n >= 0 && n < BITCOUNT);
        return IM_BITARRAY_TESTBIT(Storage, n);
    }
};