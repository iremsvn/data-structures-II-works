#include <iostream>
#include <fstream>
#include "FriendNet.h"
using namespace std;


FriendNet::FriendNet(const string fileName) : noOfVertex(0), vertex(NULL), noOfComponent(0) {
		ifstream inputFileStream(fileName.c_str());

		if (!inputFileStream) {
			cout << "File Not Found Empty Network Created" << endl;
			vertex = new Vertex[0]; //if file not exist creating empty network
			return;
		}

		int idN;
		int idF; //friendId
		inputFileStream >> noOfVertex;
		vertex = new Vertex[noOfVertex];

		for (int i = 0; i < noOfVertex; i++) {
			inputFileStream >> idN;		//first taking id to put it into corresponding array index
			vertex[idN].id = idN;		//in case of the ids are not sorted in the given file
			inputFileStream >> vertex[idN].name;
			inputFileStream >> vertex[idN].degree;
			vertex[idN].friendList = new LinkedList;
			for (int j = 0; j < vertex[idN].degree; j++) {
				inputFileStream >> idF;
				vertex[idN].friendList->add(idF);
			}
		}

		connectedComponents(); //only called once to find component number of nodes
}



FriendNet::FriendNet(const FriendNet& aNet): noOfVertex(aNet.noOfVertex), noOfComponent(aNet.noOfComponent) {
	if (noOfVertex > 0) {
		vertex = new Vertex[noOfVertex];
		for (int i = 0; i < noOfVertex; i++) {
			vertex[i].componentNum = aNet.vertex[i].componentNum;
			vertex[i].degree = aNet.vertex[i].degree;
			vertex[i].id = aNet.vertex[i].id;
			vertex[i].name = aNet.vertex[i].name;
			vertex[i].friendList = new LinkedList;
			for (int j = 1; j <= aNet.vertex[i].degree; j++) {
				int item = 0;
				aNet.vertex[i].friendList->retrieve(j, item);
				vertex[i].friendList->add(item);
			}
		}
	}
	else {
		vertex = new Vertex[0]; //if empty creating empty network
	}
}



FriendNet::~FriendNet() {
	for (int i = 0; i < noOfVertex; i++) {
		delete vertex[i].friendList;
	}
	delete[]vertex;
}



void FriendNet::connectedComponents()
{
	int compNum = 0;
	bool* visited = new bool[noOfVertex];
	for (int i = 0; i < noOfVertex; i++)
		visited[i] = false;

	for (int i = 0; i < noOfVertex; i++)
	{
		if (visited[i] == false)
		{
			BFSforConnected(i, visited, compNum);
			compNum++;
		}
	}
	noOfComponent = compNum; //assign to private data member
	delete[] visited;
}




void FriendNet::displayAverageDegrees() {
	cout << "There are " << noOfComponent << " connected components. The average degrees are: " << endl;
	for (int i = 0; i < noOfComponent; i++) {
		double sum = 0;
		double count = 0;
		cout << "For component " << i << ": ";
		for (int j = 0; j < noOfVertex; j++) {
			if (vertex[j].componentNum == i) {
				count++;
				sum = sum + vertex[j].degree;
			}
		}
		cout << (double) (sum / count) << endl;
	}
}




void FriendNet::listFriends(const string personName, const int hopNo) {

	for (int i = 0; i < noOfVertex; i++) {
		if (vertex[i].name == personName) {
			if (hopNo <= 0 || vertex[i].degree == 0) {
				cout << "people accessible from " << personName << " within " << hopNo << " hops: " << " NOBODY" << endl;
				return;
			}
			cout << "people accessible from " << personName << " within " << hopNo << " hops: ";
			int* levels = new int[noOfVertex];
			BFS(vertex[i].id, levels);
			int counter = 0;
			for (int j = 0; j < noOfVertex; j++) {
				if (levels[j] > 0 && levels[j] <= hopNo) {
					if (counter != 0)
						cout << ", ";
					cout << vertex[j].name;
					counter++;
				}		
			}
			cout << endl;
			delete[] levels;
			return;
		}
	}
	cout << personName << " does not exist in the network" << endl;
}




void FriendNet::displayDiameters() {
	int diameter;
	cout << "There are " << noOfComponent << " connected components. The diameters are: " << endl;
	for (int i = 0; i < noOfComponent; i++) {
		cout << "For component " << i << ": ";
		int maxLevel = 0;
		diameter = 0;
		for (int j = 0; j < noOfVertex; j++) {
			if (vertex[j].componentNum == i) {
				int* levels = new int[noOfVertex];
				BFS(j, levels);
				maxLevel = findMax(levels, noOfVertex);
				if (maxLevel > diameter)
					diameter = maxLevel;
				delete[] levels;
			}
		}
		cout << diameter << endl;
	}
}

int FriendNet::findMax(int* arr,int size) {
	if (size > 0) {
		int max = arr[0];

		for (int i = 1; i < size; i++)
			if (arr[i] > max)
				max = arr[i];

		return max;
	}
	
	return -1; //invalid case

}



//For Displaying Elements
void FriendNet::BFS(int startingVertex, int* levels)
{
	for (int i = 0; i < noOfVertex; i++)
		levels[i] = -1;
	Queue q;
	bool* visited = new bool[noOfVertex];
	for (int i = 0; i < noOfVertex; i++)
		visited[i] = false;
	q.enqueue(startingVertex);
	levels[startingVertex] = 0;
	visited[startingVertex] = true;

	while (!q.isEmpty()) {
		int currentVertex, i;
		q.getFront(currentVertex);
		for (i = 1; i <= vertex[currentVertex].degree; i++) {
			int adjacentNode;
			vertex[currentVertex].friendList->retrieve(i, adjacentNode);
			if (!visited[adjacentNode]) {
				visited[adjacentNode] = true;
				q.enqueue(adjacentNode);
				levels[adjacentNode] = levels[currentVertex] + 1; //**
			}
		}
		// When there is no unvisited vertex adjacent to the current node
		if (i > vertex[currentVertex].degree) {
			q.dequeue();
		}
	}
	delete[] visited;
}



//For Finding Connected Components
void FriendNet::BFSforConnected(int startingVertex, bool* visited, int compNum)
{
	Queue q;
	q.enqueue(startingVertex);
	visited[startingVertex] = true;
	vertex[startingVertex].componentNum = compNum;
	while (!q.isEmpty()) {
		int currentVertex, i;
		q.getFront(currentVertex);
		for (i = 1; i <= vertex[currentVertex].degree; i++) {
			int adjacentNode;
			vertex[currentVertex].friendList->retrieve(i, adjacentNode);
			if (!visited[adjacentNode]) {
				vertex[adjacentNode].componentNum = compNum;
				visited[adjacentNode] = true;
				q.enqueue(adjacentNode);
			}
		}
		// When there is no unvisited vertex adjacent to the current node
		if (i > vertex[currentVertex].degree) {
			q.dequeue();
		}
	}
}