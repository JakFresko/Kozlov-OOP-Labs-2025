#ifndef CLASSES_TPP
#define CLASSES_TPP

#ifndef CLASSES_HPP_INCLUDED
    #include "classes.hpp"

template <>
inline void set<char*>::sort_data() {
    for (size_t i = 1; i < Base::size; ++i) {
        char* key = Base::pdata[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && std::strcmp(key, Base::pdata[j]) < 0) {
            Base::pdata[j + 1] = Base::pdata[j];
            --j;
        }
        Base::pdata[j + 1] = key;
    }
}

template <>
inline int set<char*>::qfind(char* const& el) const {
    if (Base::size == 0) return -1;
    int lo = 0, hi = static_cast<int>(Base::size) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int cmp = std::strcmp(Base::pdata[mid], el);
        if (cmp == 0)      return mid;
        else if (cmp < 0)  lo = mid + 1;
        else               hi = mid - 1;
    }
    return -1;
}

template <>
inline bool set<char*>::is_element(char* const& el) const {
    return qfind(el) != -1;
}

template <>
inline void set<char*>::push(char* const& el) {
    if (!is_element(el)) {
        Base::push(el);
        sort_data();
    }
}

template <>
inline void set<char*>::pop(char* const& el) {
    int idx = qfind(el);
    if (idx == -1) return;
    Base::pop(static_cast<size_t>(idx));
}

template <>
inline bool set<char*>::operator==(const set<char*>& other) const {
    if (Base::size != other.size) return false;
    for (size_t i = 0; i < Base::size; ++i)
        if (std::strcmp(Base::pdata[i], other.pdata[i]) != 0)
            return false;
    return true;
}

#endif

#include <cstring>
#include <stdexcept>

template <typename T>
void Container<T>::resize(size_t new_cap) {
    if(new_cap < min_cap) {new_cap = min_cap;}
    T* temp = new T[new_cap];
    if(new_cap < capacity) {
        for(size_t i{}; i < new_cap; i++) {temp[i] = pdata[i];}
    }
    else {
        for(size_t i{}; i < capacity; i++) {temp[i] = pdata[i];}
    }
    delete[] pdata;
    pdata = temp;
    capacity = new_cap;
}

template <typename T>
Container<T>::Container(size_t cap) {
    capacity = cap > min_cap ? cap : min_cap;
    size = 0;
    pdata = new T[capacity];
}

template <typename T>
Container<T>::Container(const Container& obj) {
    capacity = obj.capacity;
    size = obj.size;
    pdata = new T[capacity];
    for(size_t i{0}; i < size; i++) {
        pdata[i] = obj.pdata[i];
    }
}

template <typename T>
Container<T>::Container(Container&& obj) noexcept {
    capacity = obj.capacity;
    size = obj.size;
    pdata = obj.pdata;
    obj.capacity = 0;
    obj.size = 0;
    obj.pdata = nullptr;
}

template <typename T>
Container<T>::~Container() {delete[] pdata;}

template <typename T>
Container<T>& Container<T>::operator=(const Container& obj) {
    if(this == &obj) {return *this;}
    delete[] pdata;
    capacity = obj.capacity;
    size = obj.size;
    pdata = new T[capacity];
    for(size_t i{0}; i < size; i++) {
        pdata[i] = obj.pdata[i];
    }
    return *this;
}

template <typename T>
Container<T>& Container<T>::operator=(Container&& obj) noexcept {
    if(this == &obj) {return *this;}
    delete[] pdata;
    size = obj.size;
    capacity = obj.capacity;
    pdata = obj.pdata;
    obj.size = 0;
    obj.capacity = 0;
    obj.pdata = nullptr;
    return *this;
}

template <typename T>
T& Container<T>::operator[](size_t idx) {
    if(idx >= size) {
        throw std::out_of_range("Incorrect index");
    }
    return pdata[idx];
}

template <typename T>
const T& Container<T>::operator[](size_t idx) const{
    if(idx >= size) {
        throw std::out_of_range("Incorrect index");
    }
    return pdata[idx];
}

template <typename T>
void Container<T>::push(const T& el) {
    if(size >= capacity) {resize(capacity * 2);}
    pdata[size++] = el;
}

template <typename T>
void Container<T>::pop(size_t idx) {
    if(idx == size) {
        size--;
        return;
    }
    for(size_t i{idx}; i < size - 1; i++) {
        pdata[i] = pdata[i + 1];
    }
    size--;
    if(size < capacity / 4) {resize(capacity / 2);}
}

template <typename T>
int Container<T>::find(const T& el) const{
    for(size_t i{}; i < size; i++) {
        if(pdata[i] == el) {return i;}
    }
    return -1;
}

