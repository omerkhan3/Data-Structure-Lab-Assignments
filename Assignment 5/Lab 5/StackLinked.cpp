// by: Omer Khan
#include "StackLinked.h"

template <typename DataType>
StackLinked<DataType>::StackLinked(int maxNumber)
{
	top = NULL;
}

template <typename DataType>
StackLinked<DataType>::StackLinked(const StackLinked& other)
{
	operator=(other);
}

template <typename DataType>
StackLinked<DataType>& StackLinked<DataType>::operator=(const StackLinked& other)
{
	clear();
	if (!other.isEmpty()) {
		top = new StackNode(other.top->dataItem, 0);
		StackNode *otherTemp = other.top->next;
		StackNode *thisTemp = 0, *thisPrevious = top;

		while (otherTemp != 0)
		{
			thisTemp = new StackNode(otherTemp->dataItem, 0);
			thisPrevious->next = 0;
			thisPrevious = top->next;
			otherTemp = top;
		}
	}

	return *this;

}


template <typename DataType>
StackLinked<DataType>::~StackLinked()
{
	clear();
}

template <typename DataType>
void StackLinked<DataType>::push(const DataType& newDataItem) throw (logic_error)
{
	if (isFull())
		throw logic_error("List is Full");


	StackNode *temp;
	temp = new StackNode(newDataItem, top);
	top = temp;


}

template <typename DataType>
DataType StackLinked<DataType>::pop() throw (logic_error)
{
	if (isEmpty())
		throw logic_error("Linked List is Empty.");

	DataType newTop = top->dataItem;
	top = top->next;
	return newTop;

}

template <typename DataType>
void StackLinked<DataType>::clear()
{
	this->top = NULL;
}

template <typename DataType>
bool StackLinked<DataType>::isEmpty() const
{
	return (top == NULL);
}

template <typename DataType>
bool StackLinked<DataType>::isFull() const
{
	return false;
}

template <typename DataType>
void StackLinked<DataType>::showStructure() const
{
	if (isEmpty())
	{
		cout << "Empty stack" << endl;
	}
	else
	{
		cout << "Top\t";
		for (StackNode* temp = top; temp != 0; temp = temp->next) {
			if (temp == top) {
				cout << "[" << temp->dataItem << "]\t";
			}
			else {
				cout << temp->dataItem << "\t";
			}
		}
		cout << "Bottom" << endl;
	}

}