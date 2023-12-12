#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <map>
#include <sstream>
#include <string>
#include <vector>

const std::string LIST_OF_NUMBERS = "0123456789";

class Tree
{
public:
	Tree();
	~Tree();
	Tree(const Tree& other);
	Tree& operator=(const Tree& newValue);
	Tree operator+(const Tree& newValue) const;

	void setRoot(Node* newRoot); // New method to set the root
	Node* getRoot() /*const*/; // New method to access the root

	std::string toString() const;
	int comp(std::string args);
	std::string getArgumentsList() const;
	std::string getErrorAndClear();
	void printNodes() const;

	void setArgumentValue(std::string arg, int value);

	std::stringstream& getErrorStream();
	void setErrorStream(const std::stringstream& stream);

	void clearArguments();

private:
	Node* root;
	std::stringstream errorStream;
	int comp(Node* currentNode);
	std::map<std::string, int> argsMap;
	std::vector<std::string> argsVector;
	void removeArgument(std::string arg);
	void setArgumentValueByIndex(int index, int value);
	static int stringToNumber(std::string str);
};

#endif
