#include "Node.h"
#include <iostream>
#include <sstream>
#include <string>

Node::Node() : numberOfNodes(0), nodes(new Node[0]), type(UNINITIALIZED)
{
}

Node::Node(const Node &otherNode) : type(otherNode.type), value(otherNode.value), numberOfNodes(otherNode.numberOfNodes)
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
    this->value = newValue.value;
    this->numberOfNodes = newValue.numberOfNodes;

    this->nodes = new Node[numberOfNodes];

    for (int i = 0; i < numberOfNodes; i++)
    {
        this->nodes[i] = newValue.nodes[i];
    }

    return *this;
}

std::string toString() const {
    return std::visit([](auto&& arg) -> std::string {
        return std::to_string(arg);
        }, value);
}

Node *Node::getNodes() const
{
  return nodes;
}

Node *Node::getNode(int index) const
{
  return &nodes[index];
}

auto Node::getValue() const -> decltype(value) {
    return value;
}

int Node::getNumberOfNodes() const
{
  return numberOfNodes;
}

NodeType Node::getNodeType() const
{
  return type;
}

void Node::setNumberOfNodes(int numberOfNodes)
{
  this->numberOfNodes = numberOfNodes;
  this->nodes = new Node[numberOfNodes];
}

void Node::setNodeType(NodeType type)
{
  this->type = type;
}

template<typename T>
void setValue(T val) {
    value = val;
}

void Node::setNode(int index, Node &node)
{
  if (index >= numberOfNodes)
  {
    return;
  }

  this->nodes[index] = node;
}
