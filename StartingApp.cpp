#include "StartingApp.hpp"

int FlightTicket::quantity = 0;

void StartingApp() {
    FlightTicket arr[100]{};
    int item{};
    int counter{};
    while(true) {
        std::cout << "1) Создание объекта\n2) Вывод объекта на экран\n3) Удаление объекта\n4) Вывод всех объектов\n5) Выход\nВыберите пункт меню: ";
        std::cin >> item;
        std::cout << '\n';
        switch (item)
        {
        case 1: {
            if(counter > 99) {
                std::cout << "Массив объектов переполнен\n";
                break;
            }
            std::cin >> arr[counter];  // читаем сразу в элемент массива, без лишних копий
            counter++;
            break;
        }
        case 2: {
            int index{};
            std::cout << "Введите индекс элемента который хотите вывести: ";
            std::cin >> index;
            std::cout << '\n';
            if(index < 0 || index >= counter) {
                std::cout << "Элемента с таким индексом не существует\n";
                break;
            }
            std::cout << arr[index];
            break;
        }
        case 3: {
            int index{};
            std::cout << "Введите индекс элемента который хотите удалить: ";
            std::cin >> index;
            std::cout << '\n';
            if(index < 0 || index >= counter) {
                std::cout << "Элемента с таким индексом не существует\n";
                break;
            }
            for(int i = index; i < counter - 1; i++) {
                arr[i] = arr[i + 1];
            }
            counter--;
            break;
        }
        case 4:
            if(counter == 0) {
                std::cout << "Нет объектов для вывода\n";
                break;
            }
            for(int i = 0; i < counter; i++) {
                std::cout << arr[i] << '\n';
            }
            break;
        case 5:
            return;
            break;
        default:
            std::cout << "Некорректный ввод, попробуйте еще раз\n";
            break;
        }
    }
}
