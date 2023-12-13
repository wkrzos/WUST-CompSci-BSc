#ifndef PARSER_H
#define PARSER_H

#include "PrefixExpressionTree.h"

class Parser
{
public:
    void parseFormula(PrefixExpressionTree& tree, std::string formula);

private:
    int parseNodes(Node* currentNode, std::string formula, int start, bool* wasError, PrefixExpressionTree& tree);
    bool isValidArgument(std::string value);
    static const std::map<std::string, int> funMap;
};

#endif
