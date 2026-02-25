#pragma once
#include <iostream>
#include <cstring>

class FlightTicket {
    private:
        const char* departure;
        const char* arrival;
        double cost;
        static int quantity;
    public:
        FlightTicket() {
            departure = new char[1]{'\0'};
            arrival   = new char[1]{'\0'};
            cost = 0;
            quantity++;
        }
        FlightTicket(const char* dep, const char* arr, double cst) {
            departure = new char[strlen(dep) + 1];
            strcpy((char*)departure, dep);
            arrival = new char[strlen(arr) + 1];
            strcpy((char*)arrival, arr);
            cost = cst;
            quantity++;
        }
        FlightTicket(const FlightTicket& ticket) {
            departure = new char[strlen(ticket.departure) + 1];
            strcpy((char*)departure, ticket.departure);
            arrival = new char[strlen(ticket.arrival) + 1];
            strcpy((char*)arrival, ticket.arrival);
            cost = ticket.cost;
            quantity++;
        }
        ~FlightTicket() {
            delete[] departure;
            delete[] arrival;
            quantity--;
        }
        FlightTicket& operator=(const FlightTicket& other) {
            if(this != &other) {
                delete[] departure;
                delete[] arrival;
                departure = new char[strlen(other.departure) + 1];
                strcpy((char*)departure, other.departure);
                arrival = new char[strlen(other.arrival) + 1];
                strcpy((char*)arrival, other.arrival);
                cost = other.cost;
            }
            return *this;
        }

        const char* get_dep()  const { return departure; }
        const char* get_arr()  const { return arrival; }
        double      get_cost() const { return cost; }
        static int  get_quantity()   { return quantity; }

        void set_dep(const char* dep) {
            delete[] departure;
            departure = new char[strlen(dep) + 1];
            strcpy((char*)departure, dep);
        }
        void set_arr(const char* arr) {
            delete[] arrival;
            arrival = new char[strlen(arr) + 1];
            strcpy((char*)arrival, arr);
        }
        void set_cost(double cst) { cost = cst; }

        friend std::ostream& operator<<(std::ostream& out, const FlightTicket& obj);
        friend std::istream& operator>>(std::istream& in,  FlightTicket& obj);
};
