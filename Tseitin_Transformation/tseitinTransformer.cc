#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode* root) : formulaRoot{ root } {}

void TseitinTransformer::transSubformula(TreeNode* subRoot) {
	if (subRoot == nullptr) return;
	if (subRoot == formulaRoot) {
		std::vector<int> v;
		v.push_back(subRoot->GetId());
		cnf.push_back(v);
	}
	if (subRoot->getContent() == "-") {
		int curId = subRoot->GetId();
		int childID = subRoot->getLeftChild()->GetId();
		addNegEq(curId, childID);
	}
	else if (subRoot->getContent() == "+") {
		int curId = subRoot->GetId();
		int leftID = subRoot->getLeftChild()->GetId();
		int rightID = subRoot->getRightChild()->GetId();
		addOrEq(curId, leftID, rightID);
	}
	else if (subRoot->getContent() == "*") {
		int curId = subRoot->GetId();
		int leftID = subRoot->getLeftChild()->GetId();
		int rightID = subRoot->getRightChild()->GetId();
		addAndEq(curId, leftID, rightID);
	}
	transSubformula(subRoot->getLeftChild());
	transSubformula(subRoot->getRightChild());
}
TreeNode* TseitinTransformer::transToNNF(TreeNode* node) {
	if (node == nullptr)  return nullptr;
	if (node->getContent() == "-") {
		TreeNode* child = node->getLeftChild();
		if (child->getContent() == "-") { //simplify --p = p
			node = child->getLeftChild();
		}
		else if (child->getContent() == "+") { //-(a+b) = -a*-b
			TreeNode* leftSubFormula = child->getLeftChild();
			TreeNode* rightSubFormula = child->getRightChild();
			node = new TreeNode("*");
			node->updateChildren(new TreeNode("-"), new TreeNode("-"));
			node->getLeftChild()->updateLeftChild(leftSubFormula);
			node->getRightChild()->updateLeftChild(rightSubFormula);
		}
		else if (child->getContent() == "*") { //-(a*b) = -a+-b
			TreeNode* leftSubFormula = child->getLeftChild();
			TreeNode* rightSubFormula = child->getRightChild();
			node = new TreeNode("+");
			node->updateChildren(new TreeNode("-"), new TreeNode("-"));
			node->getLeftChild()->updateLeftChild(leftSubFormula);
			node->getRightChild()->updateLeftChild(rightSubFormula);
		}
	};
	TreeNode* l = transToNNF(node->getLeftChild());
	TreeNode* r = transToNNF(node->getRightChild());
	node->updateChildren(l, r);
	return node;
}

void TseitinTransformer::AssignIds(TreeNode* node) {
	if (node == nullptr) return;
	if (node->getContent() == "+"
		|| node->getContent() == "*"
		|| node->getContent() == "-") {
		this->varIdCounter++;
		node->SetId(this->varIdCounter);
	}
	else {
		if (varIdTable.count(node->getContent())) {
			node->SetId(varIdTable.at(node->getContent()));
		}
		else {
			this->varIdCounter++;
			node->SetId(this->varIdCounter);
			varIdTable.insert({ node->getContent() ,varIdCounter});
		}
	}
	AssignIds(node->getLeftChild());
	AssignIds(node->getRightChild());
}

void TseitinTransformer::addNegEq(int curID, int childID) {
	std::vector<int> v1, v2;
	v1.push_back(curID);
	v1.push_back(childID);
	v2.push_back(-curID);
	v2.push_back(-childID);
	cnf.push_back(v1);
	cnf.push_back(v2);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
	std::vector<int> v1, v2,v3;
	v1.push_back(curID);
	v1.push_back(-leftID);
	v2.push_back(curID);
	v2.push_back(-rightID);
	v3.push_back(-curID);
	v3.push_back(leftID);
	v3.push_back(rightID);
	cnf.push_back(v1);
	cnf.push_back(v2);
	cnf.push_back(v3);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
	std::vector<int> v1, v2, v3;
	v1.push_back(-curID);
	v1.push_back(leftID);
	v2.push_back(-curID);
	v2.push_back(rightID);
	v3.push_back(curID);
	v3.push_back(-leftID);
	v3.push_back(-rightID);
	cnf.push_back(v1);
	cnf.push_back(v2);
	cnf.push_back(v3);
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
	formulaRoot = transToNNF(formulaRoot);
	AssignIds(formulaRoot);
	transSubformula(formulaRoot);
	return cnf;
}

std::string TseitinTransformer::cnfString() const {
	std::string result = "[";
	for (int i = 0; i < cnf.size(); i++) {
		result += "[";
		for (int j = 0; j < cnf[i].size(); j++) {
			result += std::to_string(cnf[i][j]);
			if (j != cnf[i].size() - 1)
				result += ",";
		}
		result += "]";
	}
	result += "]";
	return result;
}