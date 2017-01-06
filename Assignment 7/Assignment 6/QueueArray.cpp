// BY: Omer Khan
// CSC 2200 
// Lab 6
#include "QueueArray.h"

template <typename DataType>
QueueArray<DataType>::QueueArray(int maxNumber)
{
	maxSize = maxNumber;
	this->dataItems = new DataType[maxSize];
	front = -1;
	back = -1;

}

template <typename DataType>
QueueArray<DataType>::QueueArray(const QueueArray& other)
{
	dataItems = new DataType[maxSize];

	for (int i = 0; i <= maxSize - 1; i++)
	{
		dataItems[i] = other.dataItems[i];
	}

}


template <typename DataType>
QueueArray<DataType>& QueueArray<DataType>::operator=(const QueueArray& other)
{
	if (maxSize < other.maxSize)
	{
		delete[] dataItems;
		dataItems = new dataType[other.maxSize];
	}

	maxSize = other.maxSize;
	this->front = other.front;

	for (int i = 0; i <= this->maxSize - 1; i++)
	{
		dataItems[i] = other.dataItems[i];
	}

	return *this;
}

template <typename DataType>
QueueArray<DataType>::~QueueArray()
{
	this->clear();
}


template <typename DataType>
void QueueArray<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	if (this->isFull())
		throw logic_error("Queue is Full.");
	if (this->isEmpty())
	{
		dataItems[back + 1] = newDataItem;
		back = (++back) % maxSize;
		front++;
	}
	else if (back == 7 && !isFull())
	{
		back = 0;
		dataItems[back] = newDataItem;
	}
	else {
		back = (++back) % maxSize;
		dataItems[back] = newDataItem;
	}

}

template <typename DataType>
DataType QueueArray<DataType>::dequeue() throw (logic_error)
{
	if (this->isEmpty())
		throw logic_error("Queue is empty. ");

	if (getLength() == 1)
	{
		DataType temp = dataItems[this->front];
		clear();
		return temp;
	}

	else {
		DataType temp;
		temp = dataItems[this->front];
		front++;
		return temp;
	}
}

template <typename DataType>
void QueueArray<DataType>::clear()
{
	front = -1;
	back = -1;
}

template <typename DataType>
bool QueueArray<DataType>::isEmpty() const
{
	return (front == -1);
}

template <typename DataType>
bool QueueArray<DataType>::isFull() const
{
	return (getLength()  == this->maxSize);
}

template <typename DataType>
void QueueArray<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
	if (isFull())
		throw logic_error("Queue is Full.");
	else {
		if (isEmpty()) 
		{
			front = 0;
			back = 0;
		}
		else {
			front--;
			if (front < 0)
				front = (maxSize - 1);
		}

		dataItems[front] = newDataItem;
	}

}

template <typename DataType>
DataType QueueArray<DataType>::getRear() throw (logic_error)
{
	int cursor = -1;
	if (isEmpty()) {
		throw logic_error("Queue is Empty.");
	}
	else {
		cursor = back;
		if (front == back)
		{
			front = -1;
			back = -1;
		}
		else 
		{
			--back;
			if (back < 0) 
				back = (maxSize - 1);
		}

		return dataItems[cursor];
	}
	
}

template <typename DataType>
int QueueArray<DataType>::getLength() const
{
	if (front > back)
		return (back - front + maxSize + 1);
	else 
		return back - front + 1;
}

//--------------------------------------------------------------------

template <typename DataType>
void QueueArray<DataType>::showStructure() const
// Array implementation. Outputs the data items in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
	int j;   // Loop counter

	if (front == -1)
		cout << "Empty queue" << endl;
	else
	{
		cout << "Front = " << front << "  Back = " << back << endl;
		for (j = 0; j < maxSize; j++)
			cout << j << "\t";
		cout << endl;
		if (back >= front)
			for (j = 0; j < maxSize; j++)
				if ((j >= front) && (j <= back))
					cout << dataItems[j] << "\t";
				else
					cout << " \t";
		else
			for (j = 0; j < maxSize; j++)
				if ((j >= front) || (j <= back))
					cout << dataItems[j] << "\t";
				else
					cout << " \t";
		cout << endl;
	}
}