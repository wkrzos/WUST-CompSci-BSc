#include "Node.h"

Node::Node() : numberOfNodes(0), nodes(nullptr), type(UNINITIALIZED)
{
}

Node::Node(const Node& otherNode) : type(otherNode.type), value(otherNode.value), numberOfNodes(otherNode.numberOfNodes)
{
    nodes = new Node[numberOfNodes];

    for (int i = 0; i < numberOfNodes; i++)
    {
        nodes[i] = otherNode.nodes[i];
    }
}

Node::~Node()
{
    if (nodes != nullptr)
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

    if (nodes != nullptr)
    {
        delete[] nodes;
    }

    type = newValue.type;
    value = newValue.value;
    numberOfNodes = newValue.numberOfNodes;

    nodes = new Node[numberOfNodes];

    for (int i = 0; i < numberOfNodes; i++)
    {
        nodes[i] = newValue.nodes[i];
    }

    return *this;
}

std::string Node::toString() const
{
    return std::visit([](const auto& arg) -> std::string {
        if constexpr (std::is_same_v<decltype(arg), int>)
        {
            return std::to_string(arg);
        }
        else if constexpr (std::is_same_v<decltype(arg), double>)
        {
            return std::to_string(arg);
        }
        else if constexpr (std::is_same_v<decltype(arg), std::string>)
        {
            return arg;
        }
        else
        {
            static_assert(false, "Unsupported variant type");
        }
        },
        value);
}

Node* Node::getNodes() const
{
    return nodes;
}

Node* Node::getNode(int index) const
{
    if (index >= 0 && index < numberOfNodes)
    {
        return &nodes[index];
    }
    return nullptr;
}

auto Node::getValue() const -> decltype(value)
{
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
    if (nodes != nullptr)
    {
        delete[] nodes;
    }

    this->numberOfNodes = numberOfNodes;
    nodes = new Node[numberOfNodes];
}

void Node::setNodeType(NodeType type)
{
    this->type = type;
}

void Node::setValue(std::variant<int, double, std::string> val)
{
    value = val;
}

void Node::setNode(int index, Node& node)
{
    if (index >= 0 && index < numberOfNodes)
    {
        nodes[index] = node;
    }
}
