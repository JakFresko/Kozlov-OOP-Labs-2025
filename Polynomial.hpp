#pragma once
#include "Term.hpp"

class Polynomial {
private:
    Term*  terms;
    int    size;
    int    capacity;
    bool   order;

    void   resize(int new_cap);
    void   add_term(const Term& t);
    void   simplify();
    void   sort();

public:
    Polynomial();
    explicit Polynomial(double coef);
    explicit Polynomial(const Term& t);
    Polynomial(const Polynomial& other);
    ~Polynomial();

    Polynomial& operator=(const Polynomial& other);

    void add(const Term& t);
    void remove(int power);
    void set_order(bool asc);
    double eval(double x) const;

    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs);
    friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs);
    friend Polynomial operator*(Polynomial lhs, const Polynomial& rhs);

    Polynomial& operator+=(const Term& t);
    friend Polynomial operator+(Polynomial p, const Term& t);

    bool operator==(const Polynomial& other) const;

    friend std::istream& operator>>(std::istream& is, Polynomial& p);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
};
