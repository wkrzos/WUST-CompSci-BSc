#include <cstring>

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

    // Copy constructor
    MyStringPtr(const MyStringPtr& other) : data(nullptr) {
        if (other.data != nullptr) {
            data = new char[strlen(other.data) + 1];
            strcpy_s(data, strlen(other.data) + 1, other.data);
        }
    }

    // Assignment operator
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
