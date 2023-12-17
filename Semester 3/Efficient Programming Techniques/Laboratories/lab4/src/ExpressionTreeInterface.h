#ifndef EXPRESSIONTREEINTERFACE_H
#define EXPRESSIONTREEINTERFACE_H

#include "PrefixExpressionTree.h"
#include "Parser.h"
#include "ExpressionTreeInterface.h"
#include "Parser.h"
#include "stringUtils.h"
#include <iostream>

template <typename T>
class ExpressionTreeInterface
{
public:
    static void run();

private:
    static void executeCommand(std::string& command, PrefixExpressionTree<T>& currentTree, PrefixExpressionParser<T>& parser, std::string* arguments, int& argumentCount);

    static void handleEnterCommand(PrefixExpressionTree<T>& tree, PrefixExpressionParser<T>& parser, std::string* args, int size);
    static void handleVarsCommand(const PrefixExpressionTree<T>& tree);
    static void handleCompCommand(PrefixExpressionTree<T>& tree, std::string* args, int size);
    static void handleJoinCommand(PrefixExpressionTree<T>& tree, PrefixExpressionParser<T>& parser, std::string* args, int size);
    static void handlePrintCommand(const PrefixExpressionTree<T>& tree);
    static void handleWrongCommand(std::string& command);
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
                executeCommand(command, currentTree, currentParser, arguments, numOfArgs);
            }
        }

        // No arguments provided
        else
        {
            std::cout << "No command entered. Please enter a valid command." << std::endl;
        }
    }
}

template <typename T>
void ExpressionTreeInterface<T>::executeCommand(std::string& command, PrefixExpressionTree<T>& currentTree, PrefixExpressionParser<T>& parser, std::string* arguments, int& argumentCount) {
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
        std::cout << "Wrong command. Please enter a valid command." << std::endl;

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
    std::cout << tree.getArgumentsList() << std::endl;
}

template <typename T>
void ExpressionTreeInterface<T>::handleCompCommand(PrefixExpressionTree<T>& tree, std::string* args, int size)
{
    std::string formula = joinArrayIntoString(args + 1, size - 1);
    T result = tree.comp(formula); //TODO: change to T

    std::cout << "The result is: " << result << std::endl;
}

template <typename T>
void ExpressionTreeInterface<T>::handleJoinCommand(PrefixExpressionTree<T>& tree, PrefixExpressionParser<T>& parser, std::string* args, int size)
{
    if (size < 2)
    {
        std::cout << "Wrong command. Please enter a valid command." << std::endl;

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
    std::cout << tree.toString() << std::endl;
}

template <typename T>
void ExpressionTreeInterface<T>::handleWrongCommand(std::string& command) {
    std::cout << "No command " << command << " available." << std::endl;
}

#endif // EXPRESSIONTREEINTERFACE_H
