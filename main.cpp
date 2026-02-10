#include "/home/maxim/cpp/Kozlov-OOP-Labs-2025/StringCL.hpp"
#include <iostream>

int main() {

    char* str1 = StringConcatenate("Hellow, ", "World!");
    int len = StringLength(str1);
    for(int i{}; i < len; i++) {
        std::cout << str1[i];
    }
    std::cout << '\n';
    std::cout << "Длина строки " << len << '\n';
}
