#include "ExpressionTree.h"
#include <iostream>
#include <cctype>

// By: Omer Khan 
// CSC 2200 
// Lab 8


template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr)
{
	dataItem = elem;
	left = leftPtr;
	right = rightPtr;
}

template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = 0;
}


template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree<DataType>& source)
{
	root = NULL;
	*this = source;
}


template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
{
	if (this != &source)
	{
		clear();
		if (source.root != NULL)
		{
			copyHelper(root, source.root);
		}
	}

	return *this;
}


template <typename DataType>
ExprTree<DataType>::~ExprTree()
{
	clear();
}


template <typename DataType>
void ExprTree<DataType>::build()
{
	clear();
	buildHelper(root);
}


template <typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& p)
{
	char newdataItem;
	cin >> newdataItem;
	p = new ExprTreeNode(newdataItem, NULL, NULL);
	if ((newdataItem == '+') || (newdataItem == '-') || (newdataItem == '*') ||	(newdataItem == '/'))
	{
		buildHelper(p->left);
		buildHelper(p->right);
	}
}

template <typename DataType>
void ExprTree<DataType>::expression() const
{
	bool LEFT = true;  // using these to keep track of the side.  left = left parenthesis, right = right par
	bool RIGHT = false;

	if (root == NULL)
	{
		cout << "The tree contains no expression." << endl;
	}
	else
	{
		expressionHelper(root, LEFT);
	}
}



template <typename DataType>
void ExprTree<DataType>::expressionHelper(ExprTreeNode* p, bool side) const
{
	bool LEFT = true;
	bool RIGHT = false;

	if (isdigit(p->dataItem) && side == LEFT)
	{
		cout << '(' << p->dataItem;
	}
	else if ((p->dataItem == '+') || (p->dataItem == '-') || (p->dataItem == '*') || (p->dataItem == '/'))
	{
		expressionHelper(p->left, LEFT);
		cout << ' ' << p->dataItem << ' ';
		expressionHelper(p->right, RIGHT);
	}
	else
	{
		cout << p->dataItem << ')';
	}
}

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
	DataType result;
	if (root == NULL)
		throw logic_error("Root is NULL.");
	else
		result = evaluateHelper(root);

	return result;
}

template <typename DataType>
DataType ExprTree<DataType>::evaluateHelper(ExprTreeNode* p) const
{
	DataType leftResult;
	DataType rightResult;
	DataType result;

	if (isdigit(p->dataItem))
	{
		result = DataType(p->dataItem - '0');
	}
	else
	{
		leftResult = evaluateHelper(p->left);
		rightResult = evaluateHelper(p->right);

		switch (p->dataItem)
		{
		case '+':
			result = leftResult + rightResult;
			break;

		case '-':
			result = leftResult - rightResult;
			break;

		case '*':
			result = leftResult * rightResult;
			break;

		case '/':
			result = leftResult / rightResult;
			break;

		default:
			cout << "Not an operator." << endl;
			break;
		}
	}

	return result;
}

template <typename DataType>
void ExprTree<DataType>::clear()
{
	clearHelper(root);
}


template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode*& p)
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

template <typename DataType>
void ExprTree<DataType>::commute()
{
	if (root != NULL)
		commuteHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode*& p)
{
	ExprTreeNode* temp;

	if ((p->left != NULL) || (p->right != NULL))
	{
		if (p->left != NULL)
			commuteHelper(p->left);

		if (p->right != NULL)
			commuteHelper(p->right);

		if ((p->dataItem == '+') || (p->dataItem == '-') || (p->dataItem == '*') || (p->dataItem == '/'))
		{
			temp = p->left;
			p->left = p->right;
			p->right = temp;
		}
	}

}



#include "show8.cpp"



template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
	// return the state of the tree
	return (root == NULL);
}

template <typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode*& p, ExprTreeNode* otherCurrent)
{
	p = new ExprTreeNode(otherCurrent->dataItem, NULL, NULL);
	if (otherCurrent->left != NULL)
	{
		copyHelper(p->left, otherCurrent->left);
	}
	if (otherCurrent->right != NULL)
	{
		copyHelper(p->right, otherCurrent->right);
	}
}

template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
	return false;
}
































