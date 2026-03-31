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
        // Формат: [sign] числитель/знаменатель
        str++;
        if (*str < '0' || *str > '9') return false;
        den = 0;
        while (*str >= '0' && *str <= '9')
            den = den * 10 + (*str++ - '0');
        if (den == 0) return false;
        num = firstNum;
    } else if (*str >= '0' && *str <= '9') {
        // Формат: [sign] целое числитель/знаменатель
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
        // Формат: [sign] целое
        while (*str == ' ') str++;
        if (*str != '\0') return false;

        numerator   = sign * firstNum;
        denominator = 1;
        return true;
    }

    // Переводим в неправильную дробь и сокращаем
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
    int integer = obj.numerator / obj.denominator;
    int remainder = abs(obj.numerator % obj.denominator);

    if (remainder == 0) {
        out << integer << '\n';
    } else {
        out << integer << ' ' << remainder << '/' << obj.denominator << '\n';
    }
    return out;
}

Fraction::Fraction(int a) {
    numerator = a;
    denominator = 1;
}

Fraction::Fraction(double a) {
    int scale = 1;
    for (int i = 0; i < kNumberDecimalPlaces; i++) {
        scale *= 10;
    }

    int totalNum = static_cast<int>(round(a * scale));
    int g = gcd(abs(totalNum), scale);

    numerator   = totalNum / g;
    denominator = scale / g;
}

Fraction& Fraction::operator+=(const Fraction& other) {
    int commonDen = denominator / gcd(denominator, other.denominator) * other.denominator;
    int totalNum  = numerator * (commonDen / denominator)
                  + other.numerator * (commonDen / other.denominator);

    int g = gcd(abs(totalNum), commonDen);

    numerator   = totalNum / g;
    denominator = commonDen / g;
    return *this;
}

Fraction operator+(Fraction a, const Fraction& b) {
    a += b;
    return a;
}
