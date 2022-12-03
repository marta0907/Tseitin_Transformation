#include "tseitinTransformer.h"
//#include "satSolver.h"
#include <vector>
#include <exception>
#include "treeNode.h"
#include "parser.h"
#include <string>
#include <sstream>


int main() {
	std::string line;
	std::string formulaStr;

	while (getline(std::cin, line)) {
		try {
			TreeNode* root;
			FormulaParser fp(line);
			root = fp.getTreeRoot();
			TseitinTransformer tr(root);
			tr.transform();
			std::cout << tr.cnfString() << std::endl;
			delete root;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}