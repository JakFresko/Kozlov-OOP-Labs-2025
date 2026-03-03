#pragma once
#include <cstring>
#include <iostream>

class FlightTicket {
 private:
    char* departure;
    char* arrival;
    double cost;
    static int quantity;

 public:
    FlightTicket() {
        departure = new char[1]{'\0'};
        arrival = new char[1]{'\0'};
        cost = 0;
        quantity++;
    }
    FlightTicket(const char* dep, const char* arr, double cst) {
        departure = new char[strlen(dep) + 1];
        strncpy(departure, dep, strlen(dep) + 1);
        arrival = new char[strlen(arr) + 1];
        strncpy(arrival, arr, strlen(arr) + 1);
        cost = cst;
        quantity++;
    }
    FlightTicket(const FlightTicket& ticket) {
        departure = new char[strlen(ticket.departure) + 1];
        strncpy(departure, ticket.departure, strlen(ticket.departure) + 1);
        arrival = new char[strlen(ticket.arrival) + 1];
        strncpy(arrival, ticket.arrival, strlen(ticket.arrival) + 1);
        cost = ticket.cost;
        quantity++;
    }
    ~FlightTicket() {
        delete[] departure;
        delete[] arrival;
        quantity--;
    }
    FlightTicket& operator=(const FlightTicket& other) {
        if (this != &other) {
            delete[] departure;
            delete[] arrival;
            departure = new char[strlen(other.departure) + 1];
            strncpy(departure, other.departure, strlen(other.departure) + 1);
            arrival = new char[strlen(other.arrival) + 1];
            strncpy(arrival, other.arrival, strlen(other.arrival) + 1);
            cost = other.cost;
        }
        return *this;
    }

    const char* get_dep() const { return departure; }
    const char* get_arr() const { return arrival; }
    double get_cost() const { return cost; }
    static int get_quantity() { return quantity; }

    void set_dep(const char* dep) {
        delete[] departure;
        departure = new char[strlen(dep) + 1];
        strncpy(departure, dep, strlen(dep) + 1);
    }
    void set_arr(const char* arr) {
        delete[] arrival;
        arrival = new char[strlen(arr) + 1];
        strncpy(arrival, arr, strlen(arr) + 1);
    }
    void set_cost(double cst) { cost = cst; }

    friend std::ostream& operator<<(std::ostream& out, const FlightTicket& obj);
    friend std::istream& operator>>(std::istream& in, FlightTicket& obj);
};
