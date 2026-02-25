#include "WorkingWithClass.hpp"
#include <cstring>

std::ostream& operator<<(std::ostream& out, const FlightTicket& obj) {
    out << "Аэропорт вылета: "   << obj.departure << '\n'
        << "Аэропорт прибытия: " << obj.arrival   << '\n'
        << "Стоимость билета: "   << obj.cost      << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, FlightTicket& obj) {
    char buf[256];

    std::cout << "Аэропорт вылета: ";
    in >> buf;
    obj.departure = new char[strlen(buf) + 1];
    strcpy((char*)obj.departure, buf);

    std::cout << "Аэропорт прибытия: ";
    in >> buf;
    obj.arrival = new char[strlen(buf) + 1];
    strcpy((char*)obj.arrival, buf);

    std::cout << "Стоимость билета: ";
    in >> obj.cost;

    return in;
}
