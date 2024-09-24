#pragma once

template <typename T> struct ImVector {
    int Size;
    int Capacity;
    T* Data;

    // Provide standard typedefs but we don't use them ourselves.
    typedef T value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;

    // Constructors, destructor
    inline ImVector();
    inline ImVector(const ImVector<T>& src);
    inline ImVector<T>& operator=(const ImVector<T>& src);

    inline ~ImVector();
    inline void clear();
    inline void clear_delete();
    inline void clear_destruct();
    inline bool empty() const;
    inline int size() const;
    inline int size_in_bytes() const;
    inline int max_size() const;
    inline int capacity() const;
    inline T& operator[](int i);
    inline const T& operator[](int i) const;
    inline T* begin();
    inline const T* begin() const;
    inline T* end();
    inline const T* end() const;
    inline T& front();
    inline const T& front() const;
    inline T& back();
    inline const T& back() const;
    inline void swap(ImVector<T>& rhs);
    inline int _grow_capacity(int sz) const;
    inline void resize(int new_size);
    inline void resize(int new_size, const T& v);
    inline void shrink(int new_size);
    inline void reserve(int new_capacity);
    inline void reserve_discard(int new_capacity);
    inline void push_back(const T& v);
    inline void pop_back();
    inline void push_front(const T& v);
    inline T* erase(const T* it);
    inline T* erase(const T* it, const T* it_last);
    inline T* erase_unsorted(const T* it);
    inline T* insert(const T* it, const T& v);
    inline bool contains(const T& v) const;
    inline T* find(const T& v);
    inline const T* find(const T& v) const;
    inline int find_index(const T& v) const;
    inline bool find_erase(const T& v);
    inline bool find_erase_unsorted(const T& v);
    inline int index_from_ptr(const T* it) const;
};