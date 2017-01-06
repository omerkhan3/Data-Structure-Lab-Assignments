//--------------------------------------------------------------------
//
//  Laboratory 11, Programming Exercise 2                  heapsort.cs
//
//  (Shell) heapSort() function
//
//--------------------------------------------------------------------


template < typename DataType >
void moveDown ( DataType dataItems [], int root, int size )

// Restores the binary tree that is rooted at root to a heap by moving
// dataItems[root] downward until the tree satisfies the heap property.
// Parameter size is the number of data items in the array.

{
	// YOUR CODE GOES HERE
	// Hint: you may want to use some of the variables declared above (but you don't have to)
	// Hint: call getPriority() to get the priority of a data item (e.g. insertDataItem.getPriority())

	int child;
	DataType tmp;
	for (tmp = dataItems[root]; 2 * root + 1 < size; root = child)
	{
		child = 2 * root + 1;
		if (child != size - 1 && dataItems[child].getPriority() < dataItems[child + 1].getPriority())
			child++;
		if (tmp.getPriority() < dataItems[child].getPriority())
			dataItems[root] = dataItems[child];
		else
			break;
	}
	dataItems[root] = tmp;
}

//--------------------------------------------------------------------

template < typename DataType >
void heapSort ( DataType dataItems [], int size )

// Heap sort routine. Sorts the data items in the array in ascending
// order based on priority.

{
    DataType temp;   // Temporary storage
    int j;     // Loop counter

    // Build successively larger heaps within the array until the
    // entire array is a heap.

    for ( j = (size-1)/2 ; j >= 0 ; j-- )
        moveDown(dataItems,j,size);

    // Swap the root data item from each successively smaller heap with
    // the last unsorted data item in the array. Restore the heap after
    // each exchange.

    for ( j = size-1 ; j > 0 ; j-- )
    {
        temp = dataItems[j];
        dataItems[j] = dataItems[0];
        dataItems[0] = temp;
        moveDown(dataItems,0,j);
    }
}

