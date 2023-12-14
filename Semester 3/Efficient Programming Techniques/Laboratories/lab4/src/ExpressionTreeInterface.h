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
    static void executeCommand(std::string& command, PrefixExpressionTree& currentTree, Parser& parser, std::string* arguments, int& argumentCount);
    static void handleEnterCommand(PrefixExpressionTree& tree, Parser& parser, std::string* args, int size);
    static void handleVarsCommand(const PrefixExpressionTree& tree);
    static void handlePrintCommand(const PrefixExpressionTree& tree);
    static void handleCompCommand(PrefixExpressionTree& tree, std::string* args, int size);
    static void handleJoinCommand(PrefixExpressionTree& tree, Parser& parser, std::string* args, int size);
};

#endif // EXPRESSIONTREEINTERFACE_H


template <typename T>
void ExpressionTreeInterface<T>::run()
{

    int numOfArgs = 0;

    PrefixExpressionTree currentTree;
    Parser currentParser;

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
void ExpressionTreeInterface<T>::executeCommand(std::string& command, PrefixExpressionTree& currentTree, Parser& parser, std::string* arguments, int& argumentCount) {
    if (command == "enter")
    {
        handleEnterCommand(currentTree, parser, arguments, argumentCount);
    }
    else if (command == "vars")
    {
        handleVarsCommand(currentTree);
    }
    else if (command == "print")
    {
        handlePrintCommand(currentTree);
    }
    else if (command == "comp")
    {
        handleCompCommand(currentTree, arguments, argumentCount);
    }
    else if (command == "join")
    {
        handleJoinCommand(currentTree, parser, arguments, argumentCount);
    }
}

template <typename T>
void ExpressionTreeInterface<T>::handleEnterCommand(PrefixExpressionTree& tree, Parser& parser, std::string* args, int size)
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
void ExpressionTreeInterface<T>::handleVarsCommand(const PrefixExpressionTree& tree)
{
    std::cout << tree.getArgumentsList() << std::endl;
}

void ExpressionTreeInterface<T>::handlePrintCommand(const PrefixExpressionTree& tree)
{
    std::cout << tree.toString() << std::endl;
}

template <typename T>
void ExpressionTreeInterface<T>::handleCompCommand(PrefixExpressionTree& tree, std::string* args, int size)
{
    std::string formula = joinArrayIntoString(args + 1, size - 1);
    int result = tree.comp(formula);

    std::cout << "The result is: " << result << std::endl;
}

template <typename T>
void ExpressionTreeInterface<T>::handleJoinCommand(PrefixExpressionTree& tree, Parser& parser, std::string* args, int size)
{
    if (size < 2)
    {
        std::cout << "Wrong command. Please enter a valid command." << std::endl;

        return;
    }
    else
    {
        PrefixExpressionTree newTree;

        std::string formula = joinArrayIntoString(args + 1, size - 1);
        parser.parseFormula(newTree, formula);
        tree = tree + newTree;
    }
}
