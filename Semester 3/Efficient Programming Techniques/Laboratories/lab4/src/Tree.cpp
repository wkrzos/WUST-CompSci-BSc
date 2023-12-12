#include "Tree.h"
#include "stringUtils.h"
#include <iostream>
#include <sstream>
#include <valarray>

int Tree::stringToNumber(std::string str)
{
    int i = 0;

    std::istringstream(str) >> i;

    return i;
}


Tree::Tree() : root(NULL), argsMap(), argsVector()
{
}

Tree::~Tree()
{
    if (root != NULL)
    {
        delete root;
    }
}

Tree::Tree(const Tree& other) : root(NULL)
{
    if (other.root != NULL)
    {
        root = new Node(*other.root);
    }

    argsMap = other.argsMap;
    argsVector = other.argsVector;
}

Tree& Tree::operator=(const Tree& newValue)
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

std::string Tree::toString() const
{
    if (root == NULL)
    {
        return "";
    }

    return root->toString();
}

int Tree::comp(std::string args)
{
    int size = 0;

    std::string* argsArray = splitStringByWhitespace(args, &size);

    if (size != argsMap.size())
    {
        errorStream << "Error: Wrong number of arguments, expected: " << argsMap.size() << ", got: " << size << std::endl;

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
            errorStream << "Error: Invalid argument: " << argsArray[i] << std::endl;

            delete[] argsArray;

            return -1;
        }
    }

    if (root == NULL)
    {
        errorStream << "Error: No formula" << std::endl;

        delete[] argsArray;

        return -1;
    }

    int result = comp(root);

    delete[] argsArray;

    return result;
}

std::string Tree::getArgumentsList() const
{
    std::string result = "";

    for (int i = 0; i < argsVector.size(); i++)
    {
        result += argsVector[i] + " ";
    }

    if (result.length() > 0)
    {
        result = result.substr(0, result.length() - 1);
    }

    return result;
}

Tree Tree::operator+(const Tree& newValue) const
{
    Tree result = *this;

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

    return result;
}

std::string Tree::getErrorAndClear()
{
    std::string error = this->errorStream.str();

    errorStream.clear();

    return error;
}

void Tree::printNodes() const
{
    if (root != NULL)
    {
        for (int i = 0; i < root->getNumberOfNodes(); i++)
        {
            std::cout << root->getNode(i)->toString() << std::endl;
        }
    }
}

int Tree::comp(Node* currentNode)
{
    if (currentNode->getNodeType() == VALUE)
    {
        int i = 0;

        std::istringstream(currentNode->getValue()) >> i;

        return i;
    }
    else if (currentNode->getNodeType() == OPERATOR)
    {
        if (currentNode->getValue() == "+")
        {
            return comp(currentNode->getNode(0)) + comp(currentNode->getNode(1));
        }
        else if (currentNode->getValue() == "-")
        {
            return comp(currentNode->getNode(0)) - comp(currentNode->getNode(1));
        }
        else if (currentNode->getValue() == "*")
        {
            return comp(currentNode->getNode(0)) * comp(currentNode->getNode(1));
        }
        else if (currentNode->getValue() == "#")
        {
            return comp(currentNode->getNode(0)) + comp(currentNode->getNode(1));
        }
        else if (currentNode->getValue() == "/")
        {
            int secondNodeValue = comp(currentNode->getNode(1));

            if (secondNodeValue == 0)
            {
                throw std::invalid_argument("Division by zero");
            }

            return comp(currentNode->getNode(0)) / secondNodeValue;
        }
        else if (currentNode->getValue() == "sin")
        {
            return static_cast<int>(std::sin(comp(currentNode->getNode(0))));
        }
        else if (currentNode->getValue() == "cos")
        {
            return static_cast<int>(std::cos(comp(currentNode->getNode(0))));
        }
    }
    else if (currentNode->getNodeType() == ARGUMENT)
    {
        std::map<std::string, int>::const_iterator argsIterator = argsMap.find(currentNode->getValue());

        if (argsIterator == argsMap.end())
        {
            errorStream << "Error: Unknown argument: " << currentNode->getValue() << std::endl;
            return -1;
        }

        return argsIterator->second;
    }

    return -1;
}

void Tree::clearArguments()
{
    argsMap.clear();
    argsVector.clear();
}

void Tree::setArgumentValue(std::string arg, int value)
{
    std::map<std::string, int>::const_iterator argsIterator = argsMap.find(arg);

    if (argsIterator == argsMap.end())
    {
        argsVector.push_back(arg);
    }

    argsMap[arg] = value;
}

void Tree::removeArgument(std::string arg)
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

void Tree::setArgumentValueByIndex(int index, int value)
{
    if (index >= argsVector.size())
    {
        return;
    }

    argsMap[argsVector[index]] = value;
}

void Tree::setRoot(Node* newRoot) {
    root = newRoot;
} 

Node* Tree::getRoot() {
    return root;
}

std::stringstream& Tree::getErrorStream()
{
    return errorStream;
}

void Tree::setErrorStream(const std::stringstream& stream)
{
    errorStream.str(stream.str());
}