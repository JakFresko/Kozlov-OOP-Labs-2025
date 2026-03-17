#include "AuxiliaryFunctions.hpp"
#include "ClassFraction.hpp"

namespace {
    const int kNumberDecimalPlaces = 4;
}

Fraction::Fraction() {
    integer = 0;
    numerator = 0;
    denominator = 0;
}

Fraction::Fraction(const char* str) {
    if(!this->parse(str)) {
        std::cout << "Неправильный формат дроби\n";
    }
}

Fraction::Fraction(const Fraction& other) {
    integer = other.integer;
    numerator = other.numerator;
    denominator = other.denominator;
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        integer     = other.integer;
        numerator   = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

bool Fraction::parse(const char* str) {
        if (!str || *str == '\0') return false;

        while (*str == ' ') str++;

        int sign = 1;
        if      (*str == '-') { sign = -1; str++; }
        else if (*str == '+') { str++; }

        if (*str < '0' || *str > '9') return false;

        int firstNum = 0;
        while (*str >= '0' && *str <= '9')
            firstNum = firstNum * 10 + (*str++ - '0');
        while (*str == ' ') str++;

        int whole = 0, num = 0, den = 1;

        if (*str == '/') {

            str++;
            if (*str < '0' || *str > '9') return false;
            den = 0;
            while (*str >= '0' && *str <= '9')
                den = den * 10 + (*str++ - '0');
            if (den == 0) return false;
            num = firstNum;
        } else if (*str >= '0' && *str <= '9') {

            whole = firstNum;
            num = 0;
            while (*str >= '0' && *str <= '9')
                num = num * 10 + (*str++ - '0');
            while (*str == ' ') str++;
            if (*str != '/') return false;
            str++;
            if (*str < '0' || *str > '9') return false;
            den = 0;
            while (*str >= '0' && *str <= '9')
                den = den * 10 + (*str++ - '0');
            if (den == 0) return false;
        } else {

            whole = firstNum;

            while (*str == ' ') str++;
            if (*str != '\0') return false;

            integer     = sign * whole;
            numerator   = 0;
            denominator = 1;
            return true;
        }

        int integ = whole * sign;

        normalize(integ, num, den);

        integer = integ;
        numerator = num;
        denominator = den;

        return true;
    }

    std::istream& operator>>(std::istream& in, Fraction& obj) {
        std::cin.clear();
        char* buf = readLine();
        if (!obj.parse(buf)) {
            in.setstate(std::ios::failbit);
            std::cout << "Неправильный формат дроби\n";
        }
        delete[] buf;
        return in;
}
    std::ostream& operator<<(std::ostream& out, const Fraction& obj) {
        if(obj.numerator == 0) {
            out << obj.integer << '\n';
        }
        else {
            out << obj.integer << ' ' << obj.numerator << '/' << obj.denominator << '\n';
        }
        return out;
    }

    int Fraction::get_integer() const {
        return integer;
    }
    int Fraction::get_numerator() const {
        return numerator;
    }
    int Fraction::get_denominator() const {
        return denominator;
    }

    Fraction operator+(const Fraction& a, const Fraction& b) {

    int num1 = a.integer * a.denominator + (a.integer < 0 ? -a.numerator : a.numerator);
    int num2 = b.integer * b.denominator + (b.integer < 0 ? -b.numerator : b.numerator);


    int den1 = a.denominator;
    int den2 = b.denominator;
    int commonDen = den1 / gcd(den1, den2) * den2;

    int totalNum = num1 * (commonDen / den1) + num2 * (commonDen / den2);


    int g = gcd(abs(totalNum), commonDen);
    totalNum   /= g;
    commonDen  /= g;


    Fraction result;
    result.integer     = totalNum / commonDen;
    result.numerator   = abs(totalNum % commonDen);
    result.denominator = commonDen;

    return result;
}

Fraction operator+(const Fraction& a, int b) {
    Fraction temp;
    temp.integer     = b;
    temp.numerator   = 0;
    temp.denominator = 1;
    return a + temp;
}

Fraction operator+(int a, const Fraction& b) {
    return b + a;
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator+=(int other) {
    *this = *this + other;
    return *this;
}

Fraction operator+(const Fraction& a, double b) {
    int scale = 1;
    for (int i = 0; i < kNumberDecimalPlaces; i++)
    scale *= 10;
    int decimals = (int)(fabs(b) * scale) % scale;
    int bInt = static_cast<int>(b);
    int bNum = decimals;
    int bDen = scale;
    normalize(bInt, bNum, bDen);
    Fraction transformed;
    transformed.integer = bInt;
    transformed.numerator = bNum;
    transformed.denominator = bDen;
    return a + transformed;
}

Fraction operator+(double a, const Fraction& b) {
    return b + a;
}
