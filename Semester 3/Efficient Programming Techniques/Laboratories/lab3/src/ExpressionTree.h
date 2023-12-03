#pragma once
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include "Node/Node.h"
#include "Node/OperatorNode.h"
#include "Node/ConstantNode.h"
#include "Node/VariableNode.h"
#include <iostream>

class ExpressionTree {
private:
    Node* tree;

public:
    ExpressionTree();

    // Operator Overloading for +
    ExpressionTree operator+(const Node& other);

    // Operator Overloading for =
    ExpressionTree& operator=(const OperatorNode& other);

    Node* traverseLeft(OperatorNode* root);

    // Add any necessary member functions or declarations

    ~ExpressionTree();
};

#endif // EXPRESSIONTREE_H
