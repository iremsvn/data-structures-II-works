#include "Queue.h"
#include <cstddef>



Queue::Queue() : backPtr(NULL), frontPtr(NULL) {

}



Queue::~Queue() {
	while (!isEmpty())
		dequeue();
}


bool Queue::isEmpty() const {

	return backPtr == NULL;

}



bool Queue::enqueue(QueueItemType newItem) {


	QueueNode* newPtr = new QueueNode;


	newPtr->item = newItem;
	newPtr->next = NULL;


	if (isEmpty())  
		frontPtr = newPtr;
	else             
		backPtr->next = newPtr;

	backPtr = newPtr;  

	return true;
}




bool Queue::dequeue() {

	if (isEmpty())
		return false;

	else {
		
		QueueNode* tempPtr = frontPtr;

		if (frontPtr == backPtr) {   
			frontPtr = NULL;
			backPtr = NULL;
		}
		else
			frontPtr = frontPtr->next;

		tempPtr->next = NULL;  
		delete tempPtr;
		return true;
	}
}



bool Queue::dequeue(QueueItemType& queueFront) {

	if (isEmpty())
		return false;

	else {
	
		queueFront = frontPtr->item;
		dequeue(); 

		return true;
	}

}



bool Queue::getFront(QueueItemType& queueFront)const {

	if (isEmpty())
		return false;

	else {
		
		queueFront = frontPtr->item;

		return true;
	}

}





