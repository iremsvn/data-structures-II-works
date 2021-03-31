#pragma once
#include <string>
using namespace std;
class LinkedList {

public:
	LinkedList();
	~LinkedList();
	void add(const int id);
	void remove(const int id);
	bool retrieve(int index, int& dataItem) const;
	int getLength() const;

private:

	struct Node {
		int id;
		Node* next;
	};


	Node* head;
	int size;
	Node* find(const int id) const;

	friend class FriendNet;
};
