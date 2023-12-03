#include <iostream>
#include <string>
#include "ExpressionInterface.h"
#include "PrefixExpressionParser.h"

int main() {
    ExpressionInterface interface;

    std::string command;
    while (true) {
        std::cout << "Enter a command ('quit' to exit): ";
        std::getline(std::cin, command);

        if (command == "quit") {
            break;
        }

        interface.executeCommand(command);
    }

    return 0;
}
