#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList():head(NULL), size(0) {
	
}


LinkedList::~LinkedList() {
	while (size != 0) {
		remove(head->id);
	}
	head = NULL;
}



void LinkedList::add(const int id) {

	if (find(id) == NULL) {
		Node* newPtr = new Node;
		newPtr->id = id;
		newPtr->next = NULL;
		if (size == 0) {
			head = newPtr;
			size++;
			return;
		}
		Node* prev = head;
		while (prev->next != NULL) {
			prev = prev->next;
		}
		prev->next = newPtr;
		size++;
		return;
	}
	cout << "Person Already Exist" << endl;
}


void LinkedList::remove(const int id) {
	Node* ptr = find(id);
	if (ptr == NULL) {
		return;
	}
	if (head == ptr) {
		head = ptr->next;
	}
	else{
		Node* prev = head;
		while (prev->next != ptr) {
			prev = prev->next;
		}
		prev->next = ptr->next;
	}
	delete ptr;
	size--;
}


LinkedList::Node* LinkedList::find(const int id) const {
	Node* cur = head;
	for (int i = 0; i < size; i++) {
		int idCur = cur->id;
		if (id == idCur) {   
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}


int LinkedList::getLength() const {
	return size;
}


bool LinkedList::retrieve(int index, int& dataItem) const {
	if (index > size)
		return false;
	Node* cur = head;
	for (int i = 1; i < index; i++) {
		cur = cur->next;
	}
	dataItem = cur->id;
	return true;
}