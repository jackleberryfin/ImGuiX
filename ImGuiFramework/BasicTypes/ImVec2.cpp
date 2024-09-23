#include <assert.h>

#include "ImVec2.h"

#define IM_ASSERT(_EXPR) assert(_EXPR)

float& ImVec2::operator[](size_t idx) {
    IM_ASSERT(idx == 0 || idx == 1);
    return ((float*)(void*)(char*)this)[idx];
} // We very rarely use this [] operator, so the assert overhead is fine.

float ImVec2::operator[](size_t idx) const {
    IM_ASSERT(idx == 0 || idx == 1);
    return ((const float*)(const void*)(const char*)this)[idx];
}
