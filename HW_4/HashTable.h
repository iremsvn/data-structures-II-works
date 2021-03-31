/*
*irem seven
*21734269
*Section1
*Assigment 4
*/

#pragma once
#include <iostream>
#include <string>
#include <fstream>

enum CollisionStragedy {LINEAR, QUADRACTIC, DOUBLE};

class HashTable {
	
public:
	HashTable(const int tableSize, const CollisionStragedy option);
	~HashTable();
	bool insert(const int item);
	bool remove(const int item);
	bool search(const int item, int& numProbes);
	void display();
	void analyze(double& numSuccProbes, double& numUnsuccProbes);
	void parseText(std::string fileName);

private:
	enum LocationType { EMPTY, OCCUPIED, DELETED };

	struct hashNode {
		int key;
		LocationType type = EMPTY;
	};

	hashNode* hashTable;
	int tableSize;
	CollisionStragedy collisionStragedy;
	int* elements; //used for analysing just includes integers that are inserted
	int elementsSize;
	int hash(int key);
	int f(int i);
};
