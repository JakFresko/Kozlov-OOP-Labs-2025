#include <iostream>
#include "Term.hpp"
#include "Polynomial.hpp"

int main() {

    std::cout << "=== Term ===\n";

    Term t1(3, 2);
    Term t2(1, 0);
    Term t3(-1, 1);
    Term t4(1, 3);

    std::cout << "t1 = " << t1 << "\n";   // 3x^2
    std::cout << "t2 = " << t2 << "\n";   // 3
    std::cout << "t3 = " << t3 << "\n";   // -x
    std::cout << "t4 = " << t4 << "\n";   // x^3

    Term t5 = Term(3, 2) + Term(-1, 2);
    std::cout << "3x^2 + (-1)x^2 = " << t5 << "\n";  // 2x^2

    // ввод терма
    std::cout << "Введите терм (например: -3x^2): ";
    Term tin;
    std::cin >> tin;
    std::cout << "Вы ввели: " << tin << "\n";

    // ============================================================
    //  Демонстрация класса Polynomial
    // ============================================================
    std::cout << "\n=== Polynomial ===\n";

    // Конструкторы
    Polynomial p0;              // 0
    Polynomial p1(5.0);         // 5
    Polynomial p2(Term(3, 2));  // 3x^2
    std::cout << "p0 = " << p0 << "\n";
    std::cout << "p1 = " << p1 << "\n";
    std::cout << "p2 = " << p2 << "\n";

    // Добавление термов
    p2.add(Term(-1, 1));   // 3x^2 - x
    p2.add(Term(5, 0));    // 3x^2 - x + 5
    p2.add(Term(2, 2));    // приведение подобных: 5x^2 - x + 5
    std::cout << "p2 после add: " << p2 << "\n";

    // Удаление члена
    p2.remove(0);
    std::cout << "p2 после remove(0): " << p2 << "\n";

    // Вычисление значения
    std::cout << "p2(2) = " << p2.eval(2) << "\n";  // 5*4 - 2 = 18

    // Сортировка
    p2.set_order(true);
    std::cout << "p2 по возрастанию: " << p2 << "\n";
    p2.set_order(false);
    std::cout << "p2 по убыванию:    " << p2 << "\n";

    // Арифметика
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

    // Сравнение
    Polynomial C = A;
    std::cout << "\n(A == C): " << (A == C) << "\n";
    std::cout << "(A == B): " << (A == B) << "\n";

    // Ввод из строки
    std::cout << "\nВведите полином (Enter): ";
    Polynomial pin;
    std::cin.ignore();
    std::cin >> pin;
    std::cout << "Полином: " << pin << "\n";
    std::cout << "Значение при x=1: " << pin.eval(1) << "\n";

    return 0;
}
