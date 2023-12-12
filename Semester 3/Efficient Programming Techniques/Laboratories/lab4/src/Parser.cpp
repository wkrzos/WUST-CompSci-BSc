#include "Parser.h"
#include <sstream>
#include <iostream>

void Parser::parseFormula(Tree& tree, std::string formula)
{
    if (tree.getRoot() != nullptr)
        delete tree.getRoot();

    Node* root = new Node();
    tree.setRoot(root);

    bool wasError = false;
    tree.clearArguments(); // Assume this method resets argsMap and argsVector

    int start = parseNodes(root, formula, 0, &wasError, tree);

    if (formula.length() > start)
    {
        tree.getErrorStream() << "Error: Too many arguments" << std::endl;
        wasError = true;
    }

    if (wasError)
    {
        tree.getErrorStream() << "Corrected formula: " << tree.toString() << std::endl;
    }
}

int Parser::parseNodes(Node* currentNode, std::string formula, int start, bool* wasError, Tree& tree)
{
    std::string value = "";

    while (formula.length() > start && formula[start] == ' ')
    {
        start++;
    }

    while (formula.length() > start && formula[start] != ' ')
    {
        value += formula[start];
        start++;
    }

    value.erase(value.find_last_not_of(' ') + 1);

    std::map<std::string, int>::const_iterator numberOfArgsIterator = funMap.find(value);

    currentNode->setValue(value);

    if (numberOfArgsIterator != funMap.end())
    {
        currentNode->setNumberOfNodes(numberOfArgsIterator->second);
        currentNode->setNodeType(OPERATOR);

        for (int i = 0; i < currentNode->getNumberOfNodes(); i++)
        {
            if (formula.length() <= start)
            {
                tree.getErrorStream() << "Error: Not enough arguments for operator: " << value << ", substituting 1" << std::endl;
                currentNode->getNode(i)->setNumberOfNodes(0);
                currentNode->getNode(i)->setNodeType(VALUE);
                currentNode->getNode(i)->setValue("1");

                *wasError = true;
            }
            else
            {
                start = parseNodes(currentNode->getNode(i), formula, start, wasError, tree);
            }
        }

        if (value == "#")
        {
            if (currentNode->getNode(0)->getNodeType() != ARGUMENT || currentNode->getNode(1)->getNodeType() != OPERATOR)
            {
                tree.getErrorStream() << "Error: Invalid arguments for #, required: ARGUMENT and OPERATOR, substituting 1" << std::endl;

                currentNode->setNumberOfNodes(0);
                currentNode->setNodeType(VALUE);
                currentNode->setValue("1");
            }
        }
    }
    else if (value.find_first_not_of(LIST_OF_NUMBERS) == std::string::npos)
    {
        currentNode->setNumberOfNodes(0);
        currentNode->setNodeType(VALUE);
    }
    else if (isValidArgument(value))
    {
        currentNode->setNumberOfNodes(0);
        currentNode->setNodeType(ARGUMENT);

        tree.setArgumentValue(value, -1);
    }
    else
    {
        tree.getErrorStream() << "Error: Unknown operator: " << value << std::endl;
    }

    return start;
}

bool Parser::isValidArgument(std::string value)
{
    if (value.empty())
    {
        return false;
    }

    bool hasLetter = false;
    for (size_t i = 0; i < value.length(); ++i)
    {
        if (isalpha(value[i]))
        {
            hasLetter = true;
        }
        else if (!isdigit(value[i]))
        {
            std::cout << "Invalid character ignored: " << value[i] << std::endl;
        }
    }

    return hasLetter;
}

std::map<std::string, int> createFunctionMap()
{
    std::map<std::string, int> m;

    m["sin"] = 1;
    m["cos"] = 1;
    m["+"] = 2;
    m["-"] = 2;
    m["*"] = 2;
    m["/"] = 2;
    m["#"] = 2;

    return m;
}

const std::map<std::string, int> Parser::funMap = createFunctionMap();