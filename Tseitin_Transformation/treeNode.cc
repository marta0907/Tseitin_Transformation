#include "treeNode.h"

TreeNode::TreeNode(std::string cntt) : content{ cntt } {}

std::string TreeNode::getContent() const {
    return this->content;
}

TreeNode* TreeNode::getLeftChild() const {
    return this->leftChild;
}
TreeNode* TreeNode::getRightChild() const {
    return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode* lChild) {
    this->leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode* lChild, TreeNode* rChild) {
    this->leftChild = lChild;
    this->rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt) : TreeNode{ cntt } {}

VariableNode::VariableNode(std::string cntt) : TreeNode{ cntt } {}

TreeNode::~TreeNode() {
    if (leftChild != nullptr)
        delete leftChild;
    if (rightChild != nullptr)
        delete rightChild;
}

