#include "Term.hpp"
#include <stdexcept>
#include <sstream>
#include <string>
#include <cctype>

Term::Term() : coef(0), power(0) {}

Term::Term(double c) : coef(c), power(0) {}

Term::Term(double c, int p) : coef(c), power(p) {}

Term Term::operator+(const Term& other) const {
    if (power != other.power)
        throw std::invalid_argument("Term::operator+: degrees must match");
    return Term(coef + other.coef, power);
}

// Разбирает строку вида: [sign] [coef] [x [^ power]]
// Примеры: "3x^2", "-x^3", "5", "-7", "x", "-3x"
std::istream& operator>>(std::istream& is, Term& t) {
    std::string s;
    is >> s;
    if (s.empty()) { is.setstate(std::ios::failbit); return is; }

    double coef = 1.0;
    int    power = 0;
    size_t i = 0;

    // знак
    int sign = 1;
    if (s[i] == '-') { sign = -1; ++i; }
    else if (s[i] == '+') { ++i; }

    // числовой коэффициент (может отсутствовать перед x)
    bool has_coef = false;
    std::string num;
    while (i < s.size() && (std::isdigit(s[i]) || s[i] == '.')) {
        num += s[i++];
        has_coef = true;
    }
    coef = has_coef ? std::stod(num) : 1.0;
    coef *= sign;

    // переменная x
    if (i < s.size() && s[i] == 'x') {
        ++i;
        power = 1;
        // степень
        if (i < s.size() && s[i] == '^') {
            ++i;
            std::string pw;
            int psign = 1;
            if (i < s.size() && s[i] == '-') { psign = -1; ++i; }
            while (i < s.size() && std::isdigit(s[i])) pw += s[i++];
            power = psign * std::stoi(pw);
        }
    }

    t.coef  = coef;
    t.power = power;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Term& t) {
    if (t.power == 0) {
        os << t.coef;
        return os;
    }

    // коэффициент
    if (t.coef == -1.0)      os << '-';
    else if (t.coef != 1.0)  os << t.coef;

    // переменная
    if (t.power == 1) os << 'x';
    else              os << "x^" << t.power;

    return os;
}
