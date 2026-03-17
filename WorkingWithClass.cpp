#include "WorkingWithClass.hpp"
#include <cstring>

int FlightTicket::quantity = 0;

FlightTicket::FlightTicket() : departure(new char[1]{'\0'}), arrival(new char[1]{'\0'}), cost(0) {
    quantity++;
    std::cout << "Количество объектов: " << quantity << '\n';
}

FlightTicket::FlightTicket(const char* dep, const char* arr, double cst)
    : departure(new char[strlen(dep) + 1]), arrival(new char[strlen(arr) + 1]), cost(cst) {
    strncpy(departure, dep, strlen(dep) + 1);
    strncpy(arrival, arr, strlen(arr) + 1);
    quantity++;
    std::cout << "Количество объектов: " << quantity << '\n';
}

FlightTicket::FlightTicket(const FlightTicket& ticket)
    : departure(new char[strlen(ticket.departure) + 1]), arrival(new char[strlen(ticket.arrival) + 1]), cost(ticket.cost) {
    strncpy(departure, ticket.departure, strlen(ticket.departure) + 1);
    strncpy(arrival, ticket.arrival, strlen(ticket.arrival) + 1);
    quantity++;
    std::cout << "Количество объектов: " << quantity << '\n';
}

FlightTicket::~FlightTicket() {
    delete[] departure;
    delete[] arrival;
    quantity--;
    std::cout << "Количество объектов: " << quantity << '\n';
}

FlightTicket& FlightTicket::operator=(FlightTicket other) {
    swap(*this, other);
    return *this;
}
const char* FlightTicket::get_dep() const {
    return departure;
}
const char* FlightTicket::get_arr() const {
    return arrival;
}
double FlightTicket::get_cost() const {
    return cost;
}
int FlightTicket::get_quantity() {
    return quantity;
}

void FlightTicket::set_dep(const char* dep) {
    delete[] departure;
    departure = new char[strlen(dep) + 1];
    strncpy(departure, dep, strlen(dep) + 1);
}
void FlightTicket::set_arr(const char* arr) {
    delete[] arrival;
    arrival = new char[strlen(arr) + 1];
    strncpy(arrival, arr, strlen(arr) + 1);
}
void FlightTicket::set_cost(double cst) {
    cost = cst;
}

std::ostream& operator<<(std::ostream& out, const FlightTicket& obj) {
    out << "Аэропорт вылета: " << obj.departure << '\n' << "Аэропорт прибытия: " << obj.arrival << '\n' << "Стоимость билета: " << obj.cost << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, FlightTicket& obj) {
    char buf[kBuffSize];

    std::cout << "Аэропорт вылета: ";
    in >> buf;
    delete[] obj.departure;
    obj.departure = new char[strlen(buf) + 1];
    strncpy((char*)obj.departure, buf, strlen(buf) + 1);

    std::cout << "Аэропорт прибытия: ";
    in >> buf;
    delete[] obj.arrival;
    obj.arrival = new char[strlen(buf) + 1];
    strncpy((char*)obj.arrival, buf, strlen(buf) + 1);

    std::cout << "Стоимость билета: ";
    in >> obj.cost;

    return in;
}

void swap(FlightTicket& a, FlightTicket& b) noexcept {
    char* tmpDep = a.departure;
    char* tmpArr = a.arrival;
    double tmpCost = a.cost;

    a.departure = b.departure;
    a.arrival = b.arrival;
    a.cost = b.cost;

    b.departure = tmpDep;
    b.arrival = tmpArr;
    b.cost = tmpCost;
}

void TicketArr::Resize() {
    int newCap = capacity * 2;
    FlightTicket* NewData = new FlightTicket[newCap];
    for (int i{}; i < capacity; i++) {
        NewData[i] = data[i];
    }
    delete[] data;
    data = NewData;
    capacity = newCap;
}

TicketArr::TicketArr() : size(0), capacity(4), data(new FlightTicket[capacity]) {
}

TicketArr::~TicketArr() {
    delete[] data;
}

int TicketArr::get_size() const {
    return size;
}

void TicketArr::add(FlightTicket& ticket) {
    if (size == capacity) {
        Resize();
    }
    data[size++] = ticket;
}

bool TicketArr::remove_by_cost(int cost) {
    for (int i{}; i < size; i++) {
        if (data[i].get_cost() == cost) {
            for (int j = i; j < size - 1; j++) {
                data[j] = data[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

void TicketArr::sort_by_cost() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j].get_cost() > data[j + 1].get_cost()) {
                FlightTicket tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}

void TicketArr::sort_by_dep() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(data[j].get_dep(), data[j + 1].get_dep()) > 0) {
                FlightTicket tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}

int TicketArr::find(const char* arr) const {
    for (int i = 0; i < size; i++) {
        if (strcmp(data[i].get_arr(), arr) == 0) {
            return i;
        }
    }
    return -1;
}

void TicketArr::print_all() const {
    if (size == 0) {
        std::cout << "Массив пуст.\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        std::cout << "[" << i << "]\n" << data[i] << '\n';
    }
}

bool TicketArr::load(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    delete[] data;
    capacity = 4;
    size = 0;
    data = new FlightTicket[capacity];
    char dep[kBuffSize];
    char arr[kBuffSize];
    double cost{};
    while (file >> dep >> arr >> cost) {
        FlightTicket t(dep, arr, cost);
        add(t);
    }
    file.close();
    return true;
}

bool TicketArr::save(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        file << data[i].get_dep() << ' ' << data[i].get_arr() << ' ' << data[i].get_cost() << '\n';
    }
    file.close();
    return true;
}
