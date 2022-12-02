#ifndef TNODE_H
#define TNODE_H

#include <string>

class TreeNode {
    std::string content;
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;
protected:
    TreeNode* getLeftChild() const;
    TreeNode* getRightChild() const;
public:
    TreeNode(std::string cntt);
    void updateLeftChild(TreeNode* lChild);
    void updateChildren(TreeNode* lChild, TreeNode* rChild);
    std::string getContent() const;
    virtual ~TreeNode();
};

class OperatorNode : public TreeNode {
public:
    OperatorNode(std::string cntt);
};

class VariableNode : public TreeNode {
public:
    VariableNode(std::string cntt);
};

#endif
