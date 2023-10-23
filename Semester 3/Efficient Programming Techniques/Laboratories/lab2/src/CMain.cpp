#include <iostream>
#include "CNumber.h"

using namespace std;

int main() {

    //EXCERCISE 1
    cout << std::endl << "EXCERCISE 1" << std::endl;

    // Creating two objects of the CNumber class
    CNumber number1;
    CNumber number2;

    // Initializing objects with int values
    int value1 = 12345;
    int value2 = -6789;

    // Assigning values to CNumber objects
    number1 = value1;
    number2 = value2;

    // Displaying the values of CNumber objects
    std::cout << "Number 1: ";
    number1.vPrint();

    std::cout << "Number 2: ";
    number2.vPrint();

    //EXCERCISE 2
    cout << std::endl << "EXCERCISE 2" << std::endl;

    CNumber num_1, num_2;
    
    num_1 = 368;
    num_1.vPrint();

    num_2 = 1567;
    num_2.vPrint();

    num_1 = num_2;
    num_1.vPrint();

    //EXCERCISE 3
    /*
    After deleting the constructior, some functionality has been lost. It was used in both operator= functions to delete the arrays.
    */

    //EXCERCISE 5
    cout << std::endl << "EXCERCISE 5" << std::endl;

    string str_1;

    str_1 = num_1.sToStr();

    cout << str_1;

    //EXCERCISE 6
    cout << std::endl << "EXCERCISE 6" << std::endl;

    CNumber num_3;
    num_3 = num_1 + num_2;

    string str_2;
    str_2 = num_3.sToStr();

    cout << str_2;

}