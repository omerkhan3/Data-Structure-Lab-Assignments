
#include "Heap.h"


template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::Heap ( int maxNumber = DEFAULT_MAX_HEAP_SIZE )
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::Heap ( const Heap& other )
{
	maxSize = other.maxSize;
	size = other.maxSize;
	dataItems = new DataType[maxSize];
	for (int i = 0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>& Heap<DataType,KeyType,Comparator>::operator= ( const Heap& other )
{
	if (this == &other)
	{
		return *this;    // Self-assignment
	}

	if (other.maxSize > maxSize)
	{
		delete[] dataItems;
		dataItems = new DataType[other.maxSize];
	}
	maxSize = other.maxNumber;
	size = other.size;
	for (int i = 0; i<size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}

	return *this;
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::~Heap ()
{
	delete[] dataItems;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::insert ( const DataType &newDataItem ) throw ( logic_error )
{
	if (isFull())
		throw logic_error("Heap is Full.");

		int j, parentj;


		for (j = size, parentj = (j - 1) / 2;
			j > 0 && comparator(newDataItem.getPriority(), dataItems[parentj].getPriority());
			j = parentj, parentj = (j - 1) / 2)
		{
			dataItems[j] = dataItems[parentj];
		}

		dataItems[j] = newDataItem;
		size++;
	

	

}

template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType,KeyType,Comparator>::remove () throw ( logic_error )
{
	if (isEmpty())
			throw logic_error("Heap is empty");

		DataType max = dataItems[0];
		DataType temp;
		int index = 0;
		dataItems[index] = dataItems[size-1];
		while( index < size )
			{
			if (comparator(dataItems[2 * index + 1].getPriority(), dataItems[2 * index + 2].getPriority()))
				{
					if (2 * index + 1 < size)
						swap(dataItems[index], dataItems[2 * index + 1]);

					index = 2 * index + 1;
				}

			else
				{
					if (2 * index + 2 < size)
						swap(dataItems[index], dataItems[2 * index + 2]);

					index = 2 * index + 2;
				}
		}
		size --;
		return max;

}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::clear ()
{
	size = 0;
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isEmpty () const
{
	if (size == 0)
		return true;
	else 
		return false;
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isFull () const
{
	if (this->size == this->maxSize)
		return true;


	return false;
}

#include "show11.cpp"

template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::writeLevels() const
{
	int cursor = 0;
	int currentLevelCount = 0;
	int numInLevel = 1;

	if (size != 0)
	{
		while (cursor < size)
		{
			cout << dataItems[cursor].getPriority();
			currentLevelCount++;

			if (currentLevelCount >= numInLevel)
			{
				currentLevelCount = 0;
				numInLevel *= 2;
				cout << endl;
			}
			else
			{
				cout << ' ';
			}
			cursor++;
		}
	}
	else
	{
		cout << "Empty heap.";
	}
}

