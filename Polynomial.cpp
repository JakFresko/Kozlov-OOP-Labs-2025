#include "Polynomial.hpp"
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <string>
#include <cctype>

void Polynomial::resize(int new_cap) {
    if (new_cap < 1) new_cap = 1;
    Term* tmp = new Term[new_cap];
    for (int i = 0; i < size; ++i) tmp[i] = terms[i];
    delete[] terms;
    terms    = tmp;
    capacity = new_cap;
}


void Polynomial::simplify() {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ) {
            if (terms[i].power == terms[j].power) {
                terms[i].coef += terms[j].coef;

                for (int k = j; k < size - 1; ++k)
                    terms[k] = terms[k + 1];
                --size;
            } else {
                ++j;
            }
        }
    }

    for (int i = 0; i < size; ) {
        if (terms[i].coef == 0.0 && size > 1) {
            for (int k = i; k < size - 1; ++k) terms[k] = terms[k + 1];
            --size;
        } else {
            ++i;
        }
    }
}

void Polynomial::sort() {
    for (int i = 1; i < size; ++i) {
        Term key = terms[i];
        int  j   = i - 1;
        if (order) {
            while (j >= 0 && terms[j].power > key.power) {
                terms[j + 1] = terms[j]; --j;
            }
        } else {
            while (j >= 0 && terms[j].power < key.power) {
                terms[j + 1] = terms[j]; --j;
            }
        }
        terms[j + 1] = key;
    }
}

void Polynomial::add_term(const Term& t) {
    for (int i = 0; i < size; ++i) {
        if (terms[i].power == t.power) {
            terms[i].coef += t.coef;
            simplify();
            sort();
            return;
        }
    }
    if (size >= capacity) resize(capacity * 2);
    terms[size++] = t;
    sort();
}

Polynomial::Polynomial()
    : terms(new Term[4]), size(1), capacity(4), order(false)
{
    terms[0] = Term(0, 0);
}

Polynomial::Polynomial(double coef)
    : terms(new Term[4]), size(1), capacity(4), order(false)
{
    terms[0] = Term(coef, 0);
}

Polynomial::Polynomial(const Term& t)
    : terms(new Term[4]), size(1), capacity(4), order(false)
{
    terms[0] = t;
}

Polynomial::Polynomial(const Polynomial& other)
    : terms(new Term[other.capacity])
    , size(other.size)
    , capacity(other.capacity)
    , order(other.order)
{
    for (int i = 0; i < size; ++i) terms[i] = other.terms[i];
}

Polynomial::~Polynomial() { delete[] terms; }

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this == &other) return *this;
    delete[] terms;
    capacity = other.capacity;
    size     = other.size;
    order    = other.order;
    terms    = new Term[capacity];
    for (int i = 0; i < size; ++i) terms[i] = other.terms[i];
    return *this;
}

void Polynomial::add(const Term& t)    { add_term(t); }

void Polynomial::remove(int power) {
    for (int i = 0; i < size; ) {
        if (terms[i].power == power) {
            for (int k = i; k < size - 1; ++k) terms[k] = terms[k + 1];
            --size;
            if (size == 0) { terms[0] = Term(0, 0); size = 1; }
        } else {
            ++i;
        }
    }
}

void Polynomial::set_order(bool asc) { order = asc; sort(); }

double Polynomial::eval(double x) const {
    double result = 0.0;
    for (int i = 0; i < size; ++i)
        result += terms[i].coef * std::pow(x, terms[i].power);
    return result;
}

Polynomial& Polynomial::operator+=(const Term& t) {
    add_term(t); return *this;
}

Polynomial operator+(Polynomial p, const Term& t) {
    p += t; return p;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    for (int i = 0; i < other.size; ++i) add_term(other.terms[i]);
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
    for (int i = 0; i < other.size; ++i) {
        Term neg = other.terms[i];
        neg.coef = -neg.coef;
        add_term(neg);
    }
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    Polynomial result;
    result.terms[0] = Term(0, 0);
    result.size = 1;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < other.size; ++j)
            result.add_term(Term(terms[i].coef * other.terms[j].coef,
                                 terms[i].power + other.terms[j].power));
    *this = result;
    return *this;
}

Polynomial operator+(Polynomial lhs, const Polynomial& rhs) { lhs += rhs; return lhs; }
Polynomial operator-(Polynomial lhs, const Polynomial& rhs) { lhs -= rhs; return lhs; }
Polynomial operator*(Polynomial lhs, const Polynomial& rhs) { lhs *= rhs; return lhs; }

bool Polynomial::operator==(const Polynomial& other) const {
    if (size != other.size) return false;
    for (int i = 0; i < size; ++i)
        if (terms[i].power != other.terms[i].power ||
            terms[i].coef  != other.terms[i].coef)
            return false;
    return true;
}

std::istream& operator>>(std::istream& is, Polynomial& p) {
    std::string line;
    std::getline(is, line);
    std::string clean;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] != ' ') clean += line[i];
    }
    Polynomial tmp;
    tmp.terms[0] = Term(0, 0);
    tmp.size = 1;

    int start = 0;
    for (int i = 1; i <= (int)clean.size(); ++i) {
        if (i == (int)clean.size() ||
            ((clean[i] == '+' || clean[i] == '-') && i > 0))
        {
            std::string token = clean.substr(start, i - start);
            if (!token.empty()) {
                Term t;
                std::istringstream ss(token);
                ss >> t;
                tmp.add_term(t);
            }
            start = i;
        }
    }

    p = tmp;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    if (p.size == 0) { os << '0'; return os; }

    for (int i = 0; i < p.size; ++i) {
        const Term& t = p.terms[i];
        if (t.get_coef() == 0.0) continue;

        if (i == 0) {
            os << t;
        } else {
            if (t.get_coef() > 0) os << " + " << t;
            else {
                os << " - ";
                Term pos(-(t.get_coef()), t.get_power());
                os << pos;
            }
        }
    }
    return os;
}
