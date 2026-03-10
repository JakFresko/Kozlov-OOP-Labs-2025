#include "StartingApp.hpp"

enum menu {
    kLoadFromFile = 1,
    kSaveToFile = 2,
    kAddObj = 3,
    kRemoveObj = 4,
    kSortArr = 5,
    kSearchObj = 6,
    kEditObj = 7,
    kPrintArr = 8,
    kPrintByIndex = 9,
    kExit = 10
};

namespace {
const int kBuffSize = 256;
}

void StartingApp() {
    TicketArr arr;
    int item{};

    while (true) {
        std::cout << "1) Загрузка из файла\n"
                  << "2) Сохранение в файл\n"
                  << "3) Добавление объекта\n"
                  << "4) Удаление объекта\n"
                  << "5) Сортировка массива\n"
                  << "6) Поиск объекта\n"
                  << "7) Редактирование объекта\n"
                  << "8) Вывод массива на экран\n"
                  << "9) Печать элемента по индексу\n"
                  << "10) Выход\n"
                  << "Выберите пункт меню: ";
        std::cin >> item;
        std::cout << '\n';

        switch (item) {
            case kLoadFromFile: {
                char filename[kBuffSize];
                std::cout << "Имя файла: ";
                std::cin >> filename;
                if (arr.load(filename)) {
                    std::cout << "Загружено " << arr.get_size() << " объектов.\n";
                } else {
                    std::cout << "Не удалось открыть файл.\n";
                }
                break;
            }
            case kSaveToFile: {
                char filename[kBuffSize];
                std::cout << "Имя файла: ";
                std::cin >> filename;
                if (arr.save(filename)) {
                    std::cout << "Сохранено.\n";
                } else {
                    std::cout << "Не удалось сохранить файл.\n";
                }
                break;
            }
            case kAddObj: {
                FlightTicket t;
                std::cin >> t;
                arr.add(t);
                std::cout << "Объект добавлен.\n";
                break;
            }
            case kRemoveObj: {
                int cost{};
                std::cout << "Введите цену билета для удаления: ";
                std::cin >> cost;
                if (arr.remove_by_cost(cost)) {
                    std::cout << "Объект удалён.\n";
                } else {
                    std::cout << "Объект не найден.\n";
                }
                break;
            }
            case kSortArr: {
                int sortItem{};
                std::cout << "1) По стоимости\n2) По аэропорту вылета\nВыбор: ";
                std::cin >> sortItem;
                if (sortItem == 1) {
                    arr.sort_by_cost();
                } else {
                    arr.sort_by_dep();
                }
                std::cout << "Отсортировано.\n";
                break;
            }
            case kSearchObj: {
                char arr_name[kBuffSize];
                std::cout << "Введите аэропорт назначения: ";
                std::cin >> arr_name;
                int idx = arr.find(arr_name);
                if (idx != -1) {
                    std::cout << "Найден [" << idx << "]:\n" << arr[idx] << '\n';
                } else {
                    std::cout << "Не найдено.\n";
                }
                break;
            }
            case kEditObj: {
                int index{};
                std::cout << "Введите индекс объекта для редактирования: ";
                std::cin >> index;
                if (index < 0 || index >= arr.get_size()) {
                    std::cout << "Неверный индекс.\n";
                    break;
                }
                std::cout << "Текущие данные:\n" << arr[index] << '\n';
                std::cout << "Введите новые данные:\n";
                std::cin >> arr[index];
                std::cout << "Объект обновлён.\n";
                break;
            }
            case kPrintArr:
                arr.print_all();
                break;
            case kPrintByIndex: {
                int index{};
                std::cout << "Введите индекс объекта для печати: ";
                std::cin >> index;
                std::cout << '\n';
                if (index < 0 || index >= arr.get_size()) {
                    std::cout << "Неверный индекс.\n";
                    break;
                }
                std::cout << arr[index];
                break;
            }
            case kExit:
                return;
            default:
                std::cout << "Некорректный ввод.\n";
                break;
        }
        std::cout << '\n';
    }
}
