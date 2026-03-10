#include "WorkingWithClass.hpp"
#include <cstring>

namespace {
const int kBuffSize = 256;
}

int FlightTicket::quantity = 0;

std::ostream& operator<<(std::ostream& out, const FlightTicket& obj) {
    out << "Аэропорт вылета: " << obj.departure << '\n' << "Аэропорт прибытия: " << obj.arrival << '\n' << "Стоимость билета: " << obj.cost << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, FlightTicket& obj) {
    char buf[kBuffSize];

    std::cout << "Аэропорт вылета: ";
    in >> buf;
    obj.departure = new char[strlen(buf) + 1];
    strncpy((char*)obj.departure, buf, strlen(buf) + 1);

    std::cout << "Аэропорт прибытия: ";
    in >> buf;
    obj.arrival = new char[strlen(buf) + 1];
    strncpy((char*)obj.arrival, buf, strlen(buf) + 1);

    std::cout << "Стоимость билета: ";
    in >> obj.cost;

    return in;
}
