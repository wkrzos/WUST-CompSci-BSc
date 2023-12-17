#ifndef EXPRESSION_TREE_INTERFACE_H
#define EXPRESSION_TREE_INTERFACE_H

#include "PrefixExpressionTree.h"
#include "PrefixExpressionParser.h"
#include "stringUtils.h"
#include "Constants.h" // Include Constants.h for messages
#include <iostream>

template <typename T>
class ExpressionTreeInterface
{
public:
    static void run();

private:
    static void executeCommand(PrefixExpressionTree<T>& currentTree, PrefixExpressionParser<T>& parser, const std::string& command, std::string* arguments, int argumentCount);

    static void handleEnterCommand(PrefixExpressionTree<T>& tree, PrefixExpressionParser<T>& parser, std::string* args, int size);
    static void handleVarsCommand(const PrefixExpressionTree<T>& tree);
    static void handleCompCommand(PrefixExpressionTree<T>& tree, std::string* args, int size);
    static void handleJoinCommand(PrefixExpressionTree<T>& tree, PrefixExpressionParser<T>& parser, std::string* args, int size);
    static void handlePrintCommand(const PrefixExpressionTree<T>& tree);
    static void handleWrongCommand(const std::string& command);
};

template <typename T>
void ExpressionTreeInterface<T>::run()
{
    int numOfArgs = 0;
    PrefixExpressionTree<T> currentTree;
    PrefixExpressionParser<T> currentParser;

    while (true)
    {
        std::string userStringInput;
        std::getline(std::cin, userStringInput);

        std::string* arguments = splitStringIntoArray(userStringInput, &numOfArgs);

        if (numOfArgs > 0)
        {
            std::string command = arguments[0];

            if (command == "exit")
            {
                return;
            }
            else
            {
                executeCommand(currentTree, currentParser, command, arguments, numOfArgs);
            }
        }
        else
        {
            std::cout << MESSAGE_NO_COMMAND << std::endl;
        }
    }
}

template <typename T>
void ExpressionTreeInterface<T>::executeCommand(PrefixExpressionTree<T>& currentTree, PrefixExpressionParser<T>& parser, const std::string& command, std::string* arguments, int argumentCount) {
    if (command == "enter")
    {
        handleEnterCommand(currentTree, parser, arguments, argumentCount);
    }
    else if (command == "vars")
    {
        handleVarsCommand(currentTree);
    }
    else if (command == "comp")
    {
        handleCompCommand(currentTree, arguments, argumentCount);
    }
    else if (command == "join")
    {
        handleJoinCommand(currentTree, parser, arguments, argumentCount);
    }
    else if (command == "print")
    {
        handlePrintCommand(currentTree);
    }
    else
    {
        handleWrongCommand(command);
    }
}

template <typename T>
void ExpressionTreeInterface<T>::handleEnterCommand(PrefixExpressionTree<T>& tree, PrefixExpressionParser<T>& parser, std::string* args, int size)
{
    if (size < 2)
    {
        std::cout << MESSAGE_WRONG_ENTER_COMMAND << std::endl;
        return;
    }
    else
    {
        std::string formula = joinArrayIntoString(args + 1, size - 1);
        parser.parseFormula(tree, formula);
    }
}

template <typename T>
void ExpressionTreeInterface<T>::handleVarsCommand(const PrefixExpressionTree<T>& tree)
{
    std::cout << MESSAGE_RESULT_VARS << tree.getArgumentsList() << std::endl;
}

template <typename T>
void ExpressionTreeInterface<T>::handleCompCommand(PrefixExpressionTree<T>& tree, std::string* args, int size)
{
    if (size < 2)
    {
        std::cout << MESSAGE_WRONG_COMP_COMMAND << std::endl;
        return;
    }
    else
    {
        std::string formula = joinArrayIntoString(args + 1, size - 1);
        T result = tree.comp(formula); // TODO: change to T

        std::cout << MESSAGE_RESULT << result << std::endl;
    }
}

template <typename T>
void ExpressionTreeInterface<T>::handleJoinCommand(PrefixExpressionTree<T>& tree, PrefixExpressionParser<T>& parser, std::string* args, int size)
{
    if (size < 2)
    {
        std::cout << MESSAGE_WRONG_JOIN_COMMAND << std::endl;
        return;
    }
    else
    {
        PrefixExpressionTree<T> newTree;

        std::string formula = joinArrayIntoString(args + 1, size - 1);
        parser.parseFormula(newTree, formula);

        tree = tree + newTree;
    }
}

template <typename T>
void ExpressionTreeInterface<T>::handlePrintCommand(const PrefixExpressionTree<T>& tree)
{
    std::cout << MESSAGE_RESULT_PRINT << tree.toString() << std::endl;
}

template <typename T>
void ExpressionTreeInterface<T>::handleWrongCommand(const std::string& command) {
    std::cout << MESSAGE_WRONG_COMMAND << command << std::endl;
}

#endif // EXPRESSION_TREE_INTERFACE_H
