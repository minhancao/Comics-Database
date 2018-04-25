

#include "ComicBST.h"  // BST ADT
#include "Comic.h"
#include "Hash.h"
#include "Display.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

//By: Loi Nguyen
// display function to pass to BST traverse functions
void output(Comic & comic)
{
	ofstream outputfile;
	outputfile.open("output.txt", ios::app);

	outputfile << comic.getIsbn() << ";" << comic.getTitle() << ";" << comic.getWriter() << ";" << comic.getArtist() << ";" << comic.getPublisher() << ";" << comic.getGenre() << ";" << comic.getPublishedDate() << "\n";
	outputfile.close();
}

//By: Loi Nguyen
// function used to clear the output file before writing into it
void clearOutputFile()
{
    ofstream outputfile;
    outputfile.open("output.txt", ios::out);
    outputfile.close();
}

//By: Loi Nguyen
void outputFile(ComicBST<Comic>* &tree, Stack<Comic>* deleteStack)
{
    clearOutputFile();
	tree->breadthOrder(output);
	Comic item;
	while(!deleteStack->isEmpty())
    {
        deleteStack->pop(item);
    }

    if(deleteStack->isEmpty())
    {
        cout << "Undo delete stack is cleared/empty!" << endl;
    }
}
void displayProjectInfo();
void readFile(ComicBST<Comic>* tree1, ComicBST<Comic>* tree2, Hash* hashtable, char choice);
void getNumItems(int& tempNum);
int main()
{

	int tempnum = 0;
	getNumItems(tempnum);
	ComicBST<Comic>* isbnTree = new ComicBST<Comic>();
	ComicBST<Comic>* titleTree = new ComicBST<Comic>();
	Stack<Comic>* deleteStack = new Stack<Comic>();
	Hash* hashtable = new Hash(tempnum);

	displayProjectInfo();
	char choice;
	char choice2;
	bool exit = false;

	//demonstrate the efficiency of two hash functions
	//First: test the bad hash function
	cout << "This is the bad hash function: \n";
	readFile(isbnTree, titleTree, hashtable, 'b');
	hashtable->statistic();
	
	//release memory of the bad hash function
	Hash* temp1 = hashtable;
	ComicBST<Comic>* temp2 = isbnTree;
	ComicBST<Comic>* temp3 = titleTree;
	hashtable = nullptr; isbnTree = nullptr; titleTree = nullptr;
	delete temp1, temp2, temp3;

	//test good hash function
	hashtable = new Hash(tempnum);
	isbnTree = new ComicBST<Comic>();
	titleTree = new ComicBST<Comic>();
	cout << "This is the good hash function: \n";
	readFile(isbnTree, titleTree, hashtable, 'g');	
	hashtable->statistic();
	hashtable->reHash(); // The rehash only works when load factor is greater than or equal to 75%

	//by Matthew Dumanig
	//***************************************************************************

	do
	{
		displayMenu();

		//Prompts user input and returns input validated
		choice = inputChoice();
		//Menu choices
		switch (choice)
		{
		case 'A': cout << "===============ADD COMIC===============\n"; addData(isbnTree, titleTree, hashtable); break;
		case 'D': deleteOptions(isbnTree, titleTree, hashtable, deleteStack); break;
		case 'S': searchOptions(isbnTree, titleTree, hashtable);  break;
		case 'L': listOptions(isbnTree, titleTree, hashtable); break;
		case 'W': cout << "==============WRITE OUTPUT==============\n"; outputFile(isbnTree, deleteStack); break;
		case 'X': cout << "===============STATISTICS===============\n"; hashtable->statistic(); break;
		case 'Q': exit = true; break;
		default: cout << "Bad input! Not an available option.\n";
		}
	} while (!exit);

	outputFile(isbnTree, deleteStack); //writes data to outputfile at end of program
	cout << "Program exiting..." << endl;
	//***************************************************************************
	system("pause");
	
	return 0;
}

void displayProjectInfo()
{
	cout << "========================Comic Data Base===========================\n";
	cout << "This project application program is a database for comic books. \n";
	cout << "It allows the user to do basic database features like adding \n";
	cout << "new comics into the database, deleting, searching, undoing a\n";
	cout << "delete, and printing out the comics inside the database.\n\n";
	cout << "Developed by:\nMinh An Cao \nHuy Phan \nMatthew Dumanig\nLoi Nguyen\n";
	cout << "==================================================================\n";
}
//By: Loi Nguyen
void readFile(ComicBST<Comic>* tree1, ComicBST<Comic>* tree2, Hash* hashtable, char choice)
{
	Comic comic1;
	ifstream inputfile;
	inputfile.open("input.txt");
	if (!inputfile.good())
	{
		cout << "Error opening file!\n";
		exit(101);
	}

	string num;
	string name;
	string author;
	string pub;
	string type;
	string drawer;
	string date;

	while (!inputfile.eof())
	{
		getline(inputfile, num, ';');
		getline(inputfile, name, ';');
		getline(inputfile, author, ';');
		getline(inputfile, drawer, ';');
		getline(inputfile, pub, ';');
		getline(inputfile, type, ';');
		getline(inputfile, date);
		comic1.setIsbn(num);
		comic1.setTitle(name);
		comic1.setWriter(author);
		comic1.setArtist(drawer);
		comic1.setPublisher(pub);
		comic1.setGenre(type);
		comic1.setPublishedDate(date);
		tree1->insertByIsbn(comic1);
		tree2->insertByTitle(comic1);
		if (choice == 'b')
		{
			hashtable->Insert2(comic1);
		}
		if (choice == 'g')
		{
			hashtable->Insert(comic1);
		}
	}
	inputfile.close();
}
void getNumItems(int& tempNum)
{
	Comic comic1;
	ifstream inputfile;
	inputfile.open("input.txt");
	if (!inputfile.good())
	{
		cout << "Error opening file!\n";
		exit(101);
	}

	string num;
	string name;
	string author;
	string pub;
	string type;
	string drawer;
	string date;

	while (!inputfile.eof())
	{
		getline(inputfile, num, ';');
		getline(inputfile, name, ';');
		getline(inputfile, author, ';');
		getline(inputfile, drawer, ';');
		getline(inputfile, pub, ';');
		getline(inputfile, type, ';');
		getline(inputfile, date);
		comic1.setIsbn(num);
		comic1.setTitle(name);
		comic1.setWriter(author);
		comic1.setArtist(drawer);
		comic1.setPublisher(pub);
		comic1.setGenre(type);
		comic1.setPublishedDate(date);
		tempNum++;
	}
	inputfile.close();
}
