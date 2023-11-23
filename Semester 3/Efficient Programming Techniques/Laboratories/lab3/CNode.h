class CNode {
public:
	CNode();
	CNode();
	~CNode();

	int key;
	bool isLeaf;

	CNode* parent;
	CNode* childLeft;
	CNode* childRight;
};
