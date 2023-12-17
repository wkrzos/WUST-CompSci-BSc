#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Main
const std::string WELCOME_MESSAGE = "Welcome to the Expression Tree Interface!";
const std::string SELECT_DATA_TYPE_MESSAGE = "Select data type for the Expression Tree (1 for int, 2 for double, 3 for std::string): ";
const std::string INVALID_CHOICE_MESSAGE = "Invalid choice. Exiting...";

// PrefixExpressionTree
const std::string LIST_OF_NUMBERS = "0123456789";

const std::string ERROR_WRONG_NUM_ARGS = "Error: Wrong number of arguments.";
const std::string ERROR_INVALID_ARG = "Error: Invalid argument.";
const std::string ERROR_NO_FORMULA = "Error: No formula.";
const std::string ERROR_UNKNOWN_ARG = "Error: Unknown argument.";
const std::string ERROR_DIVISION_BY_ZERO = "Division by zero";

const std::string UNSPECIFIED_TYPE = "UNSPECIFIED";
const std::string INT_TYPE = "INT";
const std::string DOUBLE_TYPE = "DOUBLE";
const std::string STRING_TYPE = "STRING";

#endif // CONSTANTS_H
