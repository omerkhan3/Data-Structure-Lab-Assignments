
#include "PriorityQueue.h"

template<typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue(int maxNumber): Heap(maxNumber)
{
}

template<typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator>::enqueue(const DataType & newDataItem)
{
	insert(newDataItem);
}

template<typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()
{
	return remove();
}





