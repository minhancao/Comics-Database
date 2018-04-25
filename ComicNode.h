// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Minh An Cao

//
//  ComicNode.h
//
//  This is the header file for the ComicNode class.
//
//  Minh An Cao
//

#ifndef _COMIC_NODE
#define _COMIC_NODE

template<class ItemType>
class ComicNode
{
private:
	ItemType              item;         // Data portion
	ComicNode<ItemType>* leftPtr;		// Pointer to left child
	ComicNode<ItemType>* rightPtr;		// Pointer to right child

public:
	// constructors
	ComicNode(const ItemType & anItem)	{item = anItem; leftPtr = 0; rightPtr = 0;}
	ComicNode(const ItemType & anItem,
		       ComicNode<ItemType>* left,
			   ComicNode<ItemType>* right) {item = anItem; leftPtr = left; rightPtr = right;}
	// mutators
	void setItem(const ItemType & anItem) {item = anItem;}
	void setLeftPtr(ComicNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(ComicNode<ItemType>* right) {rightPtr = right;}
	// accessors
	ItemType getItem() const	 {return item;}
	ComicNode<ItemType>* getLeftPtr() const  {return leftPtr;}
	ComicNode<ItemType>* getRightPtr() const {return rightPtr;}

	bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
};

#endif
