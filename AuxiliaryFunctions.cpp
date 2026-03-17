#include "AuxiliaryFunctions.hpp"

char* readLine() {
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];

    std::cin.getline(buffer, BUFFER_SIZE);

    char* result = new char[strlen(buffer) + 1];
    strcpy(result, buffer);

    return result;
}
int gcd(int a, int b) {
        a = abs(a);
        b = abs(b);
        while (b) { int t = b; b = a % b; a = t; }
        return a;
    }

void normalize(int& integer, int& numerator, int& denominator) {
    int totalNum = integer * denominator + (integer < 0 ? -numerator : numerator);

    int g = gcd(abs(totalNum), denominator);
    totalNum    /= g;
    denominator /= g;

    integer     = totalNum / denominator;
    numerator   = abs(totalNum % denominator);
}
