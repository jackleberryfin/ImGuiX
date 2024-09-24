#pragma once

// Helper: ImSpan<>
// Pointing to a span of data we don't own.
template <typename T> struct ImSpan {
    T* Data;
    T* DataEnd;

    // Constructors, destructor
    inline ImSpan();
    inline ImSpan(T* data, int size);
    inline ImSpan(T* data, T* data_end);
    inline void set(T* data, int size);
    inline void set(T* data, T* data_end);
    inline int size() const;
    inline int size_in_bytes() const;
    inline T& operator[](int i);
    inline const T& operator[](int i) const;
    inline T* begin();
    inline const T* begin() const;
    inline T* end();
    inline const T* end() const;
    // Utilities
    inline int index_from_ptr(const T* it) const;
};