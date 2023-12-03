#include "CosNode.h"

CosNode::CosNode(Node* op) : operand(op) {}

CosNode::~CosNode() {
    delete operand;
}

double CosNode::evaluate() const {
    return std::cos(operand->evaluate());
}

void CosNode::print() const {
    std::cout << "cos(";
    operand->print();
    std::cout << ")";
}

void CosNode::printTree(int indent) const {
    std::cout << std::string(indent, ' ') << "CosNode" << std::endl;
    operand->printTree(indent + 2);
}

void CosNode::printPrefix() const {
    std::cout << "cos ";
    operand->printPrefix();
}

void CosNode::printVariables(std::set<std::string>& variableSet) const {
    operand->printVariables(variableSet);
}

size_t CosNode::countVariables() const {
    return operand->countVariables();
}

double CosNode::evaluateWithValues(const std::map<std::string, double>& values) const {
    return std::cos(operand->evaluateWithValues(values));
}
