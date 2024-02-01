#include "CMyString.h"
#include <cstring>

CMyString::CMyString() : data(nullptr) {}

CMyString::CMyString(const CMyString& other) {
    if (other.data) {
        data = new char[strlen(other.data) + 1];
        strcpy_s(data, strlen(other.data) + 1, other.data);
    }
    else {
        data = nullptr;
    }
}

CMyString::CMyString(const char* str) {
    if (str) {
        data = new char[strlen(str) + 1];
        strcpy_s(data, strlen(str) + 1, str);
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
            strcpy_s(data, strlen(other.data) + 1, other.data);
        }
        else {
            data = nullptr;
        }
    }
    return *this;
}

CMyString CMyString::operator+(const CMyString& other) const {
    int thisLen = this->data ? strlen(this->data) : 0;
    int otherLen = other.data ? strlen(other.data) : 0;
    CMyString newString;
    newString.data = new char[thisLen + otherLen + 1];

    if (this->data) {
        strcpy_s(newString.data, thisLen + 1, this->data);
    }

    if (other.data) {
        strcat_s(newString.data, thisLen + otherLen + 1, other.data);
    }

    return newString;
}

std::string CMyString::sToStandard() const {
    return std::string(data ? data : "");
}

CMyString::operator bool() const {
    return data != nullptr && strlen(data) > 0;
}
