#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln) : tknzr{ new Tokenizer{ln} } {}

TreeNode* FormulaParser::parseFormula() {
    TreeNode* resultToken = parseConjTerm();
    if (resultToken == nullptr) {
        throw std::runtime_error("Error: invalid input");
    }
    while (tknzr->advanceToken("+"))
    {
        currentToken = tknzr->getToken();
        TreeNode* a = resultToken;
        TreeNode* b = parseConjTerm();
        resultToken = new OperatorNode("+");
        resultToken->updateChildren(a, b);
    }
    return resultToken;
}

TreeNode* FormulaParser::parseConjTerm() {
    TreeNode* resultToken = parseTerm();
    if (resultToken == nullptr) {
        throw std::runtime_error("Error: invalid input");
    }
    while (tknzr->advanceToken("*"))
    {
        currentToken = tknzr->getToken();
        TreeNode* a = resultToken;
        TreeNode* b = parseTerm();
        resultToken = new OperatorNode("*");
        resultToken->updateChildren(a, b);
    }
    return resultToken;
}

TreeNode* FormulaParser::parseTerm() {
    TreeNode* resultNode = nullptr;
    if (tknzr->hasToken()) {
        currentToken = tknzr->getToken();
        if (currentToken.type == Variable) {

            resultNode = new VariableNode(currentToken.content);
        }
        else if (currentToken.content == "-") {
            resultNode = new OperatorNode(currentToken.content);
            TreeNode* node = parseTerm();
            if (node == nullptr) {
                throw std::runtime_error("Error: invalid input");
            }
            resultNode->updateLeftChild(node);
        }
        else if (currentToken.content == "(") {
            if (tknzr->hasToken()) {
                resultNode = parseFormula();
                if (tknzr->hasToken()) {
                    currentToken = tknzr->getToken();
                    if (currentToken.content != ")") {
                        throw std::runtime_error("Error: invalid input");
                    }
                }
                else {
                    throw std::runtime_error("Error: invalid input");
                }
            }
            else {
                throw std::runtime_error("Error: invalid input");
            }
        }
    }
    return resultNode;
}

TreeNode* FormulaParser::getTreeRoot() {
    TreeNode* root = parseFormula();
    if (tknzr->hasToken()) {
        throw std::runtime_error("Error: invalid input");
    }
    return root;
}

FormulaParser::~FormulaParser() {
    delete tknzr;
}