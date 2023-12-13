#ifndef PREFIXEXPRESSIONTREE_H
#define PREFIXEXPRESSIONTREE_H

#include "Node.h"
#include <map>
#include <sstream>
#include <string>
#include <vector>

const std::string LIST_OF_NUMBERS = "0123456789";

class PrefixExpressionTree
{
public:
	PrefixExpressionTree();
	PrefixExpressionTree(const PrefixExpressionTree& other);
	~PrefixExpressionTree();

	PrefixExpressionTree& operator=(const PrefixExpressionTree& newValue);
	PrefixExpressionTree operator+(const PrefixExpressionTree& newValue) const;



	std::string toString() const;
	int comp(std::string args);
	std::string getArgumentsList() const;
	void printNodes() const;

	void clearArguments();
	void setArgumentValue(std::string arg, int value);

	void setRoot(Node* newRoot); // New method to set the root
	Node* getRoot() /*const*/; // New method to access the root

private:
	Node* root;
	int comp(Node* currentNode);
	std::map<std::string, int> argsMap;
	std::vector<std::string> argsVector;
	void removeArgument(std::string arg);
	void setArgumentValueByIndex(int index, int value);
	static int stringToNumber(std::string str);
};

#endif
