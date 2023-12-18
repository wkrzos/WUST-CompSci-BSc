#include "Node.h"
#include <string>

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
