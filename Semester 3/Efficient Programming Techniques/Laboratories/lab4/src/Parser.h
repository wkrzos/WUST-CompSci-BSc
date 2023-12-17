#ifndef PARSER_H
#define PARSER_H

#include "PrefixExpressionTree.h"
#include "Parser.h"
#include <sstream>
#include <iostream>

template<typename T>
class PrefixExpressionParser
{
public:
    void parseFormula(PrefixExpressionTree<T>& peTree, std::string formula);

private:
    int parseNodes(Node* currentNode, std::string formula, int start, bool* wasError, PrefixExpressionTree<T>& tree);
    bool isValidValue(std::string value);
    bool isValidArgument(std::string value);
    static std::string getDefaultValue();
    static const std::map<std::string, int> funMap;
    std::map<std::string, int> createFunctionMap();
};

template<typename T>
void PrefixExpressionParser<T>::parseFormula(PrefixExpressionTree<T>& peTree, std::string formula)
{
    if (peTree.getRoot() != nullptr) {
        delete peTree.getRoot();
    }

    Node* root = new Node();
    peTree.setRoot(root);

    bool wasError = false;
    peTree.clearArguments(); // Assume this method resets argsMap and argsVector

    int start = parseNodes(root, formula, 0, &wasError, peTree);

    if (formula.length() > start)
    {
        std::cout << "Wrong number of arguments" << std::endl;
        wasError = true;
    }

    if (wasError)
    {
        std::cout << "Your formula has been corrected to: " << peTree.toString() << std::endl;
    }
}

template<typename T>
int PrefixExpressionParser<T>::parseNodes(Node* currentNode, std::string formula, int start, bool* wasError, PrefixExpressionTree<T>& tree)
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
        currentNode->setNodeType(OPERATION);

        for (int i = 0; i < currentNode->getNumberOfNodes(); i++)
        {
            if (formula.length() <= start)
            {
                std::cout << "Error: Not enough arguments for operator: " << value << ", substituting 1" << std::endl;
                currentNode->getNode(i)->setNumberOfNodes(0);
                currentNode->getNode(i)->setNodeType(CONSTANT);
                currentNode->getNode(i)->setValue("1");

                *wasError = true;
            }
            else
            {
                start = parseNodes(currentNode->getNode(i), formula, start, wasError, tree);
            }
        }
    }
    else if (value.find_first_not_of(LIST_OF_NUMBERS) == std::string::npos)
    {
        currentNode->setNumberOfNodes(0);
        currentNode->setNodeType(CONSTANT);
    }
    else if (isValidArgument(value))
    {
        currentNode->setNumberOfNodes(0);
        currentNode->setNodeType(VARIABLE);

        tree.setArgumentValue(value, -1);
    }
    else
    {
        std::cout << "Error: Unknown operator: " << value << std::endl;
    }

    return start;
}

template <typename T>
bool PrefixExpressionParser<T>::isValidArgument(std::string value)
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

template <typename T>
std::map<std::string, int> PrefixExpressionParser<T>::createFunctionMap()
{
  std::map<std::string, int> m;

  m["sin"] = 1;
  m["cos"] = 1;
  m["+"] = 2;
  m["-"] = 2;
  m["*"] = 2;
  m["/"] = 2;

  return m;
}

template <>
std::map<std::string, int> PrefixExpressionParser<std::string>::createFunctionMap()
{
    std::map<std::string, int> m;

    m["+"] = 2;
    m["-"] = 2;
    m["*"] = 2;
    m["/"] = 2;

    return m;
}

template<typename T>
const std::map<std::string, int> PrefixExpressionParser<T>::funMap = createFunctionMap();

template <typename T>
bool PrefixExpressionParser<T>::isValidValue(std::string value)
{
    return true;
}

template <>
bool PrefixExpressionParser<int>::isValidValue(std::string value)
{
    return value.find_first_not_of(LIST_OF_NUMBERS) == std::string::npos;
}

template <>
bool PrefixExpressionParser<double>::isValidValue(std::string value)
{
    double ld = 0;
    return ((std::istringstream(value) >> ld >> std::ws).eof());
}

template <>
bool PrefixExpressionParser<std::string>::isValidValue(std::string value)
{
    if (value.length() < 3)
    {
        return false;
    }

    if (value.at(0) != '"' || value.at(value.length() - 1) != '"')
    {
        return false;
    }

    return true;
}

template <typename T>
std::string PrefixExpressionParser<T>::getDefaultValue()
{
    return "1";
}

template <>
std::string PrefixExpressionParser<std::string>::getDefaultValue()
{
    return "1";
}

#endif