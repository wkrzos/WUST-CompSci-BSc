#ifndef PREFIXEXPRESSIONTREE_H
#define PREFIXEXPRESSIONTREE_H

#include "Node.h"
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "PrefixExpressionTree.h"
#include "stringUtils.h"
#include "stringUtils.h"
#include <iostream>
#include <sstream>
#include <valarray>
#include <numeric>

const std::string LIST_OF_NUMBERS = "0123456789";

template <typename T>
class PrefixExpressionTree
{
public:
	PrefixExpressionTree();
	PrefixExpressionTree(const PrefixExpressionTree& other);
	~PrefixExpressionTree();

	PrefixExpressionTree& operator=(const PrefixExpressionTree& newValue);
	PrefixExpressionTree operator+(const PrefixExpressionTree& newValue) const;



	std::string toString() const;
	int comp(std::string args);
	std::string getArgumentsList() const;
	void printNodes() const;

	void clearVariables();
	void setArgumentValue(std::string arg, int value);

	void setRoot(Node* newRoot); // New method to set the root
	Node* getRoot() /*const*/; // New method to access the root

private:
	Node* root;
	int comp(Node* currentNode);
	std::map<std::string, int> variableMap;
	std::vector<std::string> variableVector;
	void removeVariable(std::string var);
	void setVariableValueByIndex(int index, int value);
	static int stringToNumber(std::string str);
};

template <typename T>
PrefixExpressionTree<T>::PrefixExpressionTree() : root(NULL), variableMap(), variableVector()
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

    variableMap = other.variableMap;
    variableVector = other.variableVector;
}

template <typename T>
PrefixExpressionTree<T> PrefixExpressionTree<T>::operator+(const PrefixExpressionTree& newValue) const
{
    PrefixExpressionTree result = *this;

    if (result.root == NULL)
    {
        result.root = new Node(*newValue.root);
    }

    Node* currentNode = result.root;
    Node* parent = NULL;

    while (currentNode->getNumberOfNodes() > 0)
    {
        parent = currentNode;
        currentNode = currentNode->getNode(currentNode->getNumberOfNodes() - 1);
    }

    Node* newNode = new Node(*newValue.root);

    if (currentNode->getNodeType() == ARGUMENT)
    {
        result.removeVariable(currentNode->getValue());
    }

    if (parent != NULL)
    {
        parent->setNode(parent->getNumberOfNodes() - 1, *newNode);
    }
    else
    {
        result.root = newNode;
    }

    for (int i = 0; i < newValue.variableVector.size(); i++)
    {
        result.setArgumentValue(newValue.variableVector[i], -1);
    }

    // Merge argsMap and argsVector
    for (const auto& arg : newValue.variableMap)
    {
        // How to handle conflicts here?
        result.variableMap[arg.first] = arg.second;
    }

    // Update argsVector
    for (const auto& arg : newValue.variableVector)
    {
        if (std::find(result.variableVector.begin(), result.variableVector.end(), arg) == result.variableVector.end())
        {
            result.variableVector.push_back(arg);
        }
    }

    return result;
}

template <typename T>
PrefixExpressionTree<T>& PrefixExpressionTree<T>::operator=(const PrefixExpressionTree& newValue)
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

    for (int i = 0; i < newValue.variableVector.size(); i++)
    {
        setArgumentValue(newValue.variableVector[i], -1);
    }

    return *this;
}


template <typename T>
int PrefixExpressionTree<T>::comp(std::string args)
{
    int size = 0;

    std::string* argsArray = splitStringIntoArray(args, &size);

    if (size != variableMap.size())
    {
        std::cout << "Error: Wrong number of arguments, expected: " << variableMap.size() << ", got: " << size << std::endl;

        delete[] argsArray;

        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        if (argsArray[i].find_first_not_of(LIST_OF_NUMBERS) == std::string::npos)
        {
            setVariableValueByIndex(i, stringToNumber(argsArray[i]));
        }
        else
        {
            std::cout << "Error: Invalid argument: " << argsArray[i] << std::endl;

            delete[] argsArray;

            return -1;
        }
    }

    if (root == NULL)
    {
        std::cout << "Error: No formula" << std::endl;

        delete[] argsArray;

        return -1;
    }

    int result = comp(root);

    delete[] argsArray;

    return result;
}

