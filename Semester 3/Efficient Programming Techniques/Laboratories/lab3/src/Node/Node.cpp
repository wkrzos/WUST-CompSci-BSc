// Node class representing a single node in the expression tree
class Node {
public:
    virtual ~Node() = default;
    virtual double evaluate() const = 0;
    virtual void print() const = 0;
    virtual void printTree(int indent = 0) const = 0;
};