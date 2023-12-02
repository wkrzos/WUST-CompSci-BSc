#include <vector>
#include <string>

class Node {
private:
	NodeKey key;
	NodeType type;

public:
	Node();
	Node();
	~Node();

	int key;
	bool isLeaf;

	Node* parent;
	std::vector<Node*> children;

	void addChild(Node* child);
};

enum NodeType {
	constant,
	variable,
	operation
};

struct NodeKey {
	double constant;
	char variable;
	//What about the operation?
};

enum Operations {
	add,
	sub,
	mult,
	div,
	sin,
	cos,
	sqrt
};
