#include <iostream>
#include "CMyString.h"

int main() {
    CMyString c_str;
    c_str = "Ala ";
    c_str += "ma ";
    c_str += "kota ";
    c_str = c_str + "i psa.";

    std::cout << "Wartosc obiektu c_str: " << c_str.sToStandard() << std::endl;

    if (c_str) {
        std::cout << "Obiekt c_str zawiera znaki." << std::endl;
    }
    else {
        std::cout << "Obiekt c_str jest pusty." << std::endl;
    }

    return 0;
}
