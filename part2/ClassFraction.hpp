#pragma once
#include <iostream>
#include <cmath>

class Fraction {
    private:
        int numerator;
        int denominator;

        bool parse(const char*);

    public:
        Fraction();
        Fraction(const char*);
        Fraction(const Fraction&);

        Fraction& operator=(const Fraction&);

        friend std::ostream& operator<<(std::ostream&, const Fraction&);
        friend std::istream& operator>>(std::istream&, Fraction&);

        Fraction(int);
        Fraction(double);

        Fraction& operator+=(const Fraction&);
        friend Fraction operator+(Fraction, const Fraction&);
};
