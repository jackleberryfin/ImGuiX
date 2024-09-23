#include <assert.h>

#include "ImBitArray.h"

#define IM_ASSERT(_EXPR) assert(_EXPR)

template <int BITCOUNT, int OFFSET>
void ImBitArray<BITCOUNT, OFFSET>::ClearAllBits() {
    memset(Storage, 0, sizeof(Storage));
}

template <int BITCOUNT, int OFFSET>
void ImBitArray<BITCOUNT, OFFSET>::SetAllBits() {
    memset(Storage, 255, sizeof(Storage));
}

template <int BITCOUNT, int OFFSET> ImBitArray<BITCOUNT, OFFSET>::ImBitArray() {
    ClearAllBits();
}

template <int BITCOUNT, int OFFSET>
bool ImBitArray<BITCOUNT, OFFSET>::TestBit(int n) const {
    n += OFFSET;
    IM_ASSERT(n >= 0 && n < BITCOUNT);
    return IM_BITARRAY_TESTBIT(Storage, n);
}

template <int BITCOUNT, int OFFSET>
void ImBitArray<BITCOUNT, OFFSET>::SetBit(int n) {
    n += OFFSET;
    IM_ASSERT(n >= 0 && n < BITCOUNT);
    ImBitArraySetBit(Storage, n);
}

template <int BITCOUNT, int OFFSET>
void ImBitArray<BITCOUNT, OFFSET>::ClearBit(int n) {
    n += OFFSET;
    IM_ASSERT(n >= 0 && n < BITCOUNT);
    ImBitArrayClearBit(Storage, n);
}

template <int BITCOUNT, int OFFSET>
void ImBitArray<BITCOUNT, OFFSET>::SetBitRange(int n, int n2) {
    n += OFFSET;
    n2 += OFFSET;
    IM_ASSERT(n >= 0 && n < BITCOUNT && n2 > n && n2 <= BITCOUNT);
    ImBitArraySetBitRange(Storage, n, n2);
} // Works on range [n..n2)

template <int BITCOUNT, int OFFSET>
bool ImBitArray<BITCOUNT, OFFSET>::operator[](int n) const {
    n += OFFSET;
    IM_ASSERT(n >= 0 && n < BITCOUNT);
    return IM_BITARRAY_TESTBIT(Storage, n);
}