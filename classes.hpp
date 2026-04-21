#pragma once
#include <iostream>
#include <cstring>

template <typename T>
class Container {
    protected:
        T* pdata;
        const static size_t min_cap{4};
        size_t capacity;
        size_t size;
        void resize(size_t);
    public:
        Container(size_t cap = min_cap);
        Container(const Container&);
        Container(Container&&) noexcept;
        virtual ~Container();
        Container& operator=(const Container&);
        Container& operator=(Container&&) noexcept;
        T& operator[](size_t);
        const T& operator[](size_t) const;
        virtual void push(const T&);
        void pop(size_t);
        virtual int find(const T&) const;
        size_t get_size() const {return size;}
};

template <typename T>
class set : public Container<T> {
        using Base = Container<T>;
        void sort_data();
    public:
        set() : Base() {}
        set(size_t cap) : Base(cap) {}
        set(const set& o) : Base(o) {}
        set(set&& o) noexcept : Base(std::move(o)) {}
        set& operator=(const set& o) { Base::operator=(o); return *this; }
        set& operator=(set&& o) noexcept { Base::operator=(std::move(o)); return *this; }
        int qfind(const T&) const;
        bool is_element(const T&) const;
        int find(const T& el) const override { return qfind(el); }
        void push(const T&) override;
        void pop(const T&);
        set& operator+=(const set& other);
        set& operator-=(const set& other);
        set& operator*=(const set& other);
        friend set operator+(set lhs, const set& rhs) { lhs += rhs; return lhs; }
        friend set operator-(set lhs, const set& rhs) { lhs -= rhs; return lhs; }
        friend set operator*(set lhs, const set& rhs) { lhs *= rhs; return lhs; }
        bool operator==(const set&) const;
        bool operator!=(const set&) const;
        friend std::ostream& operator<<(std::ostream& os, const set<T>& s) {
            os << '{';
            for (std::size_t i = 0; i < s.size; ++i) {
                if (i) os << ", ";
                os << s.pdata[i];
            }
            return os << '}';
        }
};

#define CLASSES_HPP_INCLUDED
#include "classes.tpp"
