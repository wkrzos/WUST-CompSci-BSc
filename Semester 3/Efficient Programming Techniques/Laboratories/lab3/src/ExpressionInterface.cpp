#include "ExpressionInterface.h"

ExpressionInterface::ExpressionInterface() : expressionTree(nullptr) {}

ExpressionInterface::~ExpressionInterface() {
    delete expressionTree;
}

void ExpressionInterface::executeCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "enter") {
        std::string formula;
        getline(iss, formula);
        handleEnterCommand(formula);
    }
    else if (cmd == "vars") {
        handleVarsCommand();
    }
    else if (cmd == "print") {
        handlePrintCommand();
    }
    else if (cmd == "comp") {
        std::vector<double> values;
        double value;
        while (iss >> value) {
            values.push_back(value);
        }
        handleCompCommand(values);
    }
    else if (cmd == "join") {
        std::string formula;
        getline(iss, formula);
        handleJoinCommand(formula);
    }
    else {
        std::cerr << "Error: Unknown command" << std::endl;
    }
}

void ExpressionInterface::handleEnterCommand(const std::string& formula) {
    PrefixExpressionParser parser(formula);
    Node* newTree = parser.parse();

    if (newTree != nullptr) {
        delete expressionTree;
        expressionTree = newTree;

        std::cout << "Formula: ";
        expressionTree->print();
        std::cout << std::endl;
    }
    else {
        std::cerr << "Error: Invalid formula. Tree not updated." << std::endl;
    }
}

void ExpressionInterface::handleVarsCommand() const {
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

void ExpressionInterface::handlePrintCommand() const {
    if (expressionTree != nullptr) {
        std::cout << "Expression Tree (Prefix Form): ";
        expressionTree->printPrefix();
        std::cout << std::endl;
    }
    else {
        std::cerr << "Error: No formula entered. Use 'enter' command first." << std::endl;
    }
}

void ExpressionInterface::handleCompCommand(const std::vector<double>& values) const {
    if (expressionTree != nullptr) {
        std::set<std::string> variables;
        expressionTree->printVariables(variables);
        std::map<std::string, double> vals;

        size_t expectedVarCount = variables.size();
        if (values.size() != expectedVarCount) {
            std::cerr << "Error: Number of values provided does not match the number of variables in the formula."
                << std::endl;
        }
        else {
            int i = 0;
            for (std::set<std::string>::iterator it = variables.begin(); it != variables.end(); it++) {
                vals[*it] = values[i];
                i++;
            }
            double result = expressionTree->evaluateWithValues(vals);
            std::cout << "Result: " << result << std::endl;
        }
    }
    else {
        std::cerr << "Error: No formula entered. Use 'enter' command first." << std::endl;
    }
}

void Exp
