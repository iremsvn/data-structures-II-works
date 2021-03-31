/**
*Author: İrem Seven
*ID: 21704269
*Section: 1
*Assignment: 2
*/

#include <iostream>
#include "DecisionTree.h"
#include "DecisionTreeNode.h"
using namespace std;


int main()
{
	DecisionTree* tree = new DecisionTree();
	tree->train("train_data.txt", 120, 21);
	tree->print();
	cout << "\nAccuracy is: " << tree->test("test_data.txt", 120) << endl;

	return 0;
}

