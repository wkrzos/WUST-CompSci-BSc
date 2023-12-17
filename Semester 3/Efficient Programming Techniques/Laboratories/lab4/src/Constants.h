#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Main
const std::string WELCOME_MESSAGE = "===== Welcome to the Prefix Expression to Tree Parser =====";
const std::string SELECT_DATA_TYPE_MESSAGE = "Select data type for the Expression Tree (1 for int, 2 for double, 3 for std::string): ";
const std::string INVALID_CHOICE_MESSAGE = "[!] Invalid choice. Bye, exiting...";

// PrefixExpressionTree
const std::string ERROR_WRONG_NUM_ARGS = "[!] The number of given arguments is wrong. Try the vars command.";
const std::string ERROR_DIVISION_BY_ZERO = "[!] Holy hell, don't divide by zero, amigo!";
const std::string ERROR_NO_FORMULA = "[!] The formula is missing.";

const std::string ERROR_INVALID_ARG = "[DEBUG] The argument is not valid.";
const std::string ERROR_UNKNOWN_ARG = "[DEBUG] Uknown argument.";

const std::string UNSPECIFIED_TYPE = "UNSPECIFIED";
const std::string INT_TYPE = "INT";
const std::string DOUBLE_TYPE = "DOUBLE";
const std::string STRING_TYPE = "STRING";

// PrefixExpressionParser
const std::string ERROR_NOT_ENOUGH_ARGS = "[!] This operator requires a different number of arguments.";
const std::string ERROR_INVALID_CHARACTER = "[!] Wrong symbol spotted in the name of a variable. Use latin letters and numbers only.";
const std::string FORMULA_CORRECTED = "[!] Mistake found in the entered formula. It has been repaired! Try the print command.";

const std::string ERROR_UNKNOWN_OPERATION = "[DEBUG] Unknown operation.";

#endif // CONSTANTS_H
