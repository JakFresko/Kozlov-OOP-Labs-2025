#include "StartingApp.hpp"
#include "ClassFraction.hpp"

enum menu {
    kSimplifying = 1,
    kConstructorsCheck = 2,
    kFrPlusFr = 3,
    kFrPlusInt = 4,
    kFrPlusDouble = 5,
    kExit = 6
};

void StartingApp() {
    int item{};
    while(item != kExit) {
        int item{};
        std::cout << "1) Упрощение дроби\n2) Проверка конструкторов\n3) Арифметические операции (дробь + дробь)\n4) Арифметика с целыми числами\n5) Арифметика с double\n6) Выход\nВыберите пункт меню: ";
        std::cin >> item;
        std::cin.ignore();
        std::cout << '\n';
        switch (item)
        {
        case kSimplifying: {
            Fraction fr;
            std::cout << "Введите дробь: ";
            std::cin >> fr;
            std::cout << "\nРезультат: " << fr << '\n';
            break;
        }
        case kConstructorsCheck: {
            Fraction fr1;
            Fraction fr2("2 3/4");
            Fraction fr3(fr2);
            std::cout << fr1 << '\n' << fr2 << '\n' << fr3 << '\n';
            break;
        }
        case kFrPlusFr: {
            Fraction a;
            Fraction b;
            std::cout << "Введите первую дробь: ";
            if(!(std::cin >> a)) {
                std::cin.clear();
                break;
            }
            std::cout << "\nВведите вторую дробь: ";
            if(!(std::cin >> b)) {
                std::cin.clear();
                break;
            }
            std::cout << "\nСумма равна: " << a + b << '\n';
            break;
        }
        case kFrPlusInt: {
            Fraction a;
            int b;
            std::cout << "Введите дробь: ";
            if(!(std::cin >> a)) {
                std::cin.clear();
                break;
            }
            std::cout << "\nВведите целое число: ";
            if(!(std::cin >> b)) {
                std::cout << "\nОшибка ввода\n";
                std::cin.clear();
                break;
            }
            std::cout << "\nСумма равна: " << a + b << '\n';
            break;
        }
        case kFrPlusDouble: {
            Fraction a;
            double b;
            std::cout << "Введите дробь: ";
            if(!(std::cin >> a)) {
                std::cin.clear();
                break;
            }
            std::cout << "\nВведите вещественное число: ";
            if(!(std::cin >> b)) {
                std::cin.clear();
                std::cout << "\nОшибка ввода\n";
                break;
            }
            std::cout << "\nСумма равна: " << a + b << '\n';
            break;
        }
        case kExit: {
            return;
            break;
        }
        default:
            std::cout << "Неверный ввод\n";
            break;
        }
    }
}
