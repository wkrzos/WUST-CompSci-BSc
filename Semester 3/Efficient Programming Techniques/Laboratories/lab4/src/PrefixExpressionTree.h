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

	void clearArguments();
	void setArgumentValue(std::string arg, int value);

	void setRoot(Node* newRoot); // New method to set the root
	Node* getRoot() /*const*/; // New method to access the root

private:
	Node* root;
	int comp(Node* currentNode);
	std::map<std::string, int> argsMap;
	std::vector<std::string> argsVector;
	void removeArgument(std::string arg);
	void setArgumentValueByIndex(int index, int value);
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
        result.removeArgument(currentNode->getValue());
    }

    if (parent != NULL)
    {
        parent->setNode(parent->getNumberOfNodes() - 1, *newNode);
    }
    else
    {
        result.root = newNode;
    }

    for (int i = 0; i < newValue.argsVector.size(); i++)
    {
        result.setArgumentValue(newValue.argsVector[i], -1);
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

    for (int i = 0; i < newValue.argsVector.size(); i++)
    {
        setArgumentValue(newValue.argsVector[i], -1);
    }

    return *this;
}


template <typename T>
int PrefixExpressionTree<T>::comp(std::string args)
{
    int size = 0;

    std::string* argsArray = splitStringIntoArray(args, &size);

    if (size != argsMap.size())
    {
        std::cout << "Error: Wrong number of arguments, expected: " << argsMap.size() << ", got: " << size << std::endl;

        delete[] argsArray;

        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        if (argsArray[i].find_first_not_of(LIST_OF_NUMBERS) == std::string::npos)
        {
            setArgumentValueByIndex(i, stringToNumber(argsArray[i]));
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
        std::map<std::string, int>::const_iterator argsIterator = argsMap.find(currentNode->getValue());

        if (argsIterator == argsMap.end())
        {
            std::cout << "Error: Unknown argument: " << currentNode->getValue() << std::endl;
            return -1;
        }

        return argsIterator->second;
    }

    return -1;
}

template <typename T>
void PrefixExpressionTree<T>::clearArguments()
{
    argsMap.clear();
    argsVector.clear();
}

template <typename T>
void PrefixExpressionTree<T>::setArgumentValue(std::string arg, int value)
{
    std::map<std::string, int>::const_iterator argsIterator = argsMap.find(arg);

    if (argsIterator == argsMap.end())
    {
        argsVector.push_back(arg);
    }

    argsMap[arg] = value;
}

template <typename T>
void PrefixExpressionTree<T>::removeArgument(std::string arg)
{
    std::map<std::string, int>::const_iterator argsIterator = argsMap.find(arg);

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
void PrefixExpressionTree<T>::setArgumentValueByIndex(int index, int value)
{
    if (index >= argsVector.size())
    {
        return;
    }

    argsMap[argsVector[index]] = value;
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
