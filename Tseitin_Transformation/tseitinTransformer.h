#ifndef TSEITIN_H
#define TSEITIN_H

#include <vector>
#include <map>
#include <string>
#include "treeNode.h"

class TseitinTransformer
{
private:
    TreeNode* formulaRoot;
    std::vector<std::vector<int>> cnf; 
    std::map<std::string, int> varIdTable; 
    int varIdCounter = 0;
    void transSubformula(TreeNode* subRoot);
    void addNegEq(int curID, int childID); 
    void addOrEq(int curID, int leftID, int rightID); 
    void addAndEq(int curID, int leftID, int rightID); 
    TreeNode* transToNNF(TreeNode* node);
    void AssignIds(TreeNode* node);
public:
    TseitinTransformer(TreeNode* root);
    std::vector<std::vector<int>> transform();
    std::string cnfString() const; 
};

#endif