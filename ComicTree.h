// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Minh An Cao

//
//  ComicTree.h
//
//  This is the header file for the ComicTree class.
//
//  Minh An Cao
//

#ifndef _COMIC_TREEin
#define _COMIC_TREE

#include "ComicNode.h"
#include "Stack.h"
#include "Queue.h"
#include "Comic.h"

template<class ItemType>
class ComicTree
{
protected:
	ComicNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	ComicTree() {rootPtr = 0; count = 0;}
	ComicTree(const ComicTree<ItemType> & tree){ }
	virtual ~ComicTree() { }
	ComicTree & operator = (const ComicTree & sourceTree);

	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	void breadthOrder(void visit(ItemType &)) const{_breadthorder(visit, rootPtr);}

private:
	// delete all nodes from the tree
	void destroyTree(ComicNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	ComicNode<ItemType>* copyTree(const ComicNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const;
	void _iterpreorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const;
	void _iterinorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const;
	void _iterpostorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const;
	void _breadthorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const;

};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
ComicNode<ItemType>* ComicTree<ItemType>::copyTree(const ComicNode<ItemType>* nodePtr)
{
	ComicNode<ItemType>* newNodePtr = 0;


    return newNodePtr;
}

template<class ItemType>
void ComicTree<ItemType>::destroyTree(ComicNode<ItemType>* nodePtr)
{
    if(nodePtr != NULL)
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete(nodePtr);
        if(nodePtr->getLeftPtr()!=NULL)
            nodePtr->setLeftPtr(NULL);
        if(nodePtr->getRightPtr()!=NULL)
            nodePtr->setRightPtr(NULL);
        nodePtr=NULL;
    }
}

template<class ItemType>
void ComicTree<ItemType>::_preorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void ComicTree<ItemType>::_inorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void ComicTree<ItemType>::_postorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}

template<class ItemType>
void ComicTree<ItemType>::_breadthorder(void visit(ItemType &), ComicNode<ItemType>* nodePtr) const
{
	Queue<ComicNode<ItemType>*> q;

	if (nodePtr != 0)
	{
		q.enqueue(nodePtr);
	}

	while (!q.isEmpty())
	{
		ComicNode<ItemType>* temp;
		q.queueFront(temp);
		ItemType item = temp->getItem();
        visit(item);

		if (temp->getLeftPtr() != NULL)
			q.enqueue(temp->getLeftPtr());

		if (temp->getRightPtr() != NULL)
			q.enqueue(temp->getRightPtr());

		q.dequeue(temp);
	}

}

template<class ItemType>
ComicTree<ItemType> & ComicTree<ItemType>::operator=(const ComicTree<ItemType> & sourceTree)
{

}

#endif

