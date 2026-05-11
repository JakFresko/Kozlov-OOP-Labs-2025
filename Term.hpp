#pragma once
#include <iostream>

class Polynomial;

class Term {
    friend class Polynomial;
private:
    double coef;
    int    power;
public:
    Term();
    Term(double coef);
    Term(double coef, int power);

    double get_coef()  const { return coef; }
    int    get_power() const { return power; }

    Term operator+(const Term& other) const;

    friend std::istream& operator>>(std::istream& is, Term& t);
    friend std::ostream& operator<<(std::ostream& os, const Term& t);
};
