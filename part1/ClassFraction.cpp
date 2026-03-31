#include "AuxiliaryFunctions.hpp"
#include "ClassFraction.hpp"

namespace {
    const int kNumberDecimalPlaces = 4;
}

Fraction::Fraction() {
    numerator   = 0;
    denominator = 1;
}

Fraction::Fraction(const char* str) {
    numerator   = 0;
    denominator = 1;
    if (!this->parse(str)) {
        std::cout << "Неправильный формат дроби\n";
    }
}

Fraction::Fraction(const Fraction& other) {
    numerator   = other.numerator;
    denominator = other.denominator;
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
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
        while (*str == ' ') str++;
        if (*str != '\0') return false;
        numerator   = sign * firstNum;
        denominator = 1;
        return true;
    }

    int totalNum = (whole * den + num) * sign;
    int g = gcd(abs(totalNum), den);
    numerator   = totalNum / g;
    denominator = den / g;
    return true;
}

std::istream& operator>>(std::istream& in, Fraction& obj) {
    char* buf = readLine();
    if (!obj.parse(buf)) {
        in.setstate(std::ios::failbit);
        std::cout << "Неправильный формат дроби\n";
    }
    delete[] buf;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Fraction& obj) {
    int integer   = obj.numerator / obj.denominator;
    int remainder = abs(obj.numerator % obj.denominator);
    if (remainder == 0)
        out << integer << '\n';
    else
        out << integer << ' ' << remainder << '/' << obj.denominator << '\n';
    return out;
}

Fraction Fraction::operator+(const Fraction& b) const {
    int commonDen = denominator / gcd(denominator, b.denominator) * b.denominator;
    int totalNum  = numerator * (commonDen / denominator)
                  + b.numerator * (commonDen / b.denominator);

    int g = gcd(abs(totalNum), commonDen);

    Fraction result;
    result.numerator   = totalNum / g;
    result.denominator = commonDen / g;
    return result;
}

Fraction Fraction::operator+(int b) const {
    Fraction temp;
    temp.numerator   = b;
    temp.denominator = 1;
    return *this + temp;
}

Fraction operator+(int a, const Fraction& b) {
    return b + a;
}

Fraction Fraction::operator+(double b) const {
    int scale = 1;
    for (int i = 0; i < kNumberDecimalPlaces; i++)
        scale *= 10;

    int totalNum = static_cast<int>(round(b * scale));
    int g = gcd(abs(totalNum), scale);

    Fraction temp;
    temp.numerator   = totalNum / g;
    temp.denominator = scale / g;
    return *this + temp;
}

Fraction operator+(double a, const Fraction& b) {
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