//done
template <typename T>
std::string PrefixExpressionTree<T>::getArgumentsList() const
{
    if (variableVector.empty())
    {
        return "";
    }

    std::string result;
    result.reserve(std::accumulate(variableVector.begin(), variableVector.end(), 0,
        [](size_t sum, const std::string& str) { return sum + str.length() + 1; }));

    for (const auto& arg : variableVector)
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
        for (int i = 0; i < root->getNumberOfNodes(); i++)
        {
            std::cout << root->getNode(i)->toString() << std::endl;
        }
    }
}

template <typename T>
int PrefixExpressionTree<T>::comp(Node* currentNode)
{
    if (currentNode->getNodeType() == VALUE)
    {
        int i = 0;

        std::istringstream(currentNode->getValue()) >> i;

        return i;
    }
    else if (currentNode->getNodeType() == OPERATOR)
    {

        std::string opr = currentNode->getValue();

        if (opr == "+")
        {
            return comp(currentNode->getNode(0)) + comp(currentNode->getNode(1));
        }
        else if (opr == "-")
        {
            return comp(currentNode->getNode(0)) - comp(currentNode->getNode(1));
        }
        else if (opr == "*")
        {
            return comp(currentNode->getNode(0)) * comp(currentNode->getNode(1));
        }
        else if (opr == "/")
        {
            int secondNodeValue = comp(currentNode->getNode(1));

            if (secondNodeValue == 0)
            {
                throw std::invalid_argument("Division by zero");
            }

            return comp(currentNode->getNode(0)) / secondNodeValue;
        }
        else if (opr == "sin")
        {
            return static_cast<int>(std::sin(comp(currentNode->getNode(0))));
        }
        else if (opr == "cos")
        {
            return static_cast<int>(std::cos(comp(currentNode->getNode(0))));
        }
    }
    else if (currentNode->getNodeType() == ARGUMENT)
    {
        std::map<std::string, int>::const_iterator argsIterator = variableMap.find(currentNode->getValue());

        if (argsIterator == variableMap.end())
        {
            std::cout << "Error: Unknown argument: " << currentNode->getValue() << std::endl;
            return -1;
        }

        return argsIterator->second;
    }

    return -1;
}

template <typename T>
void PrefixExpressionTree<T>::clearVariables()
{
    variableMap.clear();
    variableVector.clear();
}

template <typename T>
void PrefixExpressionTree<T>::setArgumentValue(std::string arg, int value)
{
    std::map<std::string, int>::const_iterator argsIterator = variableMap.find(arg);

    if (argsIterator == variableMap.end())
    {
        variableVector.push_back(arg);
    }

    variableMap[arg] = value;
}

template <typename T>
void PrefixExpressionTree<T>::removeVariable(std::string arg)
{
    std::map<std::string, int>::const_iterator argsIterator = variableMap.find(arg);

    if (argsIterator != variableMap.end())
    {
        variableMap.erase(arg);
    }

    for (int i = 0; i < variableVector.size(); i++)
    {
        if (variableVector[i] == arg)
        {
            variableVector.erase(variableVector.begin() + i);
            break;
        }
    }
}

template <typename T>
void PrefixExpressionTree<T>::setVariableValueByIndex(int index, int value)
{
    if (index >= variableVector.size())
    {
        return;
    }

    variableMap[variableVector[index]] = value;
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
void PrefixExpressionTree<T>::setRoot(Node* newRoot) {
    root = newRoot;
}

template <typename T>
Node* PrefixExpressionTree<T>::getRoot() {
    return root;
}

#endif
