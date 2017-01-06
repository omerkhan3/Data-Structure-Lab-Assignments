// BY: Omer Khan
// CSC 2200 
// Lab 6
#include "QueueLinked.h"


template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber = Queue<DataType>::MAX_QUEUE_SIZE)
{
	front = NULL;
	back = NULL;
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{
	operator=(other);
}

template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{

		clear();
		if (other.isEmpty()) {
			return *this;
		}
		else {
			while (other_cursor != NULL) {
				enqueue(other_cursor->dataItem);
				other_cursor = other_cursor->next;
			}
		}
}



template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
	clear();
}

template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	QueueNode* new_node = NULL;
	new_node = new QueueNode(newDataItem, NULL);

		if (isEmpty()) {
			front = new_node;
			back = new_node;
		}
		else {
			back->next = new_node;
			back = new_node;
		}
		new_node = NULL;
}


template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
	QueueNode* deletedCursor = NULL;
	DataType deletedData;

	if (isEmpty()) {
		cout << "Queue is Empty." << endl;
	}
	else {
		deletedCursor = front;
		deletedData = front->dataItem;

		if (front == back) {
			front = NULL;
			back = NULL;
		}
		else {
			front = front->next;
		}


		return deletedData;
	}
}

template <typename DataType>
void QueueLinked<DataType>::clear()
{
	while (!isEmpty()) 
		dequeue();
}

template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	return (front == NULL);
}

template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	return false;
}

template <typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
	QueueNode *node = new QueueNode(newDataItem, NULL);
	if (isEmpty()) {
		front = node;
		back = node;
	}
	else {
		node->next = front;
		front = node;
	}
}

template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("Queue is Empty");
	}
	else
	{
		QueueNode *deleted = back;
		DataType data = back->dataItem;

		if (front == back) {
			front = NULL;
			back = NULL;
		}
		else {
			QueueNode *previous = front;

			while (previous->next != back) 
				previous = previous->next;

			back = previous;
			back->next = NULL;
		}


		return data;
	}
}

template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
	QueueNode* cursor = NULL;
	int length = 0;

	for (cursor = front; cursor != NULL;  cursor = cursor->next)
	{
		length++;
	}
	return length;
}

template <typename DataType>
void QueueLinked<DataType>::showStructure() const
{
	QueueNode *p;   // Iterates through the queue

	if (isEmpty())
		cout << "Empty queue" << endl;
	else
	{
		cout << "Front\t";
		for (p = front; p != 0; p = p->next)
		{
			if (p == front)
			{
				cout << '[' << p->dataItem << "] ";
			}
			else
			{
				cout << p->dataItem << " ";
			}
		}
		cout << "\trear" << endl;
	}
}