#include "Display.h"
#include "iomanip"

//************************************************
//By: Loi Nguyen
// display function to pass to BST traverse functions
//************************************************
void display(Comic & comic)
{

	cout << "|" << setw(12) << left << comic.getIsbn();
	cout << "|" << setw(45) << left << comic.getTitle();
	cout << "|" << setw(25) << left << comic.getWriter();
	cout << "|" << setw(20) << left << comic.getArtist();
	cout << "|" << setw(25) << left << comic.getPublisher();
	cout << "|" << setw(15) << left << comic.getGenre();
	cout << "|" << setw(20) << left << comic.getPublishedDate() << "|" << endl;
}

//************************************************
//By: Loi Nguyen
// display function to pass to BST traverse functions
//************************************************
void displayList(Comic & comic, int & level, int & indent)
{
	cout << setw(indent) << level << ". " << comic.getIsbn() << ";" << comic.getTitle() << ";" << comic.getWriter() << ";" << comic.getArtist() << ";" << comic.getPublisher() << ";" << comic.getGenre() << ";" << comic.getPublishedDate() << "\n\n";
}

//************************************************
//by Matthew Dumanig
//Description:
//Pre:
//Post:
//************************************************
void displayMenu()
{
	cout << "========================================\n";
	cout << "=============COMIC DATABASE=============\n";
	cout << "========================================\n";
	cout << "Menu Options:\n";
	cout << "A - Add\n";
	cout << "D - Delete\n";
	cout << "S - Search\n";
	cout << "L - List\n";
	cout << "W - Write data to file\n";
	cout << "X - Statistics\n";
	cout << "Q - Quit\n\n";
}


//DELETE FUNCTIONS

//************************************************
//by Matthew Dumanig
//Description:
//Pre:
//Post:
//************************************************
void deleteOptions(ComicBST<Comic>* treeISBN, ComicBST<Comic>* treeTitle, Hash* hashtable, Stack<Comic>* deleteStack)
{

	char choice;
	bool exit = false;

	cout << "==============DELETE OPTIONS============\n";
	cout << "I - by ISBN\n";;
	cout << "U - Undo delete\n";
	cout << "R - Return\n\n";

	do
	{
		choice = inputChoice();
		switch (choice)
		{
		case 'I': cout << "==============DELETE BY ISBN=============\n";
			primaryKeyDeleteManager(treeISBN, treeTitle, hashtable, deleteStack); exit = true;
			deleteOptions(treeISBN, treeTitle, hashtable, deleteStack); break;
		case 'U': cout << "===============UNDO DELETE===============\n";
			undoDelete(treeISBN, treeTitle, hashtable, deleteStack); exit = true;
			deleteOptions(treeISBN, treeTitle, hashtable, deleteStack); break;
		case 'R': return;
		default: cout << "Bad input! Not an available option.\n";
		}
	} while (!exit);
}

//************************************************
//by Matthew Dumanig and Minh An Cao
//Description:
//Deletes the selected node from the BST's
//Pre:
//Post:
//************************************************
void primaryKeyDeleteManager(ComicBST<Comic>* treeIsbn, ComicBST<Comic>* treeTitle, Hash* hashtable, Stack<Comic>* stack)
{
	string input;

	Comic deleted;			//used to hold the deleted Comic from the isbn tree
							//so it can be used to delete the same Comic in the treeTitle

	cin.ignore();
	do
	{
		cout << "Enter ISBN to delete: ";
		getline(cin, input);
	} while (!isbnIsValid(input));


	bool test = treeIsbn->removeByIsbn(input, deleted);
	test = hashtable->Delete(deleted.getIsbn());
	test = treeTitle->removeByTitle(deleted);

	if (test)
	{
		stack->push(deleted);
		cout << "Delete successful\n\n";
	}

	else
		cout << "Delete failed\n\n";
}

