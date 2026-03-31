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

        Fraction operator+(const Fraction&) const;
        Fraction operator+(int) const;
        friend Fraction operator+(int, const Fraction&);
        Fraction& operator+=(const Fraction&);
        Fraction& operator+=(int);
        Fraction operator+(double) const;
        friend Fraction operator+(double, const Fraction&);

};
