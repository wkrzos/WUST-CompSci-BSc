#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <variant>

enum NodeType
{
    UNINITIALIZED,
    OPERATOR,
    VALUE,
    ARGUMENT
};

class Node
{
private:
    NodeType type;
    std::variant<int, double, std::string> value;
    Node* nodes;
    int numberOfNodes;

public:
    Node();
    Node(const Node& otherNode);
    ~Node();
    std::string toString() const;

    Node* getNodes() const;
    Node* getNode(int index) const;

    auto getValue() const -> decltype(value);

    int getNumberOfNodes() const;
    NodeType getNodeType() const;

    Node& operator=(const Node& newValue);

    void setNumberOfNodes(int numberOfNodes);
    void setNodeType(NodeType type);
    void setValue(std::variant<int, double, std::string> val);
    void setNode(int index, Node& node);
};

#endif
