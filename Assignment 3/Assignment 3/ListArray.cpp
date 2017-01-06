
#include "listArray.h"

template < typename DataType >
List<DataType>::List(int maxNumber) : maxSize(maxNumber), size(0), cursor(-1)
{
	dataItems = new DataType[maxSize];

}

template < typename DataType >
List<DataType>::List(const List& source) : maxSize(source.maxSize), size(source.maxSize), cursor(source.cursor)
{
	dataItems = new DataType[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		dataItems[i] = source.dataItems[i];
	}
}

template < typename DataType >
List<DataType>& List<DataType>::operator= (const List& source)
{
	if (this->maxSize < source.maxSize)
	{
		delete[] dataItems;
		dataItems = new DataType[maxSize];
	}

	maxSize = source.maxSize;
	size = source.maxSize;
	cursor = source.cursor;

	for (int j = 0; j < size; j++)
	{
		dataItems[j] = source.dataItems[j];
	}
	return *this;
}

template < typename DataType >
List<DataType>::~List()
{
	delete[] dataItems;
}

template < typename DataType >
void List<DataType>::insert(const DataType& newDataItem) // add a number at the cursor, shift everything else to the right. 
throw (logic_error)
{
	if (isFull() == true) throw logic_error("List is Full.");

	if (size != 0)
	{
		for (int i = size; i > cursor + 1; i--)
		{
			dataItems[i] = dataItems[i - 1];
		}

		dataItems[++cursor] = newDataItem;
		size = size + 1;
	}

	else if (isEmpty())
	{
		dataItems[0] = newDataItem;
		++cursor;
		size++;
	}



}

template < typename DataType >
void List<DataType>::remove() throw (logic_error)
{
	if (isEmpty()) throw logic_error("List is empty.");
	else if (size == 1)
		clear();
	else if (cursor + 1 == size)
	{
		cursor = 0;
		size--;
	}
	else 
	{

		for (int i = cursor; i < size - 1; i++)
		{
			dataItems[i] = dataItems[i + 1];
		}


		size--;
	}
}

template < typename DataType >
void List<DataType>::replace(const DataType& newDataItem)
throw (logic_error)
{
	if (isEmpty())
		throw logic_error("List is empty.");
	dataItems[cursor] = newDataItem;
}

template < typename DataType >
void List<DataType>::clear()
{
	if (size > 0) {
		int s = size;

		for (int x = s; x >= 0; x--) {
			dataItems[x] = 0;
		}
		size = 0;
		cursor = 0;
	}
}

template < typename DataType >
bool List<DataType>::isEmpty() const
{
	return (size == 0);
}

template < typename DataType >
bool List<DataType>::isFull() const
{
	return (size == maxSize);
}

template < typename DataType >
void List<DataType>::gotoBeginning()
throw (logic_error)
{
	if (cursor != -1) {
		cursor = 0;
	}
	else {
		throw logic_error("Already at the beginning.");
	}
}

template < typename DataType >
void List<DataType>::gotoEnd()
throw (logic_error)
{
	if (size != 0) {
		cursor = size - 1;
	}
	else {
		throw logic_error("Already at the end.");
	}
}

template < typename DataType >
bool List<DataType>::gotoNext()
throw (logic_error)
{
	if (cursor == size) {
		throw logic_error("Cannot go to next, already at the end.");
		return false;
	}
	else if (cursor != size - 1) {
		cursor++;
		return true;
	}
	else {
		return false;
	}
}

template < typename DataType >
bool List<DataType>::gotoPrior()
throw (logic_error)
{
	if (cursor == -1) {
		throw logic_error("Cannot go back, already at the beginning.");
		return false;
	}
	else {
		cursor--;
		return true;
	}
}

template < typename DataType >
DataType List<DataType>::getCursor() const
throw (logic_error)
{
	if (cursor < 0) {
		throw ("Nothing to retrieve.");
	}
	else {
		return dataItems[cursor];
	}
}

#include "show3.cpp"

template < typename DataType >
void List<DataType>::moveToNth(int n)
throw (logic_error)
{
	if (n > maxSize || n < 0)
		throw ("Out of Bounds.");
	else
		dataItems[n] = dataItems[cursor];


}

template < typename DataType >
bool List<DataType>::find(const DataType& searchDataItem)
throw (logic_error)
{
	for (int i = cursor; i < size; i++)
	{
		if (dataItems[i] == searchDataItem)
			return true;
	}
	return false;
}