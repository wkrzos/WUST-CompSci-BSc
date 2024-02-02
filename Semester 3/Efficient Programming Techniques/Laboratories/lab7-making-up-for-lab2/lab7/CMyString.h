#ifndef CMYSTRING_H
#define CMYSTRING_H

#include <cstring>
#include <string>

class MyStringPtr {
public:
    MyStringPtr() : data(nullptr) {}
    MyStringPtr(const char* str) : data(nullptr) {
        if (str != nullptr) {
            data = new char[strlen(str) + 1];
            strcpy_s(data, strlen(str) + 1, str);
        }
    }
    ~MyStringPtr() {
        if (data != nullptr) {
            delete[] data;
        }
    }

    MyStringPtr(const MyStringPtr& other) : data(nullptr) {
        if (other.data != nullptr) {
            data = new char[strlen(other.data) + 1];
            strcpy_s(data, strlen(other.data) + 1, other.data);
        }
    }

    MyStringPtr& operator=(const MyStringPtr& other) {
        if (this != &other) {
            if (data != nullptr) {
                delete[] data;
            }
            if (other.data != nullptr) {
                data = new char[strlen(other.data) + 1];
                strcpy_s(data, strlen(other.data) + 1, other.data);
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    char* get() const {
        return data;
    }

private:
    char* data;
};

class CMyString {
public:
    CMyString();
    CMyString(const CMyString& other);
    ~CMyString();

    CMyString& operator=(const char* newStr);
    CMyString& operator+=(const char* appendString);
    CMyString operator+(const char* appendStr) const;
    std::string sToStandard() const;
    operator bool() const;

private:
    MyStringPtr strPtr;
};

#endif // CMYSTRING_H