template <typename T>
void set<T>::sort_data() {
    for(size_t i = 1; i < Base::size; ++i) {
        T key = Base::pdata[i];
        int j = i - 1;
        while (j >= 0 && key < Base::pdata[j]) {
            Base::pdata[j + 1] = Base::pdata[j];
            --j;
        }
        Base::pdata[j + 1] = key;
    }
}

template <typename T>
int set<T>::qfind(const T& el) const{
    if (Base::size == 0) return -1;
    int lo = 0, hi = Base::size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (Base::pdata[mid] == el) return mid;
        else if (Base::pdata[mid] < el) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

template <typename T>
bool set<T>::is_element(const T& el) const{
    if(qfind(el) == -1) {return false;}
    return true;
}

template <typename T>
void set<T>::push(const T& el) {
    if(!is_element(el)) {
        Base::push(el);
        sort_data();
    }
    return;
}

template <typename T>
void set<T>::pop(const T& el) {
    if(!is_element(el)) {return;}
    int a = qfind(el);
    Base::pop(a);
}

template <typename T>
set<T>& set<T>::operator+=(const set& other) {
    for(size_t i = 0; i < other.size; ++i) push(other.pdata[i]);
    return *this;
}

template <typename T>
set<T>& set<T>::operator-=(const set& other) {
    for(size_t i = 0; i < other.size; ++i) pop(other.pdata[i]);
    return *this;
}

template <typename T>
set<T>& set<T>::operator*=(const set& other) {
    set result;
    for(size_t i{}; i < Base::size; ++i)
        if (other.is_element(Base::pdata[i]))
            result.push(Base::pdata[i]);
    *this = std::move(result);
    return *this;
}

template <typename T>
bool set<T>::operator==(const set& other) const{
    if(this->size != other.size) {return false;}
    for(size_t i{}; i < Base::size; i++) {
        if(this->pdata[i] != other.pdata[i]) {return false;}
    }
    return true;
}

template <typename T>
bool set<T>::operator!=(const set& other) const{
    return(!(*this == other));
}

template <>
inline void set<const char*>::sort_data() {
    for (size_t i = 1; i < Base::size; ++i) {
        const char* key = Base::pdata[i];
        int j = i - 1;
        while (j >= 0 && std::strcmp(key, Base::pdata[j]) < 0) {
            Base::pdata[j + 1] = Base::pdata[j];
            --j;
        }
        Base::pdata[j + 1] = key;
    }
}

template <>
inline int set<const char*>::qfind(const char* const& el) const{
    if (Base::size == 0) return -1;
    int lo = 0, hi = Base::size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int cmp = std::strcmp(Base::pdata[mid], el);
        if (cmp == 0)      return mid;
        else if (cmp < 0)  lo = mid + 1;
        else               hi = mid - 1;
    }
    return -1;
}

template <>
inline bool set<const char*>::is_element(const char* const& el) const{
    return qfind(el) != -1;
}

template <>
inline void set<const char*>::push(const char* const& el) {
    if (!is_element(el)) {
        Base::push(el);
        sort_data();
    }
}

template <>
inline void set<const char*>::pop(const char* const& el) {
    int idx = qfind(el);
    if (idx == -1) return;
    Base::pop(idx);
}

template <>
inline bool set<const char*>::operator==(const set<const char*>& other) const {
    if (Base::size != other.size) return false;
    for (size_t i = 0; i < Base::size; ++i)
        if (std::strcmp(Base::pdata[i], other.pdata[i]) != 0)
            return false;
    return true;
}

template <>
inline void set<char*>::sort_data() {
    for (size_t i = 1; i < Base::size; ++i) {
        char* key = Base::pdata[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && std::strcmp(key, Base::pdata[j]) < 0) {
            Base::pdata[j + 1] = Base::pdata[j];
            --j;
        }
        Base::pdata[j + 1] = key;
    }
}

template <>
inline int set<char*>::qfind(char* const& el) const {
    if (Base::size == 0) return -1;
    int lo = 0, hi = static_cast<int>(Base::size) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int cmp = std::strcmp(Base::pdata[mid], el);
        if (cmp == 0)      return mid;
        else if (cmp < 0)  lo = mid + 1;
        else               hi = mid - 1;
    }
    return -1;
}

template <>
inline bool set<char*>::is_element(char* const& el) const {
    return qfind(el) != -1;
}

template <>
inline void set<char*>::push(char* const& el) {
    if (!is_element(el)) {
        Base::push(el);
        sort_data();
    }
}

template <>
inline void set<char*>::pop(char* const& el) {
    int idx = qfind(el);
    if (idx == -1) return;
    Base::pop(static_cast<size_t>(idx));
}

template <>
inline bool set<char*>::operator==(const set<char*>& other) const {
    if (Base::size != other.size) return false;
    for (size_t i = 0; i < Base::size; ++i)
        if (std::strcmp(Base::pdata[i], other.pdata[i]) != 0)
            return false;
    return true;
}

#endif
