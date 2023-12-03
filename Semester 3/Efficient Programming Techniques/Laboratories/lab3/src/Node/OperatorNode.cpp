#include "OperatorNode.h"

OperatorNode::OperatorNode(char operation, Node* l, Node* r) : op(operation), left(l), right(r) {}

OperatorNode::~OperatorNode() {
    delete left;
    delete right;
}

double OperatorNode::evaluate() const {
    switch (op) {
    case '+':
        return left->evaluate() + right->evaluate();
    case '-':
        return left->evaluate() - right->evaluate();
    case '*':
        return left->evaluate() * right->evaluate();
    case '/':
        return left->evaluate() / right->evaluate();
    case 's':
        return std::sin(right->evaluate());
    case 'c':
        return std::cos(right->evaluate());
    default:
        std::cerr << "Error: Unknown operator " << op << std::endl;
        return 0.0;
    }
}

size_t OperatorNode::countVariables() const {
    return left->countVariables() + right->countVariables();
}

double OperatorNode::evaluateWithValues(const std::map<std::string, double>& values) const {
    double leftValue = left->evaluateWithValues(values);
    double rightValue = right->evaluateWithValues(values);

    switch (op) {
    case '+':
        return leftValue + rightValue;
    case '-':
        return leftValue - rightValue;
    case '*':
        return leftValue * rightValue;
    case '/':
        return leftValue / rightValue;
    case 's':
        return std::sin(rightValue);
    case 'c':
        return std::cos(rightValue);
    default:
        std::cerr << "Error: Unknown operator " << op << std::endl;
        return 0.0;
    }
}

OperatorNode* OperatorNode::traverseLeftToOperatorNode(OperatorNode* root) {
    if (typeid(root->left) == typeid(OperatorNode)) {
        return dynamic_cast<OperatorNode*>(root->left);
    }
    else if (typeid(root->left) == typeid(ConstantNode) || typeid(root->left) == typeid(VariableNode)) {
        std::cerr << "Error: Leaf node of type ConstantNode or VariableNode encountered while traversing left." << std::endl;
        return nullptr;
    }
    else if (typeid(root->left) == typeid(OperatorNode)) {
        return traverseLeftToOperatorNode(dynamic_cast<OperatorNode*>(root->left));
    }
    else {
        std::cerr << "Error: Unexpected node type encountered on the left side." << std::endl;
        return nullptr;
    }
}

void OperatorNode::print() const {
    if (op == 's' || op == 'c') {
        std::cout << op;
        right->print();
    }
    else {
        std::cout << "(";
        left->print();
        std::cout << " " << op << " ";
        right->print();
        std::cout << ")";
    }
}

void OperatorNode::printTree(int indent) const {
    std::cout << std::string(indent, ' ') << "OperatorNode: " << op << std::endl;
    if (op == 's' || op == 'c') {
        right->printTree(indent + 2);
    }
    else {
        left->printTree(indent + 2);
        right->printTree(indent + 2);
    }
}

void OperatorNode::printPrefix() const {
    std::cout << op << " ";
    left->printPrefix();
    std::cout << " ";
    right->printPrefix();
}

void OperatorNode::printVariables(std::set<std::string>& variableSet) const {
    left->printVariables(variableSet);
    right->printVariables(variableSet);
}

void OperatorNode::setLeft(Node* Left) {
    left = Left;
}

void OperatorNode::setRight(Node* Right) {
    right = Right;
}

Node* OperatorNode::getLeft() {
    return left;
}

Node* OperatorNode::getRight() {
    return right;
}
