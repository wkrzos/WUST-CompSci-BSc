#include "CMyString.h"
#include <cstring>

CMyString::CMyString() {
    str = nullptr;
}

CMyString::CMyString(const CMyString& other) {
    if (other.str != nullptr) {
        str = new char[strlen(other.str) + 1];
        strcpy_s(str, strlen(other.str) + 1, other.str);
    }
    else {
        str = nullptr;
    }
}

CMyString::~CMyString() {
    // Check if str is not nullptr to avoid deleting nullptr,
    // which is safe but unnecessary.
    if (str != nullptr) {
        delete[] str;
        str = nullptr; // Optional: Prevent dangling pointer after deletion.
    }
}


CMyString& CMyString::operator=(const char* newStr) {
    if (str != nullptr) {
        delete[] str;
    }
    if (newStr != nullptr) {
        str = new char[strlen(newStr) + 1];
        strcpy_s(str, strlen(newStr) + 1, newStr);
    }
    else {
        str = nullptr;
    }
    return *this;
}

CMyString& CMyString::operator+=(const char* appendString) {
    if (appendString != nullptr) {
        char* temp = new char[strlen(str) + strlen(appendString) + 1];
        strcpy_s(temp, strlen(str) + strlen(appendString) + 1, str);
        strcat_s(temp, strlen(str) + strlen(appendString) + strlen(appendString) + 1, appendString);
        if (str != nullptr) {
            delete[] str;
        }
        str = temp;
    }
    return *this;
}

CMyString CMyString::operator+(const char* appendStr) const {
    CMyString result(*this);
    result += appendStr;
    return result;
}

std::string CMyString::sToStandard() const {
    if (str != nullptr) {
        return std::string(str);
    }
    else {
        return std::string();
    }
}

CMyString::operator bool() const {
    return (str != nullptr && strlen(str) > 0);
}
