#pragma once
#include <iostream>
#include <cmath>

class Fraction {
    private:
        int numerator;    // может быть отрицательным — хранит знак
        int denominator;  // всегда > 0

        bool parse(const char*);

    public:
        Fraction();
        Fraction(const char*);
        Fraction(const Fraction&);

        Fraction& operator=(const Fraction&);

        friend std::ostream& operator<<(std::ostream&, const Fraction&);
        friend std::istream& operator>>(std::istream&, Fraction&);

        int get_integer() const;
        int get_numerator() const;
        int get_denominator() const;

        friend Fraction operator+(const Fraction&, const Fraction&);
        friend Fraction operator+(const Fraction&, int);
        friend Fraction operator+(int, const Fraction&);
        Fraction& operator+=(const Fraction&);
        Fraction& operator+=(int);
        friend Fraction operator+(const Fraction&, double);
        friend Fraction operator+(double, const Fraction&);
};
