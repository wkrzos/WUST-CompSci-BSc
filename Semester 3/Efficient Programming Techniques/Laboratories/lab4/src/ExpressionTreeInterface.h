#ifndef EXPRESSIONTREEINTERFACE_H
#define EXPRESSIONTREEINTERFACE_H

#include "PrefixExpressionTree.h"
#include "Parser.h"

class ExpressionTreeInterface
{
public:
    static void run();

private:
    static void executeCommand(std::string& command, PrefixExpressionTree& currentTree, Parser& parser, std::string* arguments, int& argumentCount);
    static void handleEnterCommand(PrefixExpressionTree& tree, Parser& parser, std::string* args, int size);
    static void handleVarsCommand(const PrefixExpressionTree& tree);
    static void handlePrintCommand(const PrefixExpressionTree& tree);
    static void handleCompCommand(PrefixExpressionTree& tree, std::string* args, int size);
    static void handleJoinCommand(PrefixExpressionTree& tree, Parser& parser, std::string* args, int size);
};

#endif // EXPRESSIONTREEINTERFACE_H
