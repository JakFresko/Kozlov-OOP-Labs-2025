#pragma once
#include <cmath>
#include <iostream>

class Area {
    protected:
        char* AreaName;

        static Area** container;
        static int size;
        static int capacity;
        static void resize();
    public:
        Area();
        Area(const char*);
        Area(const Area&);
        Area& operator=(const Area&);
        virtual ~Area();
        virtual void show() = 0;
        virtual void input(std::istream& in) = 0;

        static int get_size();

        friend std::istream& operator>>(std::istream& in, Area& obj) {
            obj.input(in);
            return in;
        }

        static void AddToContainer(Area*);
        static void print();
        static void printByIndex(int);
        static void remove(int index);
        static void clear();
};

class Town : public Area {
    protected:
        char* TownName;
    public:
        Town();
        Town(char*, char*);
        Town(const Town&);
        Town& operator=(const Town&);
        void show() override;
        void input(std::istream& in) override;
        ~Town();
};

class Megapolis : public Town {
    protected:
        bool IsMegapolis;
        int Population;
    public:
        Megapolis();
        Megapolis(char*, char*, bool, int);
        Megapolis(const Megapolis&);
        Megapolis& operator=(const Megapolis&);
        void show() override;
        void input(std::istream& in) override;
        ~Megapolis();
};

class Place : public Megapolis {
    protected:
        char* PlaceName;
    public:
        Place();
        Place(char*, char*, bool, int, char*);
        Place(const Place&);
        Place& operator=(const Place&);
        void show() override;
        void input(std::istream& in) override;
        ~Place();
};
