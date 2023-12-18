#ifndef PREFIXEXPRESSIONTREE_H
#define PREFIXEXPRESSIONTREE_H

#include "Node.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <numeric>
#include "Constants.h" // Include Constants.h for error messages and type descriptions

template <typename T>
class PrefixExpressionTree
{
public:
    PrefixExpressionTree();
    PrefixExpressionTree(const PrefixExpressionTree& other);
    ~PrefixExpressionTree();

    PrefixExpressionTree<T>& operator=(const PrefixExpressionTree<T>& newValue);
    PrefixExpressionTree<T> operator+(const PrefixExpressionTree<T>& newValue) const;

    std::string toString() const;
    T comp(std::string args);
    std::string getArgumentsList() const;
    void printNodes() const;

    std::string getKnownType();
    static T getDefaultNoop();

    void clearArguments();

    void setRoot(Node* newRoot); // New method to set the root
    Node* getRoot(); // New method to access the root
    void setArgumentValue(std::string arg, T value);

private:
    Node* root;
    bool isValidValue(std::string value);
    static T stringToValue(std::string str);
    T comp(Node* currentNode);
    std::map<std::string, T> argsMap;
    std::vector<std::string> argsVector;
    void removeArgument(std::string arg);

    void setArgumentValueByIndex(int index, T value);
    std::string* splitStringIntoArray(const std::string& inputString, int* arraySize);

    static int stringToNumber(std::string str);
};

template <typename T>
PrefixExpressionTree<T>::PrefixExpressionTree() : root(NULL), argsMap(), argsVector()
{
}

template <typename T>
PrefixExpressionTree<T>::~PrefixExpressionTree()
{
    delete root;
}

template <typename T>
PrefixExpressionTree<T>::PrefixExpressionTree(const PrefixExpressionTree& other) : root(NULL)
{
    if (other.root != NULL)
    {
        root = new Node(*other.root);
    }

    argsMap = other.argsMap;
    argsVector = other.argsVector;
}

template <typename T>
T PrefixExpressionTree<T>::getDefaultNoop()
{
    return T();
}

template <>
int PrefixExpressionTree<int>::getDefaultNoop()
{
    return -401;
}

template <>
double PrefixExpressionTree<double>::getDefaultNoop()
{
    return -401;
}

template <>
std::string PrefixExpressionTree<std::string>::getDefaultNoop()
{
    return "-401";
}

template <typename T>
T PrefixExpressionTree<T>::stringToValue(std::string str)
{
    T i = 0;

    std::istringstream(str) >> i;
    return i;
}

template <>
std::string PrefixExpressionTree<std::string>::stringToValue(std::string str)
{
    return str.substr(1, str.length() - 2);
}

template <typename T>
PrefixExpressionTree<T> PrefixExpressionTree<T>::operator+(const PrefixExpressionTree<T>& newValue) const
{
    PrefixExpressionTree result = *this;

    if (result.root == NULL)
    {
        result.root = new Node(*newValue.root);
    }

    Node* currentNode = result.root;
    Node* parent = NULL;

    while (currentNode->getNodesCounter() > 0)
    {
        parent = currentNode;
        currentNode = currentNode->getNode(currentNode->getNodesCounter() - 1);
    }

    Node* newNode = new Node(*newValue.root);

    if (currentNode->getNodeType() == CONSTANT)
    {
        result.removeArgument(currentNode->getKey());
    }

    if (parent != NULL)
    {
        parent->setNode(parent->getNodesCounter() - 1, *newNode);
    }
    else
    {
        result.root = newNode;
    }

    for (int i = 0; i < newValue.argsVector.size(); i++)
    {
        result.setArgumentValue(newValue.argsVector[i], getDefaultNoop());
    }

    // Merge argsMap and argsVector
    for (const auto& arg : newValue.argsMap)
    {
        // How to handle conflicts here?
        result.argsMap[arg.first] = arg.second;
    }

    // Update argsVector
    for (const auto& arg : newValue.argsVector)
    {
        if (std::find(result.argsVector.begin(), result.argsVector.end(), arg) == result.argsVector.end())
        {
            result.argsVector.push_back(arg);
        }
    }

    return result;
}

template <typename T>
PrefixExpressionTree<T>& PrefixExpressionTree<T>::operator=(const PrefixExpressionTree<T>& newValue)
{
    if (this == &newValue)
    {
        return *this;
    }

    if (root != NULL)
    {
        delete root;
    }

    if (newValue.root != NULL)
    {
        root = new Node(*newValue.root);
    }

    for (int i = 0; i < newValue.argsVector.size(); i++)
    {
        setArgumentValue(newValue.argsVector[i], getDefaultNoop());
    }

    return *this;
}

