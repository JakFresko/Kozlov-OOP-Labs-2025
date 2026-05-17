#include <iostream>
#include "Term.hpp"
#include "Polynomial.hpp"

int main() {

    std::cout << "Term\n";

    Term t1(3, 2);
    Term t2(1, 0);
    Term t3(-1, 1);
    Term t4(1, 3);

    std::cout << "t1 = " << t1 << "\n";
    std::cout << "t2 = " << t2 << "\n";
    std::cout << "t3 = " << t3 << "\n";
    std::cout << "t4 = " << t4 << "\n";

    Term t5 = Term(3, 2) + Term(-1, 2);
    std::cout << "3x^2 + (-1)x^2 = " << t5 << "\n";

    std::cout << "Введите терм (например: -3x^2): ";
    Term tin;
    std::cin >> tin;
    std::cout << "Вы ввели: " << tin << "\n";
    std::cout << "\nPolynomial\n";

    Polynomial p0;
    Polynomial p1(5.0);
    Polynomial p2(Term(3, 2));
    std::cout << "p0 = " << p0 << "\n";
    std::cout << "p1 = " << p1 << "\n";
    std::cout << "p2 = " << p2 << "\n";

    p2.add(Term(-1, 1));
    p2.add(Term(5, 0));
    p2.add(Term(2, 2));
    std::cout << "p2 после add: " << p2 << "\n";

    p2.remove(0);
    std::cout << "p2 после remove(0): " << p2 << "\n";
    std::cout << "p2(2) = " << p2.eval(2) << "\n";
    p2.set_order(true);
    std::cout << "p2 по возрастанию: " << p2 << "\n";
    p2.set_order(false);
    std::cout << "p2 по убыванию:    " << p2 << "\n";

    Polynomial A(Term(3, 2));
    A.add(Term(1, 1));
    A.add(Term(-2, 0));
    std::cout << "\nA = " << A << "\n";

    Polynomial B(Term(1, 1));
    B.add(Term(4, 0));
    std::cout << "B = " << B << "\n";

    std::cout << "A + B = " << (A + B) << "\n";
    std::cout << "A - B = " << (A - B) << "\n";
    std::cout << "A * B = " << (A * B) << "\n";

    Polynomial C = A;
    std::cout << "\n(A == C): " << (A == C) << "\n";
    std::cout << "(A == B): " << (A == B) << "\n";

    std::cout << "\nВведите полином (Enter): ";
    Polynomial pin;
    std::cin >> pin;
    std::cout << "Полином: " << pin << "\n";
    std::cout << "Значение при x=1: " << pin.eval(1) << "\n";

    Term a;
    std::cin >> a;
    Term b;
    std::cin >> b;
    Polynomial c;
    c.add(a);
    c.add(b);
    std::cout << c << '\n';
    c = c + pin;
    std::cout << c << '\n';
    c *= pin;
    std::cout << c << '\n';
    c.remove(7);
    std::cout << c << '\n';

    return 0;
}
