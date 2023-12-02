#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdio>
#include <cstring>

// Node class representing a single node in the expression tree
class Node {
public:
    virtual ~Node() = default;
    virtual double evaluate() const = 0;
    virtual void print() const = 0;
    virtual void printTree(int indent = 0) const = 0;
};

// ConstantNode class representing a constant in the expression tree
class ConstantNode : public Node {
private:
    double value;

public:
    ConstantNode(double val) : value(val) {}

    double evaluate() const override {
        return value;
    }

    void print() const override {
        std::cout << value;
    }

    void printTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "ConstantNode: " << value << std::endl;
    }
};

// VariableNode class representing a variable in the expression tree
class VariableNode : public Node {
private:
    std::string name;
    double value;

public:
    VariableNode(const std::string& varName) : name(varName), value(0.0) {}

    void assignValue(double val) {
        value = val;
    }

    double evaluate() const override {
        return value;
    }

    void print() const override {
        std::cout << name;
    }

    void printTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "VariableNode: " << name << std::endl;
    }
};

// OperatorNode class representing an operator in the expression tree
class OperatorNode : public Node {
private:
    char op;
    Node* left;
    Node* right;

public:
    OperatorNode(char operation, Node* l, Node* r) : op(operation), left(l), right(r) {}

    ~OperatorNode() override {
        delete left;
        delete right;
    }

    double evaluate() const override {
        switch (op) {
        case '+':
            return left->evaluate() + right->evaluate();
        case '-':
            return left->evaluate() - right->evaluate();
        case '*':
            return left->evaluate() * right->evaluate();
        case '/':
            return left->evaluate() / right->evaluate();
        default:
            std::cerr << "Error: Unknown operator " << op << std::endl;
            return 0.0;
        }
    }

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << " " << op << " ";
        right->print();
        std::cout << ")";
    }

    void printTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "OperatorNode: " << op << std::endl;
        left->printTree(indent + 2);
        right->printTree(indent + 2);
    }
};

// PrefixExpressionParser class for parsing prefix expressions into a tree
class PrefixExpressionParser {
private:
    std::vector<std::string> tokens;
    size_t currentTokenIndex;

    Node* parseExpression() {
        std::string token = tokens[currentTokenIndex++];
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            return new ConstantNode(std::stod(token));
        }
        else if (isalpha(token[0])) {
            return new VariableNode(token);
        }
        else if (token.size() == 1 && strchr("+-*/", token[0])) {
            Node* left = parseExpression();
            Node* right = parseExpression();
            return new OperatorNode(token[0], left, right);
        }
        else {
            std::cerr << "Error: Invalid token " << token << std::endl;
            return nullptr;
        }
    }

public:
    PrefixExpressionParser(const std::string& expression) {
        std::istringstream iss(expression);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        currentTokenIndex = 0;
    }

    ~PrefixExpressionParser() = default;

    Node* parse() {
        return parseExpression();
    }

    void print() {
        Node* expressionTree = parseExpression();
        if (expressionTree != nullptr) {
            std::cout << "Expression Tree: ";
            expressionTree->print();
            std::cout << std::endl;
            std::cout << "Tree Structure:" << std::endl;
            expressionTree->printTree();
        }
        delete expressionTree;
    }
};

int main() {
    // Example usage
    std::string inputExpression = "* - A / B C - / A K L";
    PrefixExpressionParser parser(inputExpression);
    Node* expressionTree = parser.parse();

    if (expressionTree != nullptr) {
        // Assigning a value to the variable 'a'
        VariableNode* variableNode = dynamic_cast<VariableNode*>(expressionTree);
        if (variableNode != nullptr) {
            variableNode->assignValue(5.0);  // Assigning the value 5.0 to the variable 'a'
        }

        std::cout << "Expression Tree: ";
        expressionTree->print();
        std::cout << std::endl;
        std::cout << "Tree Structure:" << std::endl;
        expressionTree->printTree();

        double result = expressionTree->evaluate();
        std::cout << "Result: " << result << std::endl;
        delete expressionTree;
    }

    return 0;
}
