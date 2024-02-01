#ifndef CMYSTRING_H

//#define _CRT_SECURE_NO_WARNINGS
#define CMYSTRING_H

#include <string>

class CMyString {
public:
    CMyString();
    CMyString(const CMyString& other);
    CMyString(const char* str);
    ~CMyString();

    CMyString& operator=(const CMyString& other);
    CMyString operator+(const CMyString& other) const;

    std::string sToStandard() const;
    operator bool() const;

private:
    char* data;
};

#endif // CMYSTRING_H
