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

class TicketArr {
 private:
    FlightTicket* data;
    int size;
    int capacity;

    void Resize() {
        int newCap = capacity * 2;
        FlightTicket* NewData = new FlightTicket[newCap];
        for (int i{}; i < capacity; i++) {
            NewData[i] = data[i];
        }
        delete[] data;
        data = NewData;
        capacity = newCap;
    }

 public:
    TicketArr() {
        size = 0;
        capacity = 4;
        data = new FlightTicket[capacity];
    }
    ~TicketArr() { delete[] data; }

    int get_size() const { return size; }

    void add(FlightTicket& ticket) {
        if (size == capacity) {
            Resize();
        }
        data[size++] = ticket;
    }

    bool remove_by_cost(int cost) {
        for (int i{}; i < size; i++) {
            if (data[i].get_cost() == cost) {
                for (int j = i; j < size - 1; j++) {
                    data[j] = data[j + 1];
                    size--;
                    return true;
                }
            }
        }
        return false;
    }

    void sort_by_cost() {
        for (int i{}; i < size - 1; i++) {
            for (int j = i; j < size - i - 1; j++) {
                if (data[i].get_cost() > data[j + 1].get_cost()) {
                    FlightTicket tmp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = tmp;
                }
            }
        }
    }

    void sort_by_dep() {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - i - 1; j++)
                if (strcmp(data[j].get_dep(), data[j + 1].get_dep()) > 0) {
                    FlightTicket tmp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = tmp;
                }
    }

    int find(const char* arr) const {
        for (int i = 0; i < size; i++)
            if (strcmp(data[i].get_arr(), arr) == 0)
                return i;
        return -1;
    }

    void print_all() const {
        if (size == 0) {
            std::cout << "Массив пуст.\n";
            return;
        }
        for (int i = 0; i < size; i++) {
            std::cout << "[" << i << "]\n" << data[i] << '\n';
        }
    }

    bool load(const char* filename) {
        std::ifstream file(filename);
        if (!file.is_open())
            return false;
        delete[] data;
        capacity = 4;
        size = 0;
        data = new FlightTicket[capacity];
        char dep[kBuffSize], arr[kBuffSize];
        double cost;
        while (file >> dep >> arr >> cost) {
            FlightTicket t(dep, arr, cost);
            add(t);
        }
        file.close();
        return true;
    }

    // Сохранение в файл
    bool save(const char* filename) const {
        std::ofstream file(filename);
        if (!file.is_open())
            return false;
        for (int i = 0; i < size; i++)
            file << data[i].get_dep() << ' ' << data[i].get_arr() << ' ' << data[i].get_cost() << '\n';
        file.close();
        return true;
    }

    FlightTicket& operator[](int i) { return data[i]; }
    const FlightTicket& operator[](int i) const { return data[i]; }
};
