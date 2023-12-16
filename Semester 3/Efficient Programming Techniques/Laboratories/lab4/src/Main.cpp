#include "ExpressionTreeInterface.h"
#include <iostream>

int main() {

    std::cout << "[DEBUG] Welcome to the Expression Tree Interface!" << std::endl;

    ExpressionTreeInterface<std::string>::run();

    return 0;
}
