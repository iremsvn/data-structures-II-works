#include <string>
#include "LinkedList.h"
#include "Queue.h"
using namespace std;

class FriendNet {

public:

	FriendNet(const string fileName);
	FriendNet(const FriendNet& aNet);
	~FriendNet();
	void listFriends(const string personName, const int hopNo);
	void displayAverageDegrees();
	void displayDiameters();
	
	

private:
	struct Vertex {
		int id;
		string name;
		int degree; //no of friends
		int componentNum = 0; //assigned new attribute for component number
		LinkedList* friendList = NULL; //list of friends that is adjacent to that vertex
	};


	Vertex* vertex; //adjacency list representation
	int noOfVertex;
	int noOfComponent;
	void BFS(int startingVertex, int* levels);
	void BFSforConnected(int startingVertex, bool* visited, int compNum);
	void connectedComponents();
	int findMax(int* arr, int size); //just finds max int in an array
};