#pragma once
#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include "Node.h"
#include <cmath>
#include <iostream>

class OperatorNode : public Node {
private:
    char op;
    Node* left;
    Node* right;

public:
    OperatorNode(char operation, Node* l, Node* r);

    ~OperatorNode() override;

    double evaluate() const override;

    size_t countVariables() const override;

    double evaluateWithValues(const std::map<std::string, double>& values) const override;

    OperatorNode* traverseLeftToOperatorNode(OperatorNode* root);

    void print() const override;

    void printTree(int indent) const override;

    void printPrefix() const override;

    void printVariables(std::set<std::string>& variableSet) const override;

    void setLeft(Node* Left);

    void setRight(Node* Right);

    Node* getLeft();

    Node* getRight();
};

#endif // OPERATORNODE_H
