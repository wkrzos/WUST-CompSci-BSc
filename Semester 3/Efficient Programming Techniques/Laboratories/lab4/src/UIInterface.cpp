#include "UIInterface.h"
#include "Tree.h"
#include "Parser.h"
#include "stringUtils.h"
#include <iostream>

void UIInterface::startUI()
{
    Tree currentTree;
    Parser parser;

    while (true)
    {
        int argumentCount = 0;

        std::string userStringInput;
        std::getline(std::cin, userStringInput);
        std::string* arguments = argumentStringToArray(userStringInput, &argumentCount);

        if (argumentCount > 0)
        {
            std::string command = arguments[0];

            if (command == "exit")
            {
                return;
            }
            else
            {
                executeCommand(command, currentTree, parser, arguments, argumentCount);
            }
        }

        // No arguments provided
        else
        {
            std::cout << "No command entered. Please enter a valid command." << std::endl;
        }
    }
}


void UIInterface::executeCommand(std::string &command, Tree &currentTree, Parser &parser, std::string *arguments, int &argumentCount) {
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

void UIInterface::handleEnterCommand(Tree& tree, Parser& parser, std::string* args, int size)
{
    if (size < 2)
    {
        std::cout << "Invalid command, use: enter <formula>" << std::endl;
        return;
    }

    std::string formula = join(args + 1, size - 1);
    parser.parseFormula(tree, formula);
    std::cout << tree.getErrorAndClear() << std::endl;
}

void UIInterface::handleVarsCommand(const Tree& tree)
{
    std::cout << tree.getArgumentsList() << std::endl;
}

void UIInterface::handlePrintCommand(const Tree& tree)
{
    std::cout << tree.toString() << std::endl;
}

void UIInterface::handleCompCommand(Tree& tree, std::string* args, int size)
{
    std::string formula = join(args + 1, size - 1);
    int result = tree.comp(formula);

    if (result != -1)
    {
        std::cout << "Result: " << result << std::endl;
    }
    else
    {
        std::cout << tree.getErrorAndClear() << std::endl;
    }
}

void UIInterface::handleJoinCommand(Tree& tree, Parser& parser, std::string* args, int size)
{
    if (size < 2)
    {
        std::cout << "Invalid command, use: join <tree>" << std::endl;
        return;
    }
    else 
    {
        std::string formula = join(args + 1, size - 1);

        Tree newTree;
        parser.parseFormula(newTree, formula);

        std::cout << newTree.getErrorAndClear() << std::endl;

        tree = tree + newTree;
    }
}