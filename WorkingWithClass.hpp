#pragma once
#include <cstring>
#include <fstream>
#include <iostream>

namespace {
    const int kBuffSize = 256;
}

class FlightTicket {
 private:
    char* departure;
    char* arrival;
    double cost;
    static int quantity;

 public:
    FlightTicket();
    FlightTicket(const char* dep, const char* arr, double cst);
    FlightTicket(const FlightTicket& ticket);
    ~FlightTicket();
    FlightTicket& operator=(const FlightTicket& other);

    const char* get_dep() const;
    const char* get_arr() const;
    double get_cost() const;
    static int get_quantity();

    void set_dep(const char* dep);
    void set_arr(const char* arr);
    void set_cost(double cst);

    friend std::ostream& operator<<(std::ostream& out, const FlightTicket& obj);
    friend std::istream& operator>>(std::istream& in, FlightTicket& obj);
};

class TicketArr {
 private:
    FlightTicket* data;
    int size;
    int capacity;

    void Resize();

 public:
    TicketArr();
    ~TicketArr();

    int get_size() const;

    void add(FlightTicket& ticket);

    bool remove_by_cost(int cost);

    void sort_by_cost();

    void sort_by_dep();

    int find(const char* arr) const;

    void print_all() const;
    bool load(const char* filename);

    // Сохранение в файл
    bool save(const char* filename) const;

    FlightTicket& operator[](int i) { return data[i]; }
    const FlightTicket& operator[](int i) const { return data[i]; }
};