//************************************************
//Description:
//The user can undo the delete in the reverse order of the delete sequence.
//When the user selects "Save to file", the undo stack is cleaned out
//(no undo possible unless more delete occurs first)
//************************************************
void undoDelete(ComicBST<Comic>* treeISBN, ComicBST<Comic>* treeTitle, Hash* hashtable, Stack<Comic>* stack)
{
	Comic comic;

	if (stack->isEmpty())
		cout << "Stack is Empty! Can't undo delete.\n\n";
	else
	{
		stack->pop(comic);
		treeISBN->insertByIsbn(comic);
		treeTitle->insertByTitle(comic);
		hashtable->Insert(comic);
		cout << comic.getIsbn() << " " << comic.getTitle() << " Added.\n\n";
	}
}
//************************************************
//by Matthew Dumanig
//Description:
//Pre:
//Post:
//************************************************
void searchOptions(ComicBST<Comic>* treeISBN, ComicBST<Comic>* treeTitle, Hash* hashtable)
{
	char choice;
	bool exit = false;

	cout << "==============SEARCH OPTIONS============\n";
	cout << "I - by ISBN\n";
	cout << "T - by Title\n";
	cout << "R - Return\n\n";

	do
	{
		choice = inputChoice();
		switch (choice)
		{
		case 'I': cout << "==============SEARCH BY ISBN============\n";
			primaryKeySearchManager(hashtable); exit = true;
			searchOptions(treeISBN, treeTitle, hashtable); break;
		case 'T': cout << "==============SEARCH BY TITLE===========\n";
			secondaryKeySearchManager(treeTitle); exit = true;
			searchOptions(treeISBN, treeTitle, hashtable); break;
		case 'R': return;
		default: cout << "Bad input! Not an available option.\n";
		}
	} while (!exit);
}

//************************************************
//by Matthew Dumanig
//Description:
//prompt the user to enter a key, call search,
//then display the search results or a message if not found
//Pre:
//Post:
//************************************************
void primaryKeySearchManager(Hash* hashtable)
{
	string input;
	bool success = false;
	Comic* temp;

	cin.ignore();
	do
	{
		cout << "Enter ISBN to search for: ";
		getline(cin, input);
	} while (!isbnIsValid(input));

	cout << endl;
	temp = hashtable->Search(input, success);

	if(!success)
    {
        cout << "Comic not found!" << endl;
    }

	else
    {
        temp->display();
	}
}
//************************************************
//by Matthew Dumanig
//Description:
//if found, display all matches
//Pre:
//Post:
//************************************************
void secondaryKeySearchManager(ComicBST<Comic>* tree)
{
	string input;
	bool success = false;

	cout << "Enter Title to search for: ";
	cin.ignore();
	getline(cin, input);

	for (int i = 0; i < input.length(); i++)
	{
		if (islower(input[0]))
			input[0] = toupper(input[0]);

		if (input[i + 1] != NULL && input[i] == ' ' && islower(input[i + 1]))
			input[i + 1] = toupper(input[i + 1]);
	}

	cout << endl;
	success = tree->getEntryByTitle(input);
	if (!success)
		cout << "Entry not found." << endl;
}

//************************************************
//by Matthew Dumanig
//Description:
//Pre:
//Post:
//************************************************
void listOptions(ComicBST<Comic>* treeISBN, ComicBST<Comic>* treeTitle, Hash* hashtable)
{
	char choice;
	bool exit = false;

	cout << "===============LIST OPTIONS=============\n";
	cout << "U - Unsorted\n";
	cout << "I - ISBN\n";
	cout << "T - Title\n";
	cout << "Z - Special Indented\n";
	cout << "R - Return\n\n";

	do
	{
		choice = inputChoice();
		switch (choice)
		{
		case 'U': cout << "=============LIST UNSORTED==============\n\n";
			cout << "===============================================================================================================================================================================\n";
			cout << "|" << setw(12) << left << "Isbn" << "|" << setw(45) << left << "Title" << "|" << setw(25) << left << "Writer " << "|" << setw(20) << left << "Artist" << "|" << setw(25) << left << "Publisher" << "|" << setw(15) << left << "Genre" << "|" << setw(20) << left << "Published Date";
			cout << "|" << endl;
			cout << "_______________________________________________________________________________________________________________________________________________________________________________\n";
			hashtable->display(); exit = true;
			cout << "===============================================================================================================================================================================\n";
			listOptions(treeISBN, treeTitle, hashtable); break;

		case 'I': cout << "==============LIST BY ISBN==============\n\n";
			cout << "===============================================================================================================================================================================\n";
			cout << "|" << setw(12) << left << "Isbn" << "|" << setw(45) << left << "Title" << "|" << setw(25) << left << "Writer " << "|" << setw(20) << left << "Artist" << "|" << setw(25) << left << "Publisher" << "|" << setw(20) << left << "Genre" << "|" << setw(20) << left << "Published Date";
			cout << "|" << endl;
			cout << "_______________________________________________________________________________________________________________________________________________________________________________\n";
			treeISBN->inOrder(display); exit = true;
			cout << "===============================================================================================================================================================================\n";
			listOptions(treeISBN, treeTitle, hashtable); break;
		case 'T': cout << "==============LIST BY TITLE=============\n\n";
			cout << "===============================================================================================================================================================================\n";
			cout << "|" << setw(12) << left << "Isbn" << "|" << setw(45) << left << "Title" << "|" << setw(25) << left << "Writer " << "|" << setw(20) << left << "Artist" << "|" << setw(25) << left << "Publisher" << "|" << setw(20) << left << "Genre" << "|" << setw(20) << left << "Published Date";
			cout << "|" << endl;
			cout << "_______________________________________________________________________________________________________________________________________________________________________________\n";
			treeTitle->inOrder(display); exit = true;
			cout << "===============================================================================================================================================================================\n";
			listOptions(treeISBN, treeTitle, hashtable); break;
		case 'Z': cout << "==========SPECIAL INDENTED LIST=========\n\n";
			treeISBN->printList(displayList); exit = true;
			listOptions(treeISBN, treeTitle, hashtable); break;
		case 'R': return;
		default: cout << "Bad input! Not an available option.\n";
		}
	} while (!exit);
}

//************************************************
//by Matthew Dumanig
//Description:
//Adds a comic to the database
//Pre:  tree1 for isbn BST
//		tree2 for title BST
//Post: None
//************************************************
void addData(ComicBST<Comic>* tree1, ComicBST<Comic>* tree2, Hash* hashtable)
{
	Comic temp;
	string input;

	cin.ignore();

	do
	{
		cout << "Enter ISBN: ";
		getline(cin, input);
	} while (!isbnIsValid(input));
	temp.setIsbn(input);

	cout << "Enter Title: ";
	getline(cin, input);
	temp.setTitle(input);

	cout << "Enter Writer:  ";
	getline(cin, input);
	temp.setWriter(input);

	cout << "Enter Artist: ";
	getline(cin, input);
	temp.setArtist(input);

	cout << "Enter Publisher: ";
	getline(cin, input);
	temp.setPublisher(input);

	cout << "Enter Genre: ";
	getline(cin, input);
	temp.setGenre(input);

	cout << "Enter Published Date: ";
	getline(cin, input);
	temp.setPublishedDate(input);

	tree1->insertByIsbn(temp);
	tree2->insertByTitle(temp);
	hashtable->Insert(temp);

	cout << endl;
}

//************************************************
//by Matthew Dumanig
//Description:
//Prompts the user for their input for the menu.
//Validates user input as well.
//************************************************
char inputChoice()
{
	bool badInput = false;
	string input;
	char choice;

	do
	{
		badInput = false;
		cout << "Enter choice: ";
		cin >> input;
		cout << endl;
		if (input.length() > 1)
		{
			cout << "Bad input! Too many characters.\n";
			badInput = true;
		}
		choice = input[0];
		choice = toupper(choice);
		if (!isalpha(choice))
		{
			cout << "Bad input! Please enter a valid character.\n";
			badInput = true;
		}
	} while (badInput);

	return choice;
}

//************************************************
//by Matthew Dumanig
//************************************************
bool isbnIsValid(string isbn)
{
	bool goodInput = true;
	bool isSpace = false;
	bool isDigit = true;

	for (int i = 0; i < isbn.length(); i++)
	{
		if (isspace(isbn[i]))
		{
			goodInput = false;
			isSpace = true;
		}

		if (!isdigit(isbn[i]))
        {
            isDigit = false;
            goodInput = false;
        }

	}

	if (isbn.length() > 10 || isbn.length() < 10)
	{
		cout << "Bad Input! ISBN longer/shorter than 10 digits.\n";
		goodInput = false;
	}

	if (isSpace)
    {
        cout << "Bad Input! ISBN has a space.\n";
    }

    if (!isDigit)
    {
        cout << "Bad Input! ISBN is not all digits.\n";
    }

	return goodInput;
}
