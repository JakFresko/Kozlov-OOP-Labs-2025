#include "StartingApp.hpp"
#include <limits>

enum menu {
    AddObj        = 1,
    PrintByIndex  = 2,
    PrintArr      = 3,
    RemoveByIndex = 4,
    Clear         = 5,
    Exit          = 6
};

// ─── вспомогательные функции ─────────────────────────────────────────────────

static void printSeparator() {
    std::cout << "  ════════════════════════════════════\n";
}

static void printSuccess(const std::string& msg) {
    std::cout << "\n  ✔ " << msg << "\n";
}

static void printError(const std::string& msg) {
    std::cout << "\n  ✘ Ошибка: " << msg << "\n";
}

// безопасный ввод целого числа
static int safeInputInt(const std::string& prompt) {
    int value{};
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printError("Введите целое число.");
    }
    return value;
}

// ─── меню ────────────────────────────────────────────────────────────────────

static void printMenu() {
    std::cout << "\n";
    printSeparator();
    std::cout << "  │  1)  Добавить объект\n";
    std::cout << "  │  2)  Вывод по индексу\n";
    std::cout << "  │  3)  Вывод всего списка\n";
    std::cout << "  │  4)  Удалить по индексу\n";
    std::cout << "  │  5)  Очистить список\n";
    std::cout << "  │  6)  Выход\n";
    printSeparator();
    std::cout << "  Объектов в списке: " << Area::get_size() << "\n";
    std::cout << "  Выберите пункт: ";
}

// ─── выбор класса ────────────────────────────────────────────────────────────

Area* SwitchClass() {
    std::cout << "\n";
    printSeparator();
    std::cout << "  │  1)  Город\n";
    std::cout << "  │  2)  Мегаполис\n";
    std::cout << "  │  3)  Место\n";
    printSeparator();
    std::cout << "  Выберите тип объекта: ";

    int item = safeInputInt("");
    std::cout << "\n";

    switch (item) {
        case 1: return new Town();
        case 2: return new Megapolis();
        case 3: return new Place();
        default:
            printError("Такого типа не существует.");
            return nullptr;
    }
}

// ─── основное приложение ─────────────────────────────────────────────────────

void StartingApp() {
    std::cout << "\n";
    printSeparator();
    std::cout << "  │       УПРАВЛЕНИЕ ОБЪЕКТАМИ        │\n";
    printSeparator();

    int item{};
    while (item != Exit) {
        printMenu();
        item = safeInputInt("");

        switch (item) {
            case AddObj: {
                Area* obj = SwitchClass();
                if (obj == nullptr) break;

                std::cin >> *obj;  // вызов input() через operator>>

                Area::AddToContainer(obj);
                printSuccess("Объект успешно добавлен. "
                             "Индекс: [" + std::to_string(Area::get_size() - 1) + "]");
                break;
            }

            case PrintByIndex: {
                if (Area::get_size() == 0) {
                    printError("Список пуст.");
                    break;
                }
                int index = safeInputInt("  Введите индекс (0–"
                    + std::to_string(Area::get_size() - 1) + "): ");

                if (index < 0 || index >= Area::get_size()) {
                    printError("Индекс [" + std::to_string(index) + "] вне диапазона.");
                    break;
                }
                std::cout << "\n";
                printSeparator();
                Area::printByIndex(index);
                std::cout << "\n";
                printSeparator();
                break;
            }

            case PrintArr: {
                if (Area::get_size() == 0) {
                    printError("Список пуст.");
                    break;
                }
                std::cout << "\n";
                printSeparator();
                Area::print();
                printSeparator();
                break;
            }

            case RemoveByIndex: {
                if (Area::get_size() == 0) {
                    printError("Список пуст, нечего удалять.");
                    break;
                }
                int index = safeInputInt("  Введите индекс (0–"
                    + std::to_string(Area::get_size() - 1) + "): ");

                if (index < 0 || index >= Area::get_size()) {
                    printError("Индекс [" + std::to_string(index) + "] вне диапазона.");
                    break;
                }
                Area::remove(index);
                printSuccess("Объект [" + std::to_string(index) + "] удалён.");
                break;
            }

            case Clear: {
                if (Area::get_size() == 0) {
                    printError("Список уже пуст.");
                    break;
                }
                int count = Area::get_size();
                Area::clear();
                printSuccess("Список очищен. Удалено объектов: "
                             + std::to_string(count));
                break;
            }

            case Exit: {
                Area::clear();
                std::cout << "\n";
                printSeparator();
                std::cout << "  │           До свидания!             │\n";
                printSeparator();
                std::cout << "\n";
                return;
            }

            default:
                printError("Неверный пункт меню. Введите число от 1 до 6.");
                break;
        }
    }
}
