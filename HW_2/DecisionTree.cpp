/**
*Author: Ýrem Seven
*ID: 21704269
*Section: 1
*Assignment: 2
*/

#include <iostream>
#include "DecisionTree.h"
#include <cstddef>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

DecisionTree::DecisionTree(){
	rootptr = NULL;
	data = NULL;
	labels = NULL;
	numFeatures = 0;
	numSamples = 0;
}


double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses) {
	double entropy = 0;
	double totalCount = 0;
	
	for (int i = 0; i < numClasses; i++)
	{
		totalCount += classCounts[i];
	}

	for (int i = 0; i < numClasses; i++)
	{
		if (classCounts[i] != 0) {

			entropy += (classCounts[i] / totalCount) * log2(classCounts[i] / totalCount);

		}
	}
	return entropy * (-1);
}


void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures) {
	
	//make used samples all true for first decision split
	bool* usedSamples = new bool[numSamples];
	for (int i = 0; i < numSamples; i++) {
		usedSamples[i] = true;
	}

	//usedFeatures will guarantee not to use same feature again on same path
	bool* usedFeatureIds = new bool[numFeatures];
	for (int i = 0; i < numFeatures; i++) {
		usedFeatureIds[i] = true; //true means feature hasnt used yet 
	}

	//Make Copy of rootptr
	rootptr = new DecisionTreeNode();
	DecisionTreeNode* root;
	root = rootptr;
	int featureId = 0;
	int branch = false;
	build(root, data, usedSamples, usedFeatureIds, featureId, branch);
}


void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures) {


	ifstream inputFileStream(fileName.c_str());

	data = new const bool* [numSamples];
	labels = new int[numSamples];
	this->numFeatures = numFeatures;
	this->numSamples = numSamples;
	for (int i = 0; i < numSamples; i++) {
		data[i] = new bool[numFeatures];
	}

	int row = 0;
	int x = 0;

	while (row < numSamples) {
		for (int i = 0; i < numFeatures; i++) {
			inputFileStream >> x; 
			if (x == 0)
				const_cast<bool&>(data[row][i]) = false;
			else
				const_cast<bool&>(data[row][i]) = true;
		}

		inputFileStream >> labels[row];
		row++;
	}
	
	//Can be used for tree builder to test 
	/*
	for (int i = 0; i < numFeatures; i++) {
		cout << i << ";";
	}
	cout << endl;
	for (int rowL = 0; rowL < numSamples; rowL++) {
		for (int i = 0; i < numFeatures; i++) {
			cout << data[rowL][i] << ";";
		}
		cout << labels[rowL] << endl;
	}
	*/

	//find numOfClasses by taking max classLabel integer in labels, numClasses = max
	numClasses = labels[0];
	for (int i = 1; i < numSamples; i++)
		if (labels[i] > numClasses)
			numClasses = labels[i];

	train(data, labels, numSamples, numFeatures);
}


double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples,
	const int numFeatures, const bool* usedSamples, const int featureId) {

	int* classCounts = giveClassCounts(numSamples, usedSamples);
	double parentEntropy = calculateEntropy(classCounts, numClasses);
	if (parentEntropy == 0) return 0;

	//calculate usedSample for that splits false branch
	bool* usedSamplesLeft = new bool[numSamples];
	for (int i = 0; i < numSamples; i++) {
		usedSamplesLeft[i] = false;
		if (data[i][featureId] == false && usedSamples[i] == true) {
			usedSamplesLeft[i] = true;
		}
	}
	//take classCounts
	int* classCountsLeft = giveClassCounts(numSamples, usedSamplesLeft);
	//call entropy
	double leftEntropy = calculateEntropy(classCountsLeft, numClasses);

	//For right,true, branch
	//calculate usedSample for that splits false branch
	bool* usedSamplesRight = new bool[numSamples];
	for (int i = 0; i < numSamples; i++) {
		usedSamplesRight[i] = false;
		if (data[i][featureId] == true && usedSamples[i] == true) {
			usedSamplesRight[i] = true;
		}
	}


	//take classCounts
	int* classCountsRight = giveClassCounts(numSamples, usedSamplesRight);
	//call entropy
	double rightEntropy = calculateEntropy(classCountsRight, numClasses);

	//To Calculate Probabilty
	int leftCount = 0;
	int rightCount = 0;
	
	for (int i = 0; i < numClasses; i++)
	{
		leftCount += classCountsLeft[i];
	}

	for (int i = 0; i < numClasses; i++)
	{
		rightCount += classCountsRight[i];
	}

	double parentCount = (double) leftCount + rightCount;

	double gain = parentEntropy - ((leftEntropy * (leftCount / parentCount)) + (rightEntropy * (rightCount / parentCount)));

	delete[] classCounts;
	delete[] classCountsLeft;
	delete[] classCountsRight;
	delete[] usedSamplesLeft;
	delete[] usedSamplesRight;
		  
	return gain;
}


int* DecisionTree::giveClassCounts(const int numSamples, const bool* usedSamples) {

	int* classCounts = new int[numClasses];

	for (int j = 0; j < numClasses; j++) {
				classCounts[j] = 0;
	}


	for (int j = 0; j < numClasses; j++) {
		for (int i = 0; i < numSamples; i++) {
			if (usedSamples[i] == true && labels[i] == j + 1)
			{
				classCounts[j] += 1;
			}
		}
	}
	
	return classCounts;
}


