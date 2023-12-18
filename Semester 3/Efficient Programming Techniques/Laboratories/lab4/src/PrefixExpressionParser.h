#ifndef PARSER_H
#define PARSER_H

#include "PrefixExpressionTree.h"
#include "PrefixExpressionParser.h"
#include "Constants.h" // Include Constants.h for error messages

template<typename T>
class PrefixExpressionParser
{
public:
    void parseFormula(PrefixExpressionTree<T>& peTree, std::string formula);

private:
    int parseNodes(Node* currentNode, std::string formula, int start, bool* wasError, PrefixExpressionTree<T>& tree);
    static const std::map<std::string, int> funMap;
    static std::string getDefaultValue();
    static std::map<std::string, int> createFunctionMap();

    bool isCorrectConstant(std::string value);
    bool isValidVariable(std::string value);
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
    peTree.clearVariables(); // Assume this method resets variables and v_variables

    int start = parseNodes(root, formula, 0, &wasError, peTree);

    if (formula.length() > start)
    {
        std::cout << ERROR_WRONG_NUM_ARGS << std::endl;
        wasError = true;
    }

    if (wasError)
    {
        std::cout << FORMULA_CORRECTED << std::endl;
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

    currentNode->setKey(value);

    if (numberOfArgsIterator != funMap.end())
    {
        currentNode->setNodesCounter(numberOfArgsIterator->second);
        currentNode->setNodeType(OPERATION);

        for (int i = 0; i < currentNode->getNodesCounter(); i++)
        {
            if (formula.length() <= start)
            {
                std::cout << ERROR_NOT_ENOUGH_ARGS << std::endl;
                currentNode->getNode(i)->setNodesCounter(0);
                currentNode->getNode(i)->setNodeType(CONSTANT);
                currentNode->getNode(i)->setKey("1");

                *wasError = true;
            }
            else
            {
                start = parseNodes(currentNode->getNode(i), formula, start, wasError, tree);
            }
        }
    }
    else if (value.find_first_not_of("0123456789") == std::string::npos)
    {
        currentNode->setNodesCounter(0);
        currentNode->setNodeType(CONSTANT);
    }
    else if (isValidVariable(value))
    {
        currentNode->setNodesCounter(0);
        currentNode->setNodeType(VARIABLE);

        tree.setVariable(value, tree.getDefaultNodeKey());
    }
    else
    {
        std::cout << ERROR_UNKNOWN_OPERATION << std::endl;
    }

    return start;
}

template <typename T>
bool PrefixExpressionParser<T>::isValidVariable(std::string value)
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
            std::cout << ERROR_INVALID_CHARACTER << std::endl;
        }
    }

    return hasLetter;
}

template <typename T>
std::map<std::string, int> PrefixExpressionParser<T>::createFunctionMap()
{
    return {
        {"+", 2},
        {"-", 2},
        {"*", 2},
        {"/", 2},
        {"Sin", 1},
        {"Cos", 1},
    };
}

template <>
std::map<std::string, int> PrefixExpressionParser<std::string>::createFunctionMap()
{
    return {
        {"+", 2},
        {"-", 2},
        {"*", 2},
        {"/", 2}
    };
}

template<typename T>
const std::map<std::string, int> PrefixExpressionParser<T>::funMap = createFunctionMap();

template <typename T>
bool PrefixExpressionParser<T>::isCorrectConstant(std::string value)
{
    return true;
}

template <>
bool PrefixExpressionParser<int>::isCorrectConstant(std::string value)
{
    return value.find_first_not_of("0123456789") == std::string::npos;
}

template <>
bool PrefixExpressionParser<double>::isCorrectConstant(std::string value)
{
    double ld = 0;
    return ((std::istringstream(value) >> ld >> std::ws).eof());
}

template <>
bool PrefixExpressionParser<std::string>::isCorrectConstant(std::string value)
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
