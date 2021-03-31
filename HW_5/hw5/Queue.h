#pragma once
typedef int QueueItemType;

class Queue {
public:
	Queue();                   
	~Queue();                    

	bool isEmpty() const;
	bool enqueue(QueueItemType newItem);
	bool dequeue();
	bool dequeue(QueueItemType& queueFront);
	bool getFront(QueueItemType& queueFront) const;

private:

	struct QueueNode {
		QueueItemType  item;
		QueueNode* next;
	};
	QueueNode* backPtr;
	QueueNode* frontPtr;
};
