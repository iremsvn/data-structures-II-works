/**
*Author: Ýrem Seven
*ID: 21704269
*Section: 1
*Assignment: 2
*/

#ifndef __DECISION_TREE_NODE
#define __DECISION_TREE_NODE
#include <cstddef>
#include <string>

class DecisionTreeNode {
private:
	DecisionTreeNode();
	void setIsLeaf(bool isLeaf);
	bool getIsLeaf();

	int data; //feature id if non-leaf, class decision if its leaf
	DecisionTreeNode* left;
	DecisionTreeNode* right;

	bool isLeaf; //keep track of leaf node or not

	friend class DecisionTree;
};


#endif
