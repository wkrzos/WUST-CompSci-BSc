#ifndef UIINTERFACE_H
#define UIINTERFACE_H

#include "Tree.h"
#include "Parser.h"
#include <string>

class UIInterface
{
public:
    static void startUI();

private:
    static void executeCommand(std::string& command, Tree& currentTree, Parser& parser, std::string* arguments, int& argumentCount);
    static void handleEnterCommand(Tree& tree, Parser& parser, std::string* args, int size);
    static void handleVarsCommand(const Tree& tree);
    static void handlePrintCommand(const Tree& tree);
    static void handleCompCommand(Tree& tree, std::string* args, int size);
    static void handleJoinCommand(Tree& tree, Parser& parser, std::string* args, int size);
};

#endif // UIINTERFACE_H
