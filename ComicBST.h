// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Minh An Cao

//
//  ComicBST.h
//
//  This is the header file for the ComicBST class.
//
//  Minh An Cao
//

#ifndef _COMIC_BST
#define _COMIC_BST

#include "ComicTree.h"
#include <string>
#include "Queue.h"
#include "Comic.h"

using namespace std;

template<class ItemType>
class ComicBST : public ComicTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree by isbn
	ComicNode<ItemType>* _insertByIsbn(ComicNode<ItemType>* nodePtr, ComicNode<ItemType>* newNode);

	// internal insert node: insert newNode in nodePtr subtree by title
	ComicNode<ItemType>* _insertByTitle(ComicNode<ItemType>* nodePtr, ComicNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	ComicNode<ItemType>* _removeByIsbn(ComicNode<ItemType>* nodePtr, const string target, bool & success, Comic & temp);

	ComicNode<ItemType>* _removeByTitle(ComicNode<ItemType>* nodePtr, Comic target, bool & success);

	// delete target node from tree, called by internal remove node
	ComicNode<ItemType>* deleteNode(ComicNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	ComicNode<ItemType>* removeLeftmostNode(ComicNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	ComicNode<ItemType>* findNodeByIsbn(ComicNode<ItemType>* nodePtr, string & target, bool & success) const;

	// search for target node
	void findNodeByTitle(ComicNode<ItemType>* nodePtr, string & target, bool & success, Queue<Comic> & q) const;

	//find smallest node
	ComicNode<ItemType>* findSmallestNode(ComicNode<ItemType>* nodePtr, bool & success) const;

	//find largest node
	ComicNode<ItemType>* findLargestNode(ComicNode<ItemType>* nodePtr, bool & success) const;

	//prints tree as indented list
	void printIndentedList(void visit(ItemType &, int &, int &), ComicNode<ItemType>* nodePtr, int level, int indent);

public:
	// insert a node at the correct location by isbn
	bool insertByIsbn(const ItemType & newEntry);
	// insert a node at the correct location by title
	bool insertByTitle(const ItemType & newEntry);
	// remove a node if found
	bool removeByIsbn(const string & anEntry, Comic & temp);
	// remove a node if found
	bool removeByTitle(Comic temp);
	// find a target node
	bool getEntryByIsbn(string & target, ItemType & returnedItem) const;
	// find a target node
	bool getEntryByTitle(string & target) const;
	//find smallest node
	bool findSmallest(ItemType & returnedItem) const;
	//find largest node
	bool findLargest(ItemType & returnedItem) const;
	//prints tree as indented list
	void printList(void visit(ItemType &, int &, int &));

};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool ComicBST<ItemType>::insertByIsbn(const ItemType & newEntry)
{
	ComicNode<ItemType>* newNodePtr = new ComicNode<ItemType>(newEntry);
	this->rootPtr = _insertByIsbn(this->rootPtr, newNodePtr);
	ComicTree<ItemType>::count++;
	return true;
}

template<class ItemType>
bool ComicBST<ItemType>::insertByTitle(const ItemType & newEntry)
{
	ComicNode<ItemType>* newNodePtr = new ComicNode<ItemType>(newEntry);
	this->rootPtr = _insertByTitle(this->rootPtr, newNodePtr);
	ComicTree<ItemType>::count++;
	return true;
}

template<class ItemType>
bool ComicBST<ItemType>::removeByIsbn(const string & target, Comic & temp)
{
	bool success = false;
	this->rootPtr = _removeByIsbn(this->rootPtr, target, success, temp);
	if (success){
		ComicTree<ItemType>::count--;
	}

	return success;
}

template<class ItemType>
bool ComicBST<ItemType>::removeByTitle(Comic temp)
{
	bool success = false;
	this->rootPtr = _removeByTitle(this->rootPtr, temp, success);
	if (success){
		ComicTree<ItemType>::count--;
	}

	return success;
}

template<class ItemType>
bool ComicBST<ItemType>::getEntryByIsbn(string& target, ItemType & returnedItem) const
{
	bool isSuccessful = false;
	ComicNode<ItemType>* temp;
	temp = findNodeByIsbn(this->rootPtr, target, isSuccessful);

	if (isSuccessful)
	{
		returnedItem = temp->getItem();
	}
	return isSuccessful;
}

template<class ItemType>
bool ComicBST<ItemType>::getEntryByTitle(string& target) const
{
	bool isSuccessful = false;
	Queue<Comic> q;
	findNodeByTitle(this->rootPtr, target, isSuccessful, q);

	Comic temp;
	if (!q.isEmpty())
	{
		while (!q.isEmpty())
		{
			q.dequeue(temp);
			temp.display();
			cout << endl;
		}
	}

	return isSuccessful;
}

template<class ItemType>
bool ComicBST<ItemType>::findSmallest(ItemType & returnedItem) const
{
	bool successful = false;
	ComicNode<ItemType>* temp;
	temp = findSmallestNode(this->rootPtr, successful);

	if (successful)
	{
		returnedItem = temp->getItem();
	}
	return successful;
}

template<class ItemType>
bool ComicBST<ItemType>::findLargest(ItemType & returnedItem) const
{
	bool successful = false;
	ComicNode<ItemType>* temp;
	temp = findLargestNode(this->rootPtr, successful);

	if (successful)
	{
		returnedItem = temp->getItem();
	}
	return successful;
}

template<class ItemType>
void ComicBST<ItemType>::printList(void visit(ItemType &, int &, int &))
{
	printIndentedList(visit, this->rootPtr, 1, 0);
}



//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::_insertByIsbn(ComicNode<ItemType>* nodePtr,
	ComicNode<ItemType>* newNodePtr)
{
	if (nodePtr == NULL)
	{
		nodePtr = newNodePtr;
		return nodePtr;
	}

	if (newNodePtr->getItem() < nodePtr->getItem()) //uses the isbn to compare
	{

		nodePtr->setLeftPtr(_insertByIsbn(nodePtr->getLeftPtr(), newNodePtr));
		return nodePtr;
	}

	else{
		nodePtr->setRightPtr(_insertByIsbn(nodePtr->getRightPtr(), newNodePtr));
		return nodePtr;
	}

}

template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::_insertByTitle(ComicNode<ItemType>* nodePtr,
	ComicNode<ItemType>* newNodePtr)
{
	if (nodePtr == NULL)
	{
		nodePtr = newNodePtr;
		return nodePtr;
	}

	if (newNodePtr->getItem().getTitle() < nodePtr->getItem().getTitle())
	{
		nodePtr->setLeftPtr(_insertByTitle(nodePtr->getLeftPtr(), newNodePtr));
		return nodePtr;
	}

	else if (newNodePtr->getItem().getTitle() >= nodePtr->getItem().getTitle())
	{
		nodePtr->setRightPtr(_insertByTitle(nodePtr->getRightPtr(), newNodePtr));
		return nodePtr;
	}

}

template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::_removeByIsbn(ComicNode<ItemType>* nodePtr,
	string target,
	bool & success, Comic & temp)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}

	if (nodePtr->getItem().getIsbn() == target)
	{
		temp = nodePtr->getItem();
		nodePtr = deleteNode(nodePtr);
		success = true;
		return nodePtr;
	}
	if (nodePtr->getItem().getIsbn() > target)  //uses the isbn to compare
		nodePtr->setLeftPtr(_removeByIsbn(nodePtr->getLeftPtr(), target, success, temp));
	else
		nodePtr->setRightPtr(_removeByIsbn(nodePtr->getRightPtr(), target, success, temp));

	return nodePtr;
}

