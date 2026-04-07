#include "Classes.hpp"
#include <cstring>

Area** Area::container = nullptr;
int Area::size = 0;
int Area::capacity = 0;

Area::Area() {
    std::cout << "Area()" << std::endl;
    AreaName = new char[1]{'\0'};
}

Area::Area(const char* name) {
    std::cout << "Area(const char*)" << std::endl;
    AreaName = new char[strlen(name) + 1];
    strncpy(AreaName, name, strlen(name) + 1);
}

Area::Area(const Area& obj) {
    std::cout << "Area(const Area&)" << std::endl;
    AreaName = new char[strlen(obj.AreaName) + 1];
    strncpy(AreaName, obj.AreaName, strlen(obj.AreaName) + 1);
}

Area& Area::operator=(const Area& obj) {
    if(this != &obj) {
        delete[] AreaName;
        AreaName = new char[strlen(obj.AreaName) + 1];
        strncpy(AreaName, obj.AreaName, strlen(obj.AreaName) + 1);
    }
    return *this;
}

int Area::get_size() {
    return size;
}

Area::~Area() {
    std::cout << "~Area()" << std::endl;
    delete[] AreaName;
}

void Area::resize() {
    int NewCap = (capacity == 0) ? 1 : capacity * 2;
    Area **NewContainer = new Area*[NewCap];
    for (int i{}; i < size; i++) {
        NewContainer[i] = container[i];
    }
    delete[] container;
    container = NewContainer;
    capacity = NewCap;
}

void Area::AddToContainer(Area* obj) {
    if(size == capacity) {
        resize();
    }
    container[size] = obj;
    size++;
}

void Area::print() {
    for (int i = 0; i < size; ++i) {
        std::cout << "--- [" << i << "] ---\n";
        container[i]->show();
        std::cout << "\n";
    }
}

void Area::remove(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Объекта с таким индексом не существует\n";
        return;
    }
    delete container[index];
    for (int i = index; i < size - 1; ++i) {
        container[i] = container[i + 1];
    }
    container[--size] = nullptr;
}

void Area::clear() {
    for (int i = 0; i < size; ++i) {
        delete container[i];
    }
    delete[] container;
    container = nullptr;
    size      = 0;
    capacity  = 0;
}

void Area::printByIndex(int item) {
    if(item < 0 || item >= size) {
        std::cout << "Объекта с таким индексом не существует\n";
        return;
    }
    container[item]->show();
}

Town::Town() : Area() {
    std::cout << "Town()" << std::endl;
    TownName = new char[1]{'\0'};
}

Town::Town(char* ArName, char* TwnName) : Area(ArName) {
    std::cout << "Town(char*, char*)" << std::endl;
    TownName = new char[strlen(TwnName) + 1];
    strncpy(TownName, TwnName, strlen(TwnName) + 1);
}

Town::Town(const Town& obj) : Area(obj) {
    std::cout << "Town(const Town&)" << std::endl;
    TownName = new char[strlen(obj.TownName) + 1];
    strncpy(TownName, obj.TownName, strlen(obj.TownName) + 1);
}

Town& Town::operator=(const Town& obj) {
    if(this != &obj) {
        Area::operator=(obj);
        delete[] TownName;
        TownName = new char[strlen(obj.TownName) + 1];
        strncpy(TownName, obj.TownName, strlen(obj.TownName) + 1);
    }
    return *this;
}

void Town::show() {
    std::cout << "Название области: " << AreaName;
    std::cout << "\nНазвание города: " << TownName;
}

void Town::input(std::istream& in) {
    char buf[256];

    std::cout << "Введите название области: ";
    in >> buf;
    delete[] AreaName;
    AreaName = new char[strlen(buf) + 1];
    strncpy(AreaName, buf, strlen(buf) + 1);

    std::cout << "\nВведите название города: ";
    in >> buf;
    delete[] TownName;
    TownName = new char[strlen(buf) + 1];
    strncpy(TownName, buf, strlen(buf) + 1);
}

Town::~Town() {
    std::cout << "~Town()" << std::endl;
    delete[] TownName;
}

Megapolis::Megapolis() : Town() {
    std::cout << "Megapolis()" << std::endl;
    IsMegapolis = false;
    Population = 0;
}

Megapolis::Megapolis(char* ArName, char* TwnName, bool IsMeg, int Popul) : Town(ArName, TwnName) {
    std::cout << "Megapolis(char*, char*, bool, int)" << std::endl;
    IsMegapolis = IsMeg;
    Population = Popul;
}

Megapolis::Megapolis(const Megapolis& obj) : Town(obj) {
    std::cout << "Megapolis(const Megapolis&)" << std::endl;
    IsMegapolis = obj.IsMegapolis;
    Population = obj.Population;
}

Megapolis& Megapolis::operator=(const Megapolis& obj) {
    if(this != &obj) {
        Town::operator=(obj);
        IsMegapolis = obj.IsMegapolis;
        Population = obj.Population;
    }
    return *this;
}

void Megapolis::show() {
    Town::show();
    (IsMegapolis == true) ? (std::cout << "\nМегаполис\n") : (std::cout << "\nНе мегаполис\n");
    std::cout << "Численность населения: " << Population;
}

void Megapolis::input(std::istream& in) {
    Town::input(in);

    std::cout << "Мегаполис? (1/0): ";
    while(!(in >> IsMegapolis)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введены неверные данные, попробуйте еще раз\n";
    }

    std::cout << "Население: ";
    while(!(in >> Population)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введены неверные данные, попробуйте еще раз\n";
    }
}

Megapolis::~Megapolis() {
    std::cout << "~Megapolis()" << std::endl;
}

Place::Place() : Megapolis() {
    std::cout << "Place()" << std::endl;
    PlaceName = new char[1]{'\0'};
}

Place::Place(char* ArName, char* TwnName, bool IsMeg, int Popul, char* PlName)
    : Megapolis(ArName, TwnName, IsMeg, Popul) {
    std::cout << "Place(char*, char*, bool, int, char*)" << std::endl;
    PlaceName = new char[strlen(PlName) + 1];
    strncpy(PlaceName, PlName, strlen(PlName) + 1);
}

Place::Place(const Place& obj) : Megapolis(obj) {
    std::cout << "Place(const Place&)" << std::endl;
    PlaceName = new char[strlen(obj.PlaceName) + 1];
    strncpy(PlaceName, obj.PlaceName, strlen(obj.PlaceName) + 1);
}

Place& Place::operator=(const Place& obj) {
    if(this != &obj) {
        Megapolis::operator=(obj);
        delete[] PlaceName;
        PlaceName = new char[strlen(obj.PlaceName) + 1];
        strncpy(PlaceName, obj.PlaceName, strlen(obj.PlaceName) + 1);
    }
    return *this;
}

void Place::show() {
    Megapolis::show();
    std::cout << "\nМесто: " << PlaceName;
}

void Place::input(std::istream& in) {
    Megapolis::input(in);

    char buf[256];
    std::cout << "Введите название места: ";
    in >> buf;
    delete[] PlaceName;
    PlaceName = new char[strlen(buf) + 1];
    strncpy(PlaceName, buf, strlen(buf) + 1);
}

Place::~Place() {
    std::cout << "~Place()" << std::endl;
    delete[] PlaceName;
}
