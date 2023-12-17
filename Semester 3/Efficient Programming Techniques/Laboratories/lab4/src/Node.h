#ifndef NODE
#define NODE
#include <string>
#include <vector>

enum TYPE
{	
	CONSTANT,
	VARIABLE,
	OPERATION,
	NO_TYPE
};

class Node
{
private:
	int numberOfNodes;
	TYPE type;
	std::string key;
	Node* nodes;

public:
	Node();
	Node(const Node& otherNode);
	~Node();

	Node& operator=(const Node& newValue);

	std::string toString() const;

	Node* getNodes() const;
	Node* getNode(int index) const;
	std::string getValue() const;
	int getNumberOfNodes() const;
	TYPE getNodeType() const;

	void setNode(int index, Node& node);
	void setValue(std::string value);
	void setNumberOfNodes(int numberOfNodes);
	void setNodeType(TYPE type);
};

#endif