#ifndef PARSER_H
#define PARSER_H

#include "Tree.h"

class Parser
{
public:
    void parseFormula(Tree& tree, std::string formula);

private:
    int parseNodes(Node* currentNode, std::string formula, int start, bool* wasError, Tree& tree);
    bool isValidArgument(std::string value);
    static const std::map<std::string, int> funMap;
};

#endif
