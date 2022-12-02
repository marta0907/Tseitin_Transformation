#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <iostream>  
#include "tokenizer.h"

class TreeNode;
class Tokenizer;

class FormulaParser {
    Tokenizer* tknzr;
    Token currentToken;
    TreeNode* parseFormula();
    TreeNode* parseConjTerm();
    TreeNode* parseTerm();
public:
    FormulaParser(std::string ln);
    TreeNode* getTreeRoot();
    ~FormulaParser();
};
#endif