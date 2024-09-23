#pragma once

#include <cstdarg>

#include "Basic/ImVector.h"
#include "Basic/ImTypeDefs.h"

// Helper: Growable text buffer for logging/accumulating text
// (this could be called 'ImGuiTextBuilder' / 'ImGuiStringBuilder')
struct ImGuiTextBuffer
{
    ImVector<char> Buf;
    IMGUI_API static char EmptyString[1];

    ImGuiTextBuffer() {}
    inline char operator[](int i) const
    {
        IM_ASSERT(Buf.Data != NULL);
        return Buf.Data[i];
    }
    const char *begin() const { return Buf.Data ? &Buf.front() : EmptyString; }
    const char *end() const { return Buf.Data ? &Buf.back() : EmptyString; } // Buf is zero-terminated, so end() will point on the zero-terminator
    int size() const { return Buf.Size ? Buf.Size - 1 : 0; }
    bool empty() const { return Buf.Size <= 1; }
    void clear() { Buf.clear(); }
    void reserve(int capacity) { Buf.reserve(capacity); }
    const char *c_str() const { return Buf.Data ? Buf.Data : EmptyString; }
    IMGUI_API void append(const char *str, const char *str_end = NULL);
    IMGUI_API void appendf(const char *fmt, ...) IM_FMTARGS(2);
    IMGUI_API void appendfv(const char *fmt, va_list args) IM_FMTLIST(2);
};