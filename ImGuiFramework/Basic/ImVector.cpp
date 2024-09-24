#include "ImVector.h"

// Constructors, destructor
template <typename T> inline ImVector<T>::ImVector() {
    Size = Capacity = 0;
    Data = NULL;
}

template <typename T> inline ImVector<T>::ImVector(const ImVector<T>& src) {
    Size = Capacity = 0;
    Data = NULL;
    operator=(src);
}

template <typename T> inline ImVector<T>& ImVector<T>::operator=(const ImVector<T>& src) {
    clear();
    resize(src.Size);
    if (src.Data)
        memcpy(Data, src.Data, (size_t)Size * sizeof(T));
    return *this;
}

template <typename T> inline ImVector<T>::~ImVector() {
    if (Data)
        IM_FREE(Data);
} // Important: does not destruct anything

template <typename T> inline void ImVector<T>::clear() {
    if (Data) {
        Size = Capacity = 0;
        IM_FREE(Data);
        Data = NULL;
    }
} // Important: does not destruct anything

template <typename T> inline void ImVector<T>::clear_delete() {
    for (int n = 0; n < Size; n++)
        IM_DELETE(Data[n]);
    clear();
} // Important: never called automatically! always explicit.

template <typename T> inline void ImVector<T>::clear_destruct() {
    for (int n = 0; n < Size; n++)
        Data[n].~T();
    clear();
} // Important: never called automatically! always explicit.

template <typename T> inline bool ImVector<T>::empty() const {
    return Size == 0;
}

template <typename T> inline int ImVector<T>::size() const {
    return Size;
}

template <typename T> inline int ImVector<T>::size_in_bytes() const {
    return Size * (int)sizeof(T);
}

template <typename T> inline int ImVector<T>::max_size() const {
    return 0x7FFFFFFF / (int)sizeof(T);
}

template <typename T> inline int ImVector<T>::capacity() const {
    return Capacity;
}

template <typename T> inline T& ImVector<T>::operator[](int i) {
    IM_ASSERT(i >= 0 && i < Size);
    return Data[i];
}

template <typename T> inline const T& ImVector<T>::operator[](int i) const {
    IM_ASSERT(i >= 0 && i < Size);
    return Data[i];
}

template <typename T> inline T* ImVector<T>::begin() {
    return Data;
}

template <typename T> inline const T* ImVector<T>::begin() const {
    return Data;
}

template <typename T> inline T* ImVector<T>::end() {
    return Data + Size;
}

template <typename T> inline const T* ImVector<T>::end() const {
    return Data + Size;
}

template <typename T> inline T& ImVector<T>::front() {
    IM_ASSERT(Size > 0);
    return Data[0];
}

template <typename T> inline const T& ImVector<T>::front() const {
    IM_ASSERT(Size > 0);
    return Data[0];
}

template <typename T> inline T& ImVector<T>::back() {
    IM_ASSERT(Size > 0);
    return Data[Size - 1];
}

template <typename T> inline const T& ImVector<T>::back() const {
    IM_ASSERT(Size > 0);
    return Data[Size - 1];
}

template <typename T> inline void ImVector<T>::swap(ImVector<T>& rhs) {
    int rhs_size = rhs.Size;
    rhs.Size = Size;
    Size = rhs_size;
    int rhs_cap = rhs.Capacity;
    rhs.Capacity = Capacity;
    Capacity = rhs_cap;
    T* rhs_data = rhs.Data;
    rhs.Data = Data;
    Data = rhs_data;
}

template <typename T> inline int ImVector<T>::_grow_capacity(int sz) const {
    int new_capacity = Capacity ? (Capacity + Capacity / 2) : 8;
    return new_capacity > sz ? new_capacity : sz;
}

template <typename T> inline void ImVector<T>::resize(int new_size) {
    if (new_size > Capacity)
        reserve(_grow_capacity(new_size));
    Size = new_size;
}

template <typename T> inline void ImVector<T>::resize(int new_size, const T& v) {
    if (new_size > Capacity)
        reserve(_grow_capacity(new_size));
    if (new_size > Size)
        for (int n = Size; n < new_size; n++)
            memcpy(&Data[n], &v, sizeof(v));
    Size = new_size;
}

template <typename T> inline void ImVector<T>::shrink(int new_size) {
    IM_ASSERT(new_size <= Size);
    Size = new_size;
} // Resize a vector to a smaller size, guaranteed not to cause a reallocation

