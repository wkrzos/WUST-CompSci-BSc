#pragma once
#ifndef SINNODE_H
#define SINNODE_H

#include "Node.h"
#include <cmath>
#include <iostream>

class SinNode : public Node {
private:
    Node* operand;

public:
    SinNode(Node* op);

    ~SinNode() override;

    double evaluate() const override;

    void print() const override;

    void printTree(int indent) const override;

    void printPrefix() const override;

    void printVariables(std::set<std::string>& variableSet) const override;

    size_t countVariables() const override;

    double evaluateWithValues(const std::map<std::string, double>& values) const override;
};

#endif // SINNODE_H
