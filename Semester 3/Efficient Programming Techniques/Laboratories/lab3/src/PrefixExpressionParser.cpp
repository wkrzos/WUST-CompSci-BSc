#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>

// Node class representing a single node in the expression tree
class Node {
public:
    virtual ~Node() = default;
    virtual double evaluate() const = 0;
    virtual void print() const = 0;
    virtual void printTree(int indent = 0) const = 0;
    virtual void printPrefix() const = 0;
    virtual void printVariables(std::set<std::string>& variableSet) const = 0;
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

    void printPrefix() const override {
        std::cout << value;
    }

    void printVariables(std::set<std::string>& variableSet) const override {
        // Constants don't have variables
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

    void printPrefix() const override {
        std::cout << name;
    }

    void printVariables(std::set<std::string>& variableSet) const override {
        // Check if the variable has been encountered before
        if (variableSet.find(name) == variableSet.end()) {
            std::cout << name << " ";
            variableSet.insert(name); // Add the variable to the set to mark it as encountered
        }
    }
};

class SinNode : public Node {
private:
    Node* operand;

public:
    SinNode(Node* op) : operand(op) {}

    ~SinNode() override {
        delete operand;
    }

    double evaluate() const override {
        return std::sin(operand->evaluate());
    }

    void print() const override {
        std::cout << "sin(";
        operand->print();
        std::cout << ")";
    }

    void printTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "SinNode" << std::endl;
        operand->printTree(indent + 2);
    }

    void printPrefix() const override {
        std::cout << "sin ";
        operand->printPrefix();
    }

    void printVariables(std::set<std::string>& variableSet) const override {
        operand->printVariables(variableSet);
    }
};

class CosNode : public Node {
private:
    Node* operand;

public:
    CosNode(Node* op) : operand(op) {}

    ~CosNode() override {
        delete operand;
    }

    double evaluate() const override {
        return std::cos(operand->evaluate());
    }

    void print() const override {
        std::cout << "cos(";
        operand->print();
        std::cout << ")";
    }

    void printTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "CosNode" << std::endl;
        operand->printTree(indent + 2);
    }

    void printPrefix() const override {
        std::cout << "cos ";
        operand->printPrefix();
    }

    void printVariables(std::set<std::string>& variableSet) const override {
        operand->printVariables(variableSet);
    }
};

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
        case 's':  // for sin
            return std::sin(right->evaluate());
        case 'c':  // for cos
            return std::cos(right->evaluate());
        default:
            std::cerr << "Error: Unknown operator " << op << std::endl;
            return 0.0;
        }
    }

    void print() const override {
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

    void printTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "OperatorNode: " << op << std::endl;
        if (op == 's' || op == 'c') {
            right->printTree(indent + 2);
        }
        else {
            left->printTree(indent + 2);
            right->printTree(indent + 2);
        }
    }

    void printPrefix() const override {
        std::cout << op << " ";
        left->printPrefix();
        std::cout << " ";
        right->printPrefix();
    }

    void printVariables(std::set<std::string>& variableSet) const override {
        left->printVariables(variableSet);
        right->printVariables(variableSet);
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
            if (token == "sin" || token == "cos") {
                Node* operand = parseExpression();
                if (operand != nullptr) {
                    if (token == "sin") {
                        return new SinNode(operand);
                    }
                    else if (token == "cos") {
                        return new CosNode(operand);
                    }
                }
            }
            else {
                return new VariableNode(token);
            }
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

    void printTree() {
        Node* expressionTree = parseExpression();
        if (expressionTree != nullptr) {
            std::cout << "Expression Tree: ";
            expressionTree->print();
            std::cout << std::endl;
            std::cout << "Tree Structure:" << std::endl;
            expressionTree->printTree();
            std::cout << "Prefix Form: ";
            expressionTree->printPrefix();
            std::cout << std::endl;
            std::cout << "Variables: ";
            std::set<std::string> variableSet;
            expressionTree->printVariables(variableSet);
            std::cout << std::endl;
        }
        delete expressionTree;
    }
};

int main() {
    // Example usage
    std::string inputExpression = "* - 1 / 2 3 - / 4 5 cos 6";
    PrefixExpressionParser parser(inputExpression);
    Node* expressionTree = parser.parse();

    if (expressionTree != nullptr) {
        std::cout << "Expression Tree: ";
        expressionTree->print();
        std::cout << std::endl;
        std::cout << "Tree Structure:" << std::endl;
        expressionTree->printTree();
        std::cout << "Prefix Form: ";
        expressionTree->printPrefix();
        std::cout << std::endl;
        std::cout << "Variables: ";
        std::set<std::string> variableSet;
        expressionTree->printVariables(variableSet);
        std::cout << std::endl;

        double result = expressionTree->evaluate();
        std::cout << "Result: " << result << std::endl;
        delete expressionTree;
    }

    return 0;
}