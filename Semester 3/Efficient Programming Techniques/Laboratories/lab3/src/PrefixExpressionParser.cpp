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
    virtual size_t countVariables() const = 0;
    virtual double evaluateWithValues(const std::vector<double>& values) const = 0;
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

    size_t countVariables() const override {
        return 0;
    }

    double evaluateWithValues(const std::vector<double>& values) const override {
        // Constants don't depend on variables
        return value;
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
            variableSet.insert(name); // Add the variable to the set to mark it as encountered
        }
    }

    size_t countVariables() const override {
        return 1;
    }

    double evaluateWithValues(const std::vector<double>& values) const override {
        // Return the value assigned to the variable
        return value;
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

    size_t countVariables() const override {
        return operand->countVariables();
    }

    double evaluateWithValues(const std::vector<double>& values) const override {
        return std::sin(operand->evaluateWithValues(values));
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

    size_t countVariables() const override {
        return operand->countVariables();
    }

    double evaluateWithValues(const std::vector<double>& values) const override {
        return std::cos(operand->evaluateWithValues(values));
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

    size_t countVariables() const override {
        return left->countVariables() + right->countVariables();
    }

    double evaluateWithValues(const std::vector<double>& values) const override {
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

// Interface class
class ExpressionInterface {
private:
    Node* expressionTree;

public:
    ExpressionInterface() : expressionTree(nullptr) {}

    ~ExpressionInterface() {
        delete expressionTree;
    }

    void executeCommand(const std::string& command) {
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "enter") {
            // Execute 'enter' command
            std::string formula;
            getline(iss, formula);
            handleEnterCommand(formula);
        }
        else if (cmd == "vars") {
            // Execute 'vars' command
            handleVarsCommand();
        }
        else if (cmd == "print") {
            // Execute 'print' command
            handlePrintCommand();
        }
        else if (cmd == "comp") {
            // Execute 'comp' command
            std::vector<double> values;
            double value;
            while (iss >> value) {
                values.push_back(value);
            }
            handleCompCommand(values);
        }
        else {
            std::cerr << "Error: Unknown command" << std::endl;
        }
    }

private:
    void handleEnterCommand(const std::string& formula) {
        PrefixExpressionParser parser(formula);
        Node* newTree = parser.parse();

        if (newTree != nullptr) {
            // Delete the old expression tree
            delete expressionTree;
            expressionTree = newTree;

            std::cout << "Formula: " << formula << std::endl;
        }
        else {
            std::cerr << "Error: Invalid formula. Tree not updated." << std::endl;
        }
    }

    void handleVarsCommand() const {
        if (expressionTree != nullptr) {
            std::set<std::string> variableSet;
            expressionTree->printVariables(variableSet);
            std::cout << "Variables: ";
            for (const auto& variable : variableSet) {
                std::cout << variable << " ";
            }
            std::cout << std::endl;
        }
        else {
            std::cerr << "Error: No formula entered. Use 'enter' command first." << std::endl;
        }
    }

    void handlePrintCommand() const {
        if (expressionTree != nullptr) {
            std::cout << "Expression Tree (Prefix Form): ";
            expressionTree->printPrefix();
            std::cout << std::endl;
        }
        else {
            std::cerr << "Error: No formula entered. Use 'enter' command first." << std::endl;
        }
    }

    void handleCompCommand(const std::vector<double>& values) const {
        if (expressionTree != nullptr) {
            size_t expectedVarCount = expressionTree->countVariables();
            if (values.size() != expectedVarCount) {
                std::cerr << "Error: Number of values provided does not match the number of variables in the formula."
                    << std::endl;
            }
            else {
                double result = expressionTree->evaluateWithValues(values);
                std::cout << "Result: " << result << std::endl;
            }
        }
        else {
            std::cerr << "Error: No formula entered. Use 'enter' command first." << std::endl;
        }
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
