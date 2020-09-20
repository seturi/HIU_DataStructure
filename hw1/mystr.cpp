#include <iostream>
#include <cstring>
#include "mystr.h"
using namespace std;

Mystring::Mystring(const char* str = "default") {
    len = strlen(str);
    string = new char[len + 1];
    strcpy(string, str);
}

bool Mystring::operator ==(const Mystring& str) {
    if (strcmp(string, str.string) == 0) {
        return true;
    }
    return false;
}

Mystring& Mystring::operator =(const Mystring& str) {
    if (string != NULL) {
        delete[]string;
    }
    len = str.len;
    string = new char[len + 1];
    strcpy(string, str.string);
    return *this;
}

Mystring Mystring ::operator *(const Mystring& str) {
    int minLen;
    char* temp = new char[len + str.len + 1];

    if (len >= str.len) {
        minLen = str.len;
    }
    else {
        minLen = len;
    }

    int tempidx = 0;
    for (int j = 0; j < minLen; j++) {
        temp[tempidx++] = string[j];
        temp[tempidx++] = str.string[j];
    }

    if (len > str.len) {
        for (int j = minLen; j <= len; j++) {
            temp[tempidx++] = string[j];
        }
    }
    else if (len < str.len) {
        for (int j = minLen; j <= str.len; j++) {
            temp[tempidx++] = str.string[j];
        }
    }
    return Mystring(temp);
}

Mystring Mystring::operator +(const Mystring& str) {
    char* temp = new char[len + str.len + 1];
    strcpy(temp, string);
    strcat(temp, str.string);
    return Mystring(temp);
}

ostream& operator <<(ostream& out, const Mystring& str) {
    out << str.string;
    return out;
}

Mystring::~Mystring() { delete[] string; }