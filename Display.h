#ifndef Display_h
#define Display_h

#include "ComicBST.h"  // BST ADT
#include "Comic.h"
#include "Hash.h"
#include "Stack.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//By Matthew Dumanig
//*************************************
void primaryKeySearchManager(Hash* hashtable);  //by Matthew Dumanig and Minh An Cao
void secondaryKeySearchManager(ComicBST<Comic>* tree);
void displayMenu();
void deleteOptions(ComicBST<Comic>*  treeISBN, ComicBST<Comic>*  treeTitle, Hash* hashtable, Stack<Comic>* deleteStack);
void searchOptions(ComicBST<Comic>* treeISBN, ComicBST<Comic>* treeTitle, Hash* hashtable);
void listOptions(ComicBST<Comic>* treeISBN, ComicBST<Comic>* treeTitle, Hash* hashtable);
char inputChoice();
bool isbnIsValid(string isbn);
void addData(ComicBST<Comic>* tree1, ComicBST<Comic>* tree2, Hash* hashtable);
void primaryKeyDeleteManager(ComicBST<Comic>* treeISBN, ComicBST<Comic>* treeTitle, Hash* hashtable, Stack<Comic>* stack);
void undoDelete(ComicBST<Comic>*  treeISBN, ComicBST<Comic>*  treeTitle, Hash* hashtable, Stack<Comic>* deleteStack);
//***************************************
#endif