template <typename T>
T PrefixExpressionTree<T>::comp(std::string args)
{
    int size = 0;

    std::string* argsArray = splitStringIntoArray(args, &size);

    if (size != argsMap.size())
    {
        std::cout << ERROR_WRONG_NUM_ARGS << std::endl;

        delete[] argsArray;

        return getDefaultNoop();
    }

    for (int i = 0; i < size; i++)
    {
        if (isValidValue(argsArray[i]))
        {
            setArgumentValueByIndex(i, stringToValue(argsArray[i]));
        }
        else
        {
            std::cout << ERROR_INVALID_ARG << std::endl;

            delete[] argsArray;

            return getDefaultNoop();
        }
    }

    if (root == NULL)
    {
        std::cout << ERROR_NO_FORMULA << std::endl;

        delete[] argsArray;

        return getDefaultNoop();
    }

    T result = comp(root);

    delete[] argsArray;

    return result;
}

template <typename T>
std::string PrefixExpressionTree<T>::getArgumentsList() const
{
    if (argsVector.empty())
    {
        return "";
    }

    std::string result;
    result.reserve(std::accumulate(argsVector.begin(), argsVector.end(), 0,
        [](size_t sum, const std::string& str) { return sum + str.length() + 1; }));

    for (const auto& arg : argsVector)
    {
        result += arg + " ";
    }

    result.pop_back(); // Remove the last space
    return result;
}

template <typename T>
void PrefixExpressionTree<T>::printNodes() const
{
    if (root != NULL)
    {
        for (int i = 0; i < root->getNodesCounter(); i++)
        {
            std::cout << root->getNode(i)->toString() << std::endl;
        }
    }
}

template <typename T>
T PrefixExpressionTree<T>::comp(Node* currentNode)
{
    if (currentNode->getNodeType() == CONSTANT)
    {
        return stringToValue(currentNode->getKey());
    }
    else if (currentNode->getNodeType() == OPERATION)
    {
        if (currentNode->getKey() == "+")
        {
            return comp(currentNode->getNode(0)) + comp(currentNode->getNode(1));
        }
        else if (currentNode->getKey() == "-")
        {
            return comp(currentNode->getNode(0)) - comp(currentNode->getNode(1));
        }
        else if (currentNode->getKey() == "*")
        {
            return comp(currentNode->getNode(0)) * comp(currentNode->getNode(1));
        }
        else if (currentNode->getKey() == "/")
        {
            T secondNodeValue = comp(currentNode->getNode(1));

            if (secondNodeValue == 0)
            {
                throw std::invalid_argument(ERROR_DIVISION_BY_ZERO);
            }

            return comp(currentNode->getNode(0)) / secondNodeValue;
        }
        else if (currentNode->getKey() == "sin")
        {
            return static_cast<int>(std::sin(comp(currentNode->getNode(0))));
        }
        else if (currentNode->getKey() == "cos")
        {
            return static_cast<int>(std::cos(comp(currentNode->getNode(0))));
        }
    }
    else if (currentNode->getNodeType() == VARIABLE)
    {
        typename std::map<std::string, T>::const_iterator argsIterator = argsMap.find(currentNode->getKey());

        if (argsIterator == argsMap.end())
        {
            std::cout << ERROR_UNKNOWN_ARG << std::endl;
            return getDefaultNoop();
        }

        return argsIterator->second;
    }

    return getDefaultNoop();
}

