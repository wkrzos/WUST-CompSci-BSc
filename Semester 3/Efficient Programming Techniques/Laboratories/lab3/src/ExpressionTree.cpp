#include "ExpressionTree.h"

ExpressionTree::ExpressionTree() : tree(nullptr) {}

ExpressionTree ExpressionTree::operator+(const Node& other) {
    ExpressionTree newTree;
    Node* leaf = traverseLeft(dynamic_cast<OperatorNode*>(tree));
    if (leaf != nullptr) {
        *leaf = other;
    }
    return newTree;
}

ExpressionTree& ExpressionTree::operator=(const OperatorNode& other) {
    if (this != &other) {
        delete tree;
        tree = new OperatorNode(other);
    }
    return *this;
}

Node* ExpressionTree::traverseLeft(OperatorNode* root) {
    if (root == nullptr) {
        std::cerr << "Error: Root is null." << std::endl;
        return nullptr;
    }

    if (typeid(root->getLeft()) == typeid(OperatorNode)) {
        return traverseLeft(dynamic_cast<OperatorNode*>(root->getLeft()));
    }
    else if (typeid(root->getLeft()) == typeid(ConstantNode) || typeid(root->getLeft()) == typeid(VariableNode)) {
        return root->getLeft();
    }
    else {
        std::cerr << "Error: Unexpected node type encountered on the left side." << std::endl;
        return nullptr;
    }
}

ExpressionTree::~ExpressionTree() {
    delete tree;
}
