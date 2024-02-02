#include "CMyString.h"
#include <cstring>

CMyString::CMyString() : strPtr(nullptr) {}

CMyString::CMyString(const CMyString& other) : strPtr(other.strPtr) {}

CMyString::~CMyString() {}

CMyString& CMyString::operator=(const char* newStr) {
    strPtr = MyStringPtr(newStr);
    return *this;
}

CMyString CMyString::operator+(const char* appendStr) const {
    CMyString result(*this);
    result += appendStr;
    return result;
}

CMyString& CMyString::operator+=(const char* appendString) {
    if (strPtr.get() != nullptr) {
        char* temp = new char[strlen(strPtr.get()) + strlen(appendString) + 1];
        strcpy_s(temp, strlen(strPtr.get()) + strlen(appendString) + 1, strPtr.get());
        strcat_s(temp, strlen(strPtr.get()) + strlen(appendString) + strlen(appendString) + 1, appendString);
        strPtr = MyStringPtr(temp);
    }
    return *this;
}

std::string CMyString::sToStandard() const {
    if (strPtr.get() != nullptr) {
        return std::string(strPtr.get());
    }
    else {
        return std::string();
    }
}

CMyString::operator bool() const {
    return (strPtr.get() != nullptr && strlen(strPtr.get()) > 0);
}