template <>
std::string PrefixExpressionTree<std::string>::comp(Node* currentNode)
{
    if (currentNode->getNodeType() == CONSTANT)
    {
        return stringToValue(currentNode->getKey());
    }
    else if (currentNode->getNodeType() == OPERATION)
    {
        if (currentNode->getKey() == "+")
        {
            return comp(currentNode->getNode(0)) + comp(currentNode->getNode(1));
        }
        else if (currentNode->getKey() == "-")
        {
            std::string firstNodeValue = comp(currentNode->getNode(0));
            int pos = firstNodeValue.rfind(comp(currentNode->getNode(1)));
            if (pos != std::string::npos)
            {
                firstNodeValue.erase(pos, comp(currentNode->getNode(0)).length());
            }
            return firstNodeValue;
        }
        else if (currentNode->getKey() == "*")
        {
            std::string secondValue = comp(currentNode->getNode(1));
            std::string firstValue = comp(currentNode->getNode(0));

            if (secondValue.length() < 1)
            {
                return firstValue;
            }

            std::string newString = "";
            std::string stringToCopy = secondValue.substr(1);

            for (int i = 0; i < firstValue.length(); i++)
            {
                newString += firstValue[i];
                if (firstValue[i] == secondValue[0])
                {
                    newString += stringToCopy;
                }
            }

            return newString;
        }
        else if (currentNode->getKey() == "/")
        {
            std::string secondValue = comp(currentNode->getNode(1));
            std::string firstValue = comp(currentNode->getNode(0));

            if (secondValue.length() < 1)
            {
                return firstValue;
            }

            std::string newString = "";

            for (int i = 0; i < firstValue.length(); i++)
            {
                newString += firstValue[i];

                if (firstValue.substr(i, secondValue.length()) == secondValue)
                {
                    i += secondValue.length() - 1;
                }
            }

            return newString;
        }
    }
    else if (currentNode->getNodeType() == VARIABLE)
    {
        std::map<std::string, std::string>::const_iterator argsIterator = argsMap.find(currentNode->getKey());

        if (argsIterator == argsMap.end())
        {
            std::cout << ERROR_UNKNOWN_ARG << std::endl;
            return getDefaultNoop();
        }

        return argsIterator->second;
    }

    return getDefaultNoop();
}

template <typename T>
void PrefixExpressionTree<T>::clearArguments()
{
    argsMap.clear();
    argsVector.clear();
}

template <typename T>
void PrefixExpressionTree<T>::removeArgument(std::string arg)
{
    typename std::map<std::string, T>::const_iterator argsIterator = argsMap.find(arg);

    if (argsIterator != argsMap.end())
    {
        argsMap.erase(arg);
    }

    for (int i = 0; i < argsVector.size(); i++)
    {
        if (argsVector[i] == arg)
        {
            argsVector.erase(argsVector.begin() + i);
            break;
        }
    }
}

template <typename T>
void PrefixExpressionTree<T>::setArgumentValue(std::string arg, T value)
{
    typename std::map<std::string, T>::const_iterator argsIterator = argsMap.find(arg);

    if (argsIterator == argsMap.end())
    {
        argsVector.push_back(arg);
    }

    argsMap[arg] = value;
}

template <typename T>
std::string PrefixExpressionTree<T>::toString() const
{
    return root->toString();
}

template <typename T>
int PrefixExpressionTree<T>::stringToNumber(std::string str)
{
    int i = 0;

    std::istringstream(str) >> i;

    return i;
}

template <typename T>
void PrefixExpressionTree<T>::setRoot(Node* newRoot)
{
    root = newRoot;
}

template <typename T>
Node* PrefixExpressionTree<T>::getRoot()
{
    return root;
}

template <typename T>
std::string PrefixExpressionTree<T>::getKnownType()
{
    return "UNSPECIFIED";
}

template <>
std::string PrefixExpressionTree<int>::getKnownType()
{
    return "INT";
}

template <>
std::string PrefixExpressionTree<double>::getKnownType()
{
    return "DOUBLE";
}

template <>
std::string PrefixExpressionTree<std::string>::getKnownType()
{
    return "STRING";
}

template <typename T>
bool PrefixExpressionTree<T>::isValidValue(std::string value)
{
    return true;
}

template <>
bool PrefixExpressionTree<int>::isValidValue(std::string value)
{
    return value.find_first_not_of("0123456789") == std::string::npos;
}

template <>
bool PrefixExpressionTree<double>::isValidValue(std::string value)
{
    double ld = 0;
    return ((std::istringstream(value) >> ld >> std::ws).eof());
}

template <>
bool PrefixExpressionTree<std::string>::isValidValue(std::string value)
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
void PrefixExpressionTree<T>::setArgumentValueByIndex(int index, T value)
{
    if (index >= argsVector.size())
    {
        return;
    }

    argsMap[argsVector[index]] = value;
}

// Splits a string into an array of words. Returns the array and updates the size.
template <typename T>
std::string* PrefixExpressionTree<T>::splitStringIntoArray(const std::string& inputString, int* arraySize)
{
    std::string* wordArray = new std::string[inputString.length()]; // Allocate maximum possible size
    int wordCount = 0;
    std::string currentWord;

    for (char ch : inputString)
    {
        if (ch == ' ')
        {
            if (!currentWord.empty())
            {
                wordArray[wordCount++] = currentWord;
                currentWord.clear();
            }
        }
        else
        {
            currentWord += ch;
        }
    }

    if (!currentWord.empty())
    {
        wordArray[wordCount++] = currentWord;
    }

    *arraySize = wordCount;
    return wordArray;
}

#endif