template <typename T> inline void ImVector<T>::reserve(int new_capacity) {
    if (new_capacity <= Capacity)
        return;
    T* new_data = (T*)IM_ALLOC((size_t)new_capacity * sizeof(T));
    if (Data) {
        memcpy(new_data, Data, (size_t)Size * sizeof(T));
        IM_FREE(Data);
    }
    Data = new_data;
    Capacity = new_capacity;
}

template <typename T> inline void ImVector<T>::reserve_discard(int new_capacity) {
    if (new_capacity <= Capacity)
        return;
    if (Data)
        IM_FREE(Data);
    Data = (T*)IM_ALLOC((size_t)new_capacity * sizeof(T));
    Capacity = new_capacity;
}

template <typename T>
// NB: It is illegal to call push_back/push_front/insert with a reference pointing inside the ImVector data itself! e.g.
// v.push_back(v[10]) is forbidden.
inline void ImVector<T>::push_back(const T& v) {
    if (Size == Capacity)
        reserve(_grow_capacity(Size + 1));
    memcpy(&Data[Size], &v, sizeof(v));
    Size++;
}

template <typename T> inline void ImVector<T>::pop_back() {
    IM_ASSERT(Size > 0);
    Size--;
}

template <typename T> inline void ImVector<T>::push_front(const T& v) {
    if (Size == 0)
        push_back(v);
    else
        insert(Data, v);
}

template <typename T> inline T* ImVector<T>::erase(const T* it) {
    IM_ASSERT(it >= Data && it < Data + Size);
    const ptrdiff_t off = it - Data;
    memmove(Data + off, Data + off + 1, ((size_t)Size - (size_t)off - 1) * sizeof(T));
    Size--;
    return Data + off;
}

template <typename T> inline T* ImVector<T>::erase(const T* it, const T* it_last) {
    IM_ASSERT(it >= Data && it < Data + Size && it_last >= it && it_last <= Data + Size);
    const ptrdiff_t count = it_last - it;
    const ptrdiff_t off = it - Data;
    memmove(Data + off, Data + off + count, ((size_t)Size - (size_t)off - (size_t)count) * sizeof(T));
    Size -= (int)count;
    return Data + off;
}

template <typename T> inline T* ImVector<T>::erase_unsorted(const T* it) {
    IM_ASSERT(it >= Data && it < Data + Size);
    const ptrdiff_t off = it - Data;
    if (it < Data + Size - 1)
        memcpy(Data + off, Data + Size - 1, sizeof(T));
    Size--;
    return Data + off;
}

template <typename T> inline T* ImVector<T>::insert(const T* it, const T& v) {
    IM_ASSERT(it >= Data && it <= Data + Size);
    const ptrdiff_t off = it - Data;
    if (Size == Capacity)
        reserve(_grow_capacity(Size + 1));
    if (off < (int)Size)
        memmove(Data + off + 1, Data + off, ((size_t)Size - (size_t)off) * sizeof(T));
    memcpy(&Data[off], &v, sizeof(v));
    Size++;
    return Data + off;
}

template <typename T> inline bool ImVector<T>::contains(const T& v) const {
    const T* data = Data;
    const T* data_end = Data + Size;
    while (data < data_end)
        if (*data++ == v)
            return true;
    return false;
}

template <typename T> inline T* ImVector<T>::find(const T& v) {
    T* data = Data;
    const T* data_end = Data + Size;
    while (data < data_end)
        if (*data == v)
            break;
        else
            ++data;
    return data;
}

template <typename T> inline const T* ImVector<T>::find(const T& v) const {
    const T* data = Data;
    const T* data_end = Data + Size;
    while (data < data_end)
        if (*data == v)
            break;
        else
            ++data;
    return data;
}

template <typename T> inline int ImVector<T>::find_index(const T& v) const {
    const T* data_end = Data + Size;
    const T* it = find(v);
    if (it == data_end)
        return -1;
    const ptrdiff_t off = it - Data;
    return (int)off;
}

template <typename T> inline bool ImVector<T>::find_erase(const T& v) {
    const T* it = find(v);
    if (it < Data + Size) {
        erase(it);
        return true;
    }
    return false;
}

template <typename T> inline bool ImVector<T>::find_erase_unsorted(const T& v) {
    const T* it = find(v);
    if (it < Data + Size) {
        erase_unsorted(it);
        return true;
    }
    return false;
}

template <typename T> inline int ImVector<T>::index_from_ptr(const T* it) const {
    IM_ASSERT(it >= Data && it < Data + Size);
    const ptrdiff_t off = it - Data;
    return (int)off;
}