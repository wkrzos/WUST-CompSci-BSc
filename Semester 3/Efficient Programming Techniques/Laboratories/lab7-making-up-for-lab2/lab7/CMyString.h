#ifndef CMYSTRING_H
#define CMYSTRING_H

#include <string>

class CMyString {
private:
    char* str;

public:
    CMyString(); // Konstruktor bezparametrowy
    CMyString(const CMyString& other); // Konstruktor kopiujący
    ~CMyString(); // Destruktor

    CMyString& operator=(const char* newStr); // Przeciążony operator przypisania =
    CMyString& operator+=(const char* appendString); // Przeciążony operator +=
    CMyString operator+(const char* appendStr) const; // Przeciążony operator +

    std::string sToStandard() const; // Metoda zwracająca wartość obiektu jako std::string
    operator bool() const; // Przeciążony operator rzutowania do bool
};

#endif // CMYSTRING_H
