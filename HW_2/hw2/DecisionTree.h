/**
*Author: Ýrem Seven
*ID: 21704269
*Section: 1
*Assignment: 2
*/


#ifndef __DECISION_TREE
#define __DECISION_TREE
#include "DecisionTreeNode.h"
#include <cstddef>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

class DecisionTree {
public:
	DecisionTree();
	double calculateEntropy(const int* classCounts, const int numClasses);
	void train(const string fileName, const int numSamples, const int numFeatures);
	double calculateInformationGain(const bool** data, const int* labels, const int numSamples,
									const int numFeatures, const bool* usedSamples, const int featureId);
	void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
	void print();
	double test(const string fileName, const int numSamples);
	double test(const bool** data, const int* labels, const int numSamples);
	int predict(const bool* data);

	DecisionTreeNode* getRoot(); 
	void setRoot(DecisionTreeNode* rootN);

private:
	void build(DecisionTreeNode*& root, const bool** data, bool* usedSamples, bool* usedFeatureIds, int featureId, bool branch);
	int* giveClassCounts(const int numSamples, const bool* usedSamples);
	void preorder(DecisionTreeNode* ptr, int level);

	DecisionTreeNode* rootptr;
	const bool** data;
    int numSamples;  //row
	int numFeatures; //col
	int* labels; //sample class names
	int numClasses; //for entropy calculated in train parse version
};

#endif