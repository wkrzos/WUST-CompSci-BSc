#ifndef NODE
#define NODE

#include <string>

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
    // Constructors and Destructor
    Node();
    Node(const Node& otherNode);
    ~Node();

    // Assignment Operator
    Node& operator=(const Node& newValue);

    // Accessor Methods
    std::string toString() const;
    Node* getNodes() const;
    Node* getNode(int index) const;
    std::string getValue() const;
    int getNumberOfNodes() const;
    TYPE getNodeType() const;

    // Mutator Methods
    void setNode(int index, Node& node);
    void setValue(std::string value);
    void setNumberOfNodes(int numberOfNodes);
    void setNodeType(TYPE type);
};

#endif
