#include "Node.h"
#include <string>

Node::Node() : numberOfNodes(0), nodes(new Node[0]), type(NO_TYPE)
{
}

Node::Node(const Node& otherNode) : type(otherNode.type), key(otherNode.key), numberOfNodes(otherNode.numberOfNodes)
{
    this->nodes = new Node[numberOfNodes];

    for (int i = 0; i < numberOfNodes; i++)
    {
        this->nodes[i] = otherNode.nodes[i];
    }
}

Node::~Node()
{
    if (nodes != NULL)
    {
        delete[] nodes;
    }
}

Node& Node::operator=(const Node& newValue)
{
    if (this == &newValue)
    {
        return *this;
    }

    if (nodes != NULL)
    {
        delete[] nodes;
    }

    this->type = newValue.type;
    this->key = newValue.key;
    this->numberOfNodes = newValue.numberOfNodes;

    this->nodes = new Node[numberOfNodes];

    for (int i = 0; i < numberOfNodes; i++)
    {
        this->nodes[i] = newValue.nodes[i];
    }

    return *this;
}

std::string Node::toString() const
{
    std::string result = key;

    for (int i = 0; i < numberOfNodes; i++)
    {
        result += " " + nodes[i].toString();
    }

    return result;
}

Node* Node::getNodes() const
{
    return nodes;
}

Node* Node::getNode(int index) const
{
    return &nodes[index];
}

std::string Node::getValue() const
{
    return key;
}

int Node::getNumberOfNodes() const
{
    return numberOfNodes;
}

TYPE Node::getNodeType() const
{
    return type;
}

void Node::setNumberOfNodes(int numberOfNodes)
{
    this->numberOfNodes = numberOfNodes;
    this->nodes = new Node[numberOfNodes];
}

void Node::setNodeType(TYPE type)
{
    this->type = type;
}

void Node::setValue(std::string value)
{
    this->key = value;
}

void Node::setNode(int index, Node& node)
{
    if (index >= numberOfNodes)
    {
        return;
    }

    this->nodes[index] = node;
}
