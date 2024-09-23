#pragma once

// Helper: ImSpan<>
// Pointing to a span of data we don't own.
template <typename T>
struct ImSpan
{
    T *Data;
    T *DataEnd;

    // Constructors, destructor
    inline ImSpan() { Data = DataEnd = NULL; }
    inline ImSpan(T *data, int size)
    {
        Data = data;
        DataEnd = data + size;
    }
    inline ImSpan(T *data, T *data_end)
    {
        Data = data;
        DataEnd = data_end;
    }

    inline void set(T *data, int size)
    {
        Data = data;
        DataEnd = data + size;
    }
    inline void set(T *data, T *data_end)
    {
        Data = data;
        DataEnd = data_end;
    }
    inline int size() const { return (int)(ptrdiff_t)(DataEnd - Data); }
    inline int size_in_bytes() const { return (int)(ptrdiff_t)(DataEnd - Data) * (int)sizeof(T); }
    inline T &operator[](int i)
    {
        T *p = Data + i;
        IM_ASSERT(p >= Data && p < DataEnd);
        return *p;
    }
    inline const T &operator[](int i) const
    {
        const T *p = Data + i;
        IM_ASSERT(p >= Data && p < DataEnd);
        return *p;
    }

    inline T *begin() { return Data; }
    inline const T *begin() const { return Data; }
    inline T *end() { return DataEnd; }
    inline const T *end() const { return DataEnd; }

    // Utilities
    inline int index_from_ptr(const T *it) const
    {
        IM_ASSERT(it >= Data && it < DataEnd);
        const ptrdiff_t off = it - Data;
        return (int)off;
    }
};