/*
#include "CMyString.h"
#include <cstring>

CMyString::CMyString() : data(nullptr) {}

CMyString::CMyString(const CMyString& other) {
    // Alokacja i kopiowanie danych
    if (other.data) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }
    else {
        data = nullptr;
    }
}

CMyString::CMyString(const char* str) {
    // Alokacja i kopiowanie danych
    if (str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    else {
        data = nullptr;
    }
}

CMyString::~CMyString() {
    delete[] data;
}

CMyString& CMyString::operator=(const CMyString& other) {
    if (this != &other) {
        delete[] data;
        if (other.data) {
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        else {
            data = nullptr;
        }
    }
    return *this;
}

CMyString CMyString::operator+(const CMyString& other) const {
    CMyString newString;
    int thisLen = strlen(this->data);
    int otherLen = strlen(other.data);
    newString.data = new char[thisLen + otherLen + 1];
    strcpy(newString.data, this->data);
    strcat(newString.data, other.data);
    return newString;
}

std::string CMyString::sToStandard() const {
    return std::string(data);
}

CMyString::operator bool() const {
    return data != nullptr && strlen(data) > 0;
}
*/