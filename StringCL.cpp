#include "StringCL.hpp"

int StringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char* StringConcatenate(const char* str1, const char* str2) {
    int len1 = StringLength(str1);
    int len2 = StringLength(str2);
    char* result = new char[len1 + len2 + 1];
    for (int i = 0; i < len1; i++) {
        result[i] = str1[i];
    }
    for (int i = 0; i < len2; i++) {
        result[len1 + i] = str2[i];
    }
    result[len1 + len2] = '\0';
    return result;
}
