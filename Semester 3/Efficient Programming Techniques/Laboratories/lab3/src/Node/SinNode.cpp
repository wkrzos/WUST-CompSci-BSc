#include "SinNode.h"

SinNode::SinNode(Node* op) : operand(op) {}

SinNode::~SinNode() {
    delete operand;
}

double SinNode::evaluate() const {
    return std::sin(operand->evaluate());
}

void SinNode::print() const {
    std::cout << "sin(";
    operand->print();
    std::cout << ")";
}

void SinNode::printTree(int indent) const {
    std::cout << std::string(indent, ' ') << "SinNode" << std::endl;
    operand->printTree(indent + 2);
}

void SinNode::printPrefix() const {
    std::cout << "sin ";
    operand->printPrefix();
}

void SinNode::printVariables(std::set<std::string>& variableSet) const {
    operand->printVariables(variableSet);
}

size_t SinNode::countVariables() const {
    return operand->countVariables();
}

double SinNode::evaluateWithValues(const std::map<std::string, double>& values) const {
    return std::sin(operand->evaluateWithValues(values));
}
