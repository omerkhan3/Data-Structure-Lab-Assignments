
#include "ListLinked.h"

// ListNode member functions

template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
	this->dataItem = nodeData;
	this->next = nextPtr;
}

// List member functions

template <typename DataType>
List<DataType>::List(int ignored = 0)
{
	head = 0;
	cursor = 0;
}


template <typename DataType>
List<DataType>::List(const List& other)
{
	ListNode* copy = other.head;

	while (copy != NULL) {
		this->dataItem = copy->dataItem;
		this->next = copy->next;
		gotoNext();
		copy = copy->next;
	}
	*this = other;
}

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
	ListNode* copy = other.head;
	while (copy != NULL) {
		insert(copy->dataItem);
		gotoNext();
		copy = copy->next;
	}
	return *this;
}

template <typename DataType>
List<DataType>::~List()
{
	clear();
}

template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty())
	{
		head  = new ListNode(newDataItem, 0);
		cursor = head;
		
	}
	else
	{
		 cursor->next = new ListNode(newDataItem, cursor->next);
		 cursor = cursor->next;
	}


}

template <typename DataType>
void List<DataType>::remove() throw (logic_error)
{
	ListNode* Node;
	if (isEmpty()) {
		cout << "Cannot remove from empty list." << endl;
	}
	else if (cursor == head) {
		Node = head;
		head = head->next;
		gotoNext();
		delete Node;
	}
	else {
		ListNode* previous;
		Node = cursor;
		previous = head;
		while (previous->next != cursor) {
			previous = previous->next;
		}
		if (cursor->next != NULL)
			cursor = cursor->next;
		else
			cursor = head;
		previous->next = Node->next;
		delete Node;
		Node = NULL;
	}
	

}

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty()) throw logic_error("list is empty.");
	if (head != NULL)
		cursor->dataItem = newDataItem;
}

template <typename DataType>
void List<DataType>::clear()
{
	if (isEmpty()) {
		cout << "List is already empty!" << endl;
	}
	else {
		cursor = head;
		ListNode *Node;
		while (cursor != NULL) {
			Node = head;
			head = head->next;
			cursor = cursor->next;
			delete Node;
		}
		head = NULL;
		cursor = NULL;
	}


}

template <typename DataType>
bool List<DataType>::isEmpty() const
{
	return head == 0;
}

template <typename DataType>
bool List<DataType>::isFull() const
{
	return false;
}

template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
	cursor = head;
}

template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
	while (cursor->next != NULL)
	{
		cursor = cursor->next;
	}
}

template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
	if (cursor -> next!= NULL)
	{
		cursor = cursor->next;
		return true;
	}

	else 
		return false;
}

template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
	if (cursor != head && head != NULL) {
		ListNode *findPrior = head;
		while (findPrior->next != cursor)
			findPrior = findPrior->next;
		cursor = findPrior;
		return true;
	}
	else
		return false;
}

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
	if (!isEmpty()) {
		return cursor->dataItem;
	}
	else {
		throw logic_error("List is empty.");
	}
}

template <typename DataType>
void List<DataType>::moveToBeginning() throw (logic_error)
{
	if (cursor != head && head != NULL) {
		ListNode* findPrior = head;
		while (findPrior->next != cursor) {
			findPrior = findPrior->next;
		}
		findPrior->next = cursor->next;
		cursor->next = head;
		head = cursor;
	}
}

template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty()) {
		head = new ListNode(newDataItem, 0);
		cursor = head;
	}
	else {
		if (cursor == head) {
			ListNode *node = new ListNode(newDataItem, head);
			head = node;
			cursor = node;
		}
		else {
			gotoPrior();
			insert(newDataItem);
		}
	}
}


#include "show5.cpp"

