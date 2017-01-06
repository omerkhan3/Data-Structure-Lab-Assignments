// By: Omer Khan 
// CSC 2200 
// Lab 9

#include "BSTree.h"
#include <iostream>
#include <algorithm>

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
	this->dataItem = nodeDataItem;
	this->left = leftPtr;
	this->right = rightPtr;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ()
{
	root = NULL;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other )
{
	root = NULL;
	*this = other;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= ( const BSTree<DataType,KeyType>& other )
{
	if (this != &source)
	{
		clear();
		if (other.root != NULL)
		{
			copyHelper(root, other.root);
		}
	}

	return *this;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::copyHelper(BSTreeNode*& p, BSTreeNode* otherCurrent)
{
	p = new BSTreeNode(otherCurrent->dataItem, NULL, NULL);
	if (otherCurrent->left != NULL)
	{
		copyHelper(p->left, otherCurrent->left);
	}
	if (otherCurrent->right != NULL)
	{
		copyHelper(p->right, otherCurrent->right);
	}
}


template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree ()
{
	this->clear();
}


template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem )
{
	insertHelper(this->root, newDataItem);
}


template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode *&p,const DataType& newDataItem)
{
	if (p == 0) // insert
	{
		p = new BSTreeNode(newDataItem, 0, 0);
	}

	else if (p->dataItem.getKey() >= newDataItem.getKey()) // search left
	{
		insertHelper(p->left, newDataItem);
	}

	else if (p->dataItem.getKey() < newDataItem.getKey()) // search right
	{
		insertHelper(p->right, newDataItem);
	}
	else                                                 // update
		p->dataItem = newDataItem; 


}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
	return (retrieveHelper(root, searchKey, searchDataItem));
}


template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode *p, const KeyType& searchKey, DataType& searchDataItem) const
{
	bool result; 

	if (p == 0)
		result = false;

	else if (searchKey < p->dataItem.getKey())
		result = retrieveHelper(p->left, searchKey, searchDataItem);

	else if (searchKey > p->dataItem.getKey())
		result = retrieveHelper(p->right, searchKey, searchDataItem);

	else
	{
		result = true;
		searchDataItem = p->dataItem;
	}

	return result;


}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey )
{
	
	return removeHelper(deleteKey, root);
}

template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::removeHelper(const KeyType& deleteKey, BSTreeNode *&p) {

	if (p == NULL)
		return false; // not found

	if (p != NULL)
	{

		if (deleteKey < p->dataItem.getKey())
			removeHelper(deleteKey, p->left); // traverse left if the inputted key is less than the current node.

		else if (deleteKey > p->dataItem.getKey()) // traverse right if the inputted key is less than the current node.
			removeHelper(deleteKey, p->right);

		else
		{
			BSTreeNode *deleteNode = p;

			if (p->left == NULL)  // No left child
			{
				p = p->right;
				delete deleteNode;
			}
			else if (p->right == NULL) // No right child
			{
				p = p->left;
				delete deleteNode;
			}

			else if ((p->left != NULL) && (p->right != NULL)) // if the node has both right and left children.  
			{
				BSTreeNode *tempNode = p->right;

				while (tempNode->left != NULL)
					tempNode = tempNode->left;

				p->dataItem = tempNode->dataItem;


				removeHelper(tempNode->dataItem.getKey(), p->right);
			}

			return true;
		}
	}
}




template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys () const
{
	writeKeysHelper(root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode *p) const
{
	if (p == NULL)
		return;
	else {
		writeKeysHelper(p->left);
		cout << p->dataItem.getKey() << " ";
		writeKeysHelper(p->right);
	}
}


template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear ()
{
	clearHelper(root);
}


template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode*& p)
{
	if (p != NULL)
	{
		if (p->right != NULL)
			clearHelper(p->right);

		if (p->left != NULL)
			clearHelper(p->left);

		delete p;
		p = NULL;
	}
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty () const
{
	return (root == 0);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight () const
{
	return getHeightHelper(root) - 1;
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode *p)  const
{
	if (p == NULL)
		return 0;
	else {
		int leftheight = getHeightHelper(p->left) + 1;
		int rightheight = getHeightHelper(p->right) + 1;

		return max(rightheight, leftheight);
	}


}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount () const
{
	if (root == NULL)
		return 0;
	else 
		return getCountHelper(this->root);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode *p) const
{
	int count = 1;
	if (p->left != NULL)
		count = count + getCountHelper(p->left);
	if (p->right != NULL)
		count = count + getCountHelper(p->right);

	return count;

}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const
{
	writeLessThanHelper(root, searchKey);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThanHelper(BSTreeNode *p, const KeyType& searchKey) const
{
	if (p == NULL)
		return;
	else {
		writeLessThanHelper(p->left, searchKey);
		if (p->dataItem.getKey() < searchKey)
		{
			cout << p->dataItem.getKey() << " ";
			writeLessThanHelper(p->right, searchKey);
		}
	}
}


#include "show9.cpp"



