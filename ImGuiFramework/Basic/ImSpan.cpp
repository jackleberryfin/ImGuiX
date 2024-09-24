#include "ImSpan.h"

// Constructors, destructor
template <typename T> inline ImSpan<T>::ImSpan() {
    Data = DataEnd = NULL;
}

template <typename T> inline ImSpan<T>::ImSpan(T* data, int size) {
    Data = data;
    DataEnd = data + size;
}

template <typename T> inline ImSpan<T>::ImSpan(T* data, T* data_end) {
    Data = data;
    DataEnd = data_end;
}

template <typename T> inline void ImSpan<T>::set(T* data, int size) {
    Data = data;
    DataEnd = data + size;
}

template <typename T> inline void ImSpan<T>::set(T* data, T* data_end) {
    Data = data;
    DataEnd = data_end;
}

template <typename T> inline int ImSpan<T>::size() const {
    return (int)(ptrdiff_t)(DataEnd - Data);
}

template <typename T> inline int ImSpan<T>::size_in_bytes() const {
    return (int)(ptrdiff_t)(DataEnd - Data) * (int)sizeof(T);
}

template <typename T> inline T& ImSpan<T>::operator[](int i) {
    T* p = Data + i;
    IM_ASSERT(p >= Data && p < DataEnd);
    return *p;
}

template <typename T> inline const T& ImSpan<T>::operator[](int i) const {
    const T* p = Data + i;
    IM_ASSERT(p >= Data && p < DataEnd);
    return *p;
}

template <typename T> inline T* ImSpan<T>::begin() {
    return Data;
}

template <typename T> inline const T* ImSpan<T>::begin() const {
    return Data;
}

template <typename T> inline T* ImSpan<T>::end() {
    return DataEnd;
}

template <typename T> inline const T* ImSpan<T>::end() const {
    return DataEnd;
}

// Utilities
template <typename T> inline int ImSpan<T>::index_from_ptr(const T* it) const {
    IM_ASSERT(it >= Data && it < DataEnd);
    const ptrdiff_t off = it - Data;
    return (int)off;
}