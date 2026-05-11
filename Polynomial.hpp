#pragma once
#include "Term.hpp"

class Polynomial {
private:
    Term*  terms;
    int    size;
    int    capacity;
    bool   order;   // true — возрастание, false — убывание

    void   resize(int new_cap);
    void   add_term(const Term& t);   // добавить и привести подобные
    void   simplify();                // объединить одинаковые степени
    void   sort();                    // сортировка по степени

public:
    // ---- конструкторы / деструктор ----
    Polynomial();
    explicit Polynomial(double coef);
    explicit Polynomial(const Term& t);
    Polynomial(const Polynomial& other);
    ~Polynomial();

    // ---- присваивание ----
    Polynomial& operator=(const Polynomial& other);

    // ---- изменение ----
    void add(const Term& t);
    void remove(int power);          // удалить член с данной степенью
    void set_order(bool asc);        // true — возрастание

    // ---- вычисление ----
    double eval(double x) const;

    // ---- арифметика ----
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs);
    friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs);
    friend Polynomial operator*(Polynomial lhs, const Polynomial& rhs);

    // сложение с отдельным термом
    Polynomial& operator+=(const Term& t);
    friend Polynomial operator+(Polynomial p, const Term& t);

    // ---- сравнение ----
    bool operator==(const Polynomial& other) const;

    // ---- ввод / вывод ----
    friend std::istream& operator>>(std::istream& is, Polynomial& p);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
};