template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::_removeByTitle(ComicNode<ItemType>* nodePtr,
	Comic target,
	bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}

	if (nodePtr->getItem().getIsbn() == target.getIsbn())
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
		return nodePtr;
	}
	if (nodePtr->getItem().getTitle() > target.getTitle())  //uses the title to compare
		nodePtr->setLeftPtr(_removeByTitle(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem().getTitle() <= target.getTitle())
		nodePtr->setRightPtr(_removeByTitle(nodePtr->getRightPtr(), target, success));

	return nodePtr;
}


template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::deleteNode(ComicNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = NULL;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		ComicNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = NULL;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == NULL)
	{
		ComicNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = NULL;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::removeLeftmostNode(ComicNode<ItemType>* nodePtr,
	ItemType & successor)
{
	if (nodePtr->getLeftPtr() == NULL)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::findNodeByIsbn(ComicNode<ItemType>* nodePtr,
	string & target, bool & success) const
{
	while (nodePtr != NULL)
	{
		if (nodePtr->getItem().getIsbn() == target)
		{
			success = true;
			return nodePtr;
			break;
		}

		if (target > nodePtr->getItem().getIsbn())
		{
			nodePtr = nodePtr->getRightPtr();
		}

		else
		if (target < nodePtr->getItem().getIsbn())
		{
			nodePtr = nodePtr->getLeftPtr();
		}
	}

	return nodePtr;
}

template<class ItemType>
void ComicBST<ItemType>::findNodeByTitle(ComicNode<ItemType>* nodePtr,
	string & target, bool & success, Queue<Comic> & q) const
{

	if (nodePtr != NULL)
	{
		findNodeByTitle(nodePtr->getLeftPtr(), target, success, q);
		if (nodePtr->getItem().getTitle() == target)
		{
			success = true;
			q.enqueue(nodePtr->getItem());
		}
		findNodeByTitle(nodePtr->getRightPtr(), target, success, q);
	}

}

template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::findSmallestNode(ComicNode<ItemType>* nodePtr, bool & success) const
{
	if (nodePtr == NULL)
	{
		return nodePtr;
	}

	if (nodePtr->getLeftPtr() == NULL)
	{
		success = true;
		return nodePtr;
	}

	else{
		return findSmallestNode(nodePtr->getLeftPtr(), success);
	}
}

template<class ItemType>
ComicNode<ItemType>* ComicBST<ItemType>::findLargestNode(ComicNode<ItemType>* nodePtr, bool & success) const
{
	if (nodePtr == NULL)
	{
		return nodePtr;
	}

	if (nodePtr->getRightPtr() == NULL)
	{
		success = true;
		return nodePtr;
	}

	else{
		return findLargestNode(nodePtr->getRightPtr(), success);
	}
}

template<class ItemType>
void ComicBST<ItemType>::printIndentedList(void visit(ItemType &, int &, int &), ComicNode<ItemType>* nodePtr, int level, int indent)
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item, level, indent);
		printIndentedList(visit, nodePtr->getLeftPtr(), level + 1, indent + 8);
		printIndentedList(visit, nodePtr->getRightPtr(), level + 1, indent + 8);
	}
}



#endif

