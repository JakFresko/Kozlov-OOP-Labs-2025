#include "StartingApp.hpp"

enum menu {
    kCreateObj = 1,
    kPrintObj = 2,
    kDeleteObj = 3,
    kPrintArr = 4,
    kExit = 5
};

namespace {
const int kArrLen = 100;
}

int FlightTicket::quantity = 0;

void StartingApp() {
    FlightTicket arr[kArrLen]{};
    int item{};
    int counter{};
    while (true) {
        std::cout << "1) Создание объекта\n2) Вывод объекта на экран\n3) Удаление объекта\n4) Вывод всех объектов\n5) Выход\nВыберите пункт меню: ";
        std::cin >> item;
        std::cout << '\n';
        switch (item) {
            case kCreateObj: {
                if (counter > kArrLen - 1) {
                    std::cout << "Массив объектов переполнен\n";
                    break;
                }
                std::cin >> arr[counter];  // читаем сразу в элемент массива, без лишних копий
                counter++;
                break;
            }
            case kPrintObj: {
                int index{};
                std::cout << "Введите индекс элемента который хотите вывести: ";
                std::cin >> index;
                std::cout << '\n';
                if (index < 0 || index >= counter) {
                    std::cout << "Элемента с таким индексом не существует\n";
                    break;
                }
                std::cout << arr[index];
                break;
            }
            case kDeleteObj: {
                int index{};
                std::cout << "Введите индекс элемента который хотите удалить: ";
                std::cin >> index;
                std::cout << '\n';
                if (index < 0 || index >= counter) {
                    std::cout << "Элемента с таким индексом не существует\n";
                    break;
                }
                for (int i = index; i < counter - 1; i++) {
                    arr[i] = arr[i + 1];
                }
                counter--;
                break;
            }
            case kPrintArr:
                if (counter == 0) {
                    std::cout << "Нет объектов для вывода\n";
                    break;
                }
                for (int i = 0; i < counter; i++) {
                    std::cout << arr[i] << '\n';
                }
                break;
            case kExit:
                return;
                break;
            default:
                std::cout << "Некорректный ввод, попробуйте еще раз\n";
                break;
        }
    }
}
