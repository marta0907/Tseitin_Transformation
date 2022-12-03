#ifndef TNODE_H
#define TNODE_H

#include <string>

class TreeNode {
    std::string content;
    int id = 0;
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;
public:
    TreeNode* getLeftChild();
    TreeNode* getRightChild();
    TreeNode(std::string cntt);
    void updateLeftChild(TreeNode* lChild);
    void updateChildren(TreeNode* lChild, TreeNode* rChild);
    std::string getContent() const;
    void SetId(int id);
    int GetId();
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
