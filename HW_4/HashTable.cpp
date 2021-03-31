/*
*irem seven
*21734269
*Section1
*Assigment 4
*/

#include "HashTable.h"
using namespace std;


HashTable::HashTable(const int tableSize = 0, const CollisionStragedy option = LINEAR ): tableSize(tableSize),
				     collisionStragedy(option), hashTable(NULL), elements(NULL), elementsSize(0) {
	if (tableSize > 0) {
		hashTable = new hashNode[tableSize];
		elements = new int[tableSize];
	}
}

HashTable::~HashTable() {
	delete[]hashTable;
}

int HashTable::hash(int key) {
	return (key % tableSize);
}

int HashTable::f(int i) {
	if (collisionStragedy == LINEAR)
		return i;
	else if (collisionStragedy == QUADRACTIC)
		return (i * i);
	else if (collisionStragedy == DOUBLE) {
		int reverse = 0, r;
		while (i != 0)
		{
			r = i % 10;
			reverse = reverse * 10 + r;
			i /= 10;
		}
		return reverse;
	}
}

bool HashTable::insert(const int item) {
	if (elementsSize == tableSize)
		return false;
	int index = hash(item);
	if (collisionStragedy != DOUBLE) {
		for (int i = 0; i < tableSize; i++) {
			if (hashTable[hash(index + f(i))].type != OCCUPIED) {
				hashTable[hash(index + f(i))].key = item;
				hashTable[hash(index + f(i))].type = OCCUPIED;
				elements[elementsSize - 1] = item;
				elementsSize++;
				return true;
			}
		}
		return false;
	}
	else {
		int j = f(item);
		for (int i = 0; i < tableSize; i++) {
			if (hashTable[hash(index + (i * j))].type != OCCUPIED) {
				hashTable[hash(index + (i * j))].key = item;
				hashTable[hash(index + (i * j))].type = OCCUPIED;
				elements[elementsSize - 1] = item;
				elementsSize++;
				return true;
			}
		}
		return false;
	}
}

bool HashTable::remove(const int item) {
	int index = hash(item);
	if (collisionStragedy != DOUBLE) {
		int i = 0;
		while (hashTable[hash(index + f(i))].type != EMPTY) {
			if (hashTable[hash(index + f(i))].key == item && hashTable[hash(index + f(i))].type == OCCUPIED) {
				hashTable[hash(index + f(i))].type = DELETED;
				elementsSize--;
				return true;
			}
			

			if (elementsSize == tableSize)
			{
				if (i == elementsSize)
					return false;
			}
			i++;
		}
		return false;
	}
	else {
		int j = f(item);
		int i = 0;
		while(hashTable[hash(index + (i * j))].type != EMPTY) {
			if (hashTable[hash(index + (i * j))].key == item && hashTable[hash(index + (i * j))].type == OCCUPIED) {
				hashTable[hash(index + (i * j))].type = DELETED;
				elementsSize--;
				return true;
			}
			
			if (elementsSize == tableSize)
			{
				if (i == elementsSize)
					return false;
			}
			i++;
		}
		return false;
	}
}

bool HashTable::search(const int item, int& numProbes) {
	int index = hash(item);
	numProbes = 0;
	if (collisionStragedy != DOUBLE) {
		for (int i = 0; i < tableSize; i++) {
			numProbes++;
			if (hashTable[hash(index + f(i))].type == EMPTY) {
				return false;
			}
			if (hashTable[hash(index + f(i))].type == OCCUPIED && hashTable[hash(index + f(i))].key == item) {
				return true;
			}
		}
		return false;
	}
	else {
		int j = f(item);
		for (int i = 0; i < tableSize; i++) {
			numProbes++;
			if (hashTable[hash(index + (i * j))].type == EMPTY) {
				return false;
			}
			if (hashTable[hash(index + (i * j))].type == OCCUPIED && hashTable[hash(index + (i * j))].key == item) {
				return true;
			}
		}
		return false;
	}
}


void HashTable::display() {
	for (int i = 0; i < tableSize; i++) {
		cout << i << ": ";
		if (hashTable[i].type == OCCUPIED)
			cout << hashTable[i].key;
		cout << endl;
	}
}


void HashTable::analyze(double& numSuccProbes, double& numUnsuccProbes) { //return avg. no of probes
	int probeNumber;
	double totProbeNum = 0;
	for (int i = 0; i < elementsSize; i++) {
		search(elements[i], probeNumber);
		totProbeNum = totProbeNum + probeNumber;
	}
	numSuccProbes = totProbeNum / elementsSize;
	
	//unsuccessfull 
	if (collisionStragedy == DOUBLE) {
		numUnsuccProbes = -1;
		return;
	}

	totProbeNum = 0;
	for (int i = 0; i < tableSize; i++) {
		probeNumber = 0;
		int nonExistNum = i;
			while (search(nonExistNum, probeNumber)) {
				nonExistNum = nonExistNum + tableSize;
			}
			totProbeNum += probeNumber; //unsuccedfull Probe added
	}
	numUnsuccProbes = totProbeNum / tableSize;
}


void HashTable::parseText(std::string fileName) {
	ifstream inputFileStream(fileName.c_str());
	string operation;
	int item;
	int probeNo = 0;
	while (inputFileStream >> operation >> item) {

		//** do operation
		if (operation == "I") {
			if (insert(item))
				cout << item << " inserted" << endl;
			else
				cout << item << " not inserted" << endl;
		}
		if (operation == "R") {
			if (remove(item))
				cout << item << " removed" << endl;
			else
				cout << item << " not removed" << endl;
		}
		if (operation == "S") {
			if (search(item, probeNo))
				cout << item << " found after " << probeNo << " probes" << endl;
			else
				cout << item << " not found after " << probeNo << " probes" << endl;
		}
	}
}


