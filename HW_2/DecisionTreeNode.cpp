/**
*Author: Ýrem Seven
*ID: 21704269
*Section: 1
*Assignment: 2
*/

#include "DecisionTreeNode.h"
#include <iostream>
using namespace std;

DecisionTreeNode::DecisionTreeNode() {
	data = -1;
	left = NULL;
	right = NULL;
	isLeaf = false;
}


void DecisionTreeNode::setIsLeaf(bool isLeafN) { //if true its leaf node if false its decision node
	isLeaf = isLeafN;
}
bool DecisionTreeNode::getIsLeaf() {
	return isLeaf;
}