void DecisionTree::build(DecisionTreeNode*& root, const bool** data, bool* usedSamples, bool* usedFeatureIds, int featureId, bool branch) {

	double* gains = new double[numFeatures];

	for (int i = 0; i < numFeatures; i++) {
		if (usedFeatureIds[i] == true) //if usedId is true then use it
			gains[i] = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples, i);
		else
			gains[i] = -1;
		cout << "gain for id:" << i << "=" << gains[i] << endl;
	}

	double maxGain = 0;
	for (int i = 0; i < numFeatures; i++)
		if (gains[i] > maxGain)
			maxGain = gains[i];

	cout << "max gain:" << maxGain << endl;


	if (maxGain == 0) //stop when leaf node reached, that is when the max gain = 0
	{
		int classN;
		for (classN = 0; classN < numSamples; classN++) {
			if (usedSamples[classN] == true)
				break;
		}
		root = new DecisionTreeNode();
		root->data = labels[classN];
		root->right = NULL;
		root->left = NULL;
		root->setIsLeaf(true); //set as leaf node
		return;
	}

	if (root == NULL)
		root = new DecisionTreeNode();
 
	for (int i = 0; i < numFeatures; i++) {
		if (maxGain == gains[i]) {
			root->data = i;
			featureId = i;  //featureId
			break;			
		}
	}

	delete[] gains;

	root->right = NULL;
	root->left = NULL;

	//calculate usedSample for that splits false branch
	bool* usedSamplesLeft = new bool[numSamples];
	for (int i = 0; i < numSamples; i++) {
		usedSamplesLeft[i] = false;
		if (data[i][featureId] == false && usedSamples[i] == true) {
			usedSamplesLeft[i] = true;
		}
	}

	//usedFeaturesId calculation, if that feature is used make it false not to use again
	bool* usedFeatureIdsLeft = new bool[numFeatures];
	for (int i = 0; i < numFeatures; i++) {
		usedFeatureIdsLeft[i] = true;
		if ((featureId == i && branch == false) || usedFeatureIds[i] == false)
			usedFeatureIdsLeft[i] = false; //-1 means feature used, dont use it again 
	}


	build(root->left, data, usedSamplesLeft, usedFeatureIdsLeft,featureId,false);

	delete[] usedFeatureIdsLeft;
	delete[] usedSamplesLeft;

	//For right,true, branch
	//calculate usedSample for that splits false branch
	bool* usedSamplesRight = new bool[numSamples];
	for (int i = 0; i < numSamples; i++) {
		usedSamplesRight[i] = false;
		if (data[i][featureId] == true && usedSamples[i] == true) {
			usedSamplesRight[i] = true;
		}
	}

	/*
	//usedFeaturesId calculation
	int* usedFeatureIdsRight = new int[numFeatures];
	for (int i = 0; i < numFeatures; i++) {
		if (featureId == i && branch == true)
			usedFeatureIdsRight[i] = -1; //-1 means feature used, dont use it again 
	}
	*/

	//usedFeaturesId calculation, if that feature is used make it false not to use again
	bool* usedFeatureIdsRight = new bool[numFeatures];
	for (int i = 0; i < numFeatures; i++) {
		usedFeatureIdsRight[i] = true;
		if ((featureId == i && branch == true) || usedFeatureIds[i] == false)
			usedFeatureIdsRight[i] = false;  //false means feature used, dont use it again 
	}

	build(root->right, data, usedSamplesRight, usedFeatureIdsRight, featureId, true);

	delete[] usedFeatureIdsRight;
	delete[] usedSamplesRight;

	return;
}


void DecisionTree::preorder(DecisionTreeNode* root, int level) {
	if (root == NULL)
		return;

	for (int i = 0; i < level; i++)
		cout << "\t";
	if (root->getIsLeaf())
		cout << "class = ";
	else
		cout << "featureId = ";

	cout << root->data << endl;

	level++;

	preorder(root->left, level);
	preorder(root->right, level);
}


void DecisionTree::print() { //preorder printing
	cout << endl;
	int level = 0;
	preorder(rootptr, level);
}


double DecisionTree::test(const string fileName, const int numSamples) {

	ifstream inputFileStream(fileName.c_str());

	const bool** testData = new const bool* [numSamples];
	int* testLabels = new int[numSamples];
	const int testNumSamples = numSamples;
	for (int i = 0; i < numSamples; i++) {
		testData[i] = new bool[numFeatures];
	}

	int rowT = 0;
	int xT = 0;

	while (rowT < testNumSamples && testNumSamples <= this->numSamples) {
		for (int i = 0; i < numFeatures; i++) { //to avoid errors
			inputFileStream >> xT;
			if (xT == 0)
				const_cast<bool&>(testData[rowT][i]) = false;
			else
				const_cast<bool&>(testData[rowT][i]) = true;
		}

		inputFileStream >> testLabels[rowT];
		rowT++;
	}
	double accuracy = 0;
	accuracy = test(testData, testLabels, testNumSamples);
	return accuracy;

}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples) {
	//call predict for each row
	int treeClass;
	double correct = 0;
	int tot = 0;
	for (int i = 0; i < numSamples; i++) {

		treeClass = predict(data[i]);

		//check if its true
		if (treeClass == labels[i])
			correct++;
		tot++;
	}
	return correct / tot;
}

int DecisionTree::predict(const bool* data){
	DecisionTreeNode* ptr = rootptr;
	int className;
	while (ptr != NULL) {

		className = ptr->data;
		
		if (data[ptr->data] == false)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	return className;
}

DecisionTreeNode* DecisionTree::getRoot() {
	return rootptr;
}

void DecisionTree::setRoot(DecisionTreeNode* rootN) {
	rootptr = rootN;
}

