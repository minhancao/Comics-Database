#include "Hash.h"
#include <iomanip>
#include <iostream>

//*********************************************
// Constructor: Assign every position in the
//hash table an initial pointer
//*********************************************
Hash::Hash(int size2)
{
	int numtemp;
	loadFactor = 0;
	collision = 0;
	prime[0] = 97;
	prime[1] = 31;
	prime[2] = 12;
	prime[3] = 19;
	if (((size2 * 2) % 2) == 0)
	{
		numtemp = (size2 * 2) + 1;
	}
	Size = numtemp;
	hashTable = new Comic*[Size];
	for (int i = 0; i < Size; i++)
	{
		hashTable[i] = nullptr;
	}
}

//***********************************************
//this is the hash function. It will change the
// key into a particular address
//***********************************************
int Hash::hashFunction(string key, int arraySize, int prime1, int prime2)
{
	int address = 0;

	//hash the key to get the address
	for (unsigned int i = 0; i < key.length(); i++)
	{
		address = address + static_cast<int>(key[i])*prime1%prime2;
	}
	address = address % arraySize;
	return address;
}

int Hash::badHash(string key, int arraySize)
{
	int address = 0;

	//hash the key to get the address
	for (unsigned int i = 0; i<key.length(); i++)
	{
		address = address + static_cast<int>(key[i]);
	}
	address = address % 5;
	return address;
}
//*****************************************************
//this function inserts a new comic into the hash table
//*****************************************************
void Hash::Insert(const Comic & newEntry)
{
	bool flag = false;
	Comic* insert = new Comic(newEntry);

	//hash the search key into an address to locate the
	//position of the book in the hash table.
	int key = hashFunction(insert->getIsbn(), Size, prime[0], prime[1]);

	//if there is no book was here, insert
	//the comic in this location
	if (hashTable[key] == nullptr)
	{
		hashTable[key] = insert;

		//update the load factor when insert successful
		loadFactor++;
	}

	//if the position is already occupied
	//find the empty position in the second half of the hash table
	//and insert the book in this location if found
	else
	{

		//find the empty position in the second half of the hash table
		//and insert the book in this location if found
		int i = key + 1;
		while (i<Size && flag == false)
		{

			//update the number of collision
			collision++;

			//insert the book in empty position
			if (hashTable[i] == nullptr)
			{
				hashTable[i] = insert;

				//update the load factor
				loadFactor++;
				flag = true;
			}
			i++;
		}

		//if the book is not inserted in the second half of the hash table
		if (flag == false)
		{

			//find the empty position in the first half of the hash table
			//and insert the book in this location if found
			i = 0;
			while (i<key && flag == false)
			{

				//update the number of collision
				collision++;

				//insert the book in the empty location
				if (hashTable[i] == nullptr)
				{
					hashTable[i] = insert;

					//update the load factor
					loadFactor++;
					flag = true;
				}
				i++;
			}
		}
	}
}
//*****************************************************
//this function inserts a new comic into a bad hash table
//*****************************************************
void Hash::Insert2(const Comic & newEntry)
{
	bool flag = false;
	Comic* insert = new Comic(newEntry);

	//hash the search key into an address to locate the
	//position of the book in the hash table.
	int key = badHash(insert->getIsbn(), Size);

	//if there is no book was here, insert
	//the comic in this location
	if (hashTable[key] == nullptr)
	{
		hashTable[key] = insert;

		//update the load factor when insert successful
		loadFactor++;
	}

	//if the position is already occupied
	//find the empty position in the second half of the hash table
	//and insert the book in this location if found
	else
	{

		//find the empty position in the second half of the hash table
		//and insert the book in this location if found
		int i = key + 1;
		while (i<Size && flag == false)
		{

			//update the number of collision
			collision++;

			//insert the book in empty position
			if (hashTable[i] == nullptr)
			{
				hashTable[i] = insert;

				//update the load factor
				loadFactor++;
				flag = true;
			}
			i++;
		}

		//if the book is not inserted in the second half of the hash table
		if (flag == false)
		{

			//find the empty position in the first half of the hash table
			//and insert the book in this location if found
			i = 0;
			while (i<key && flag == false)
			{

				//update the number of collision
				collision++;

				//insert the book in the empty location
				if (hashTable[i] == nullptr)
				{
					hashTable[i] = insert;

					//update the load factor
					loadFactor++;
					flag = true;
				}
				i++;
			}
		}
	}
}


//*******************************************************
//this function return the load factor of the hash table
//*******************************************************
double Hash::getLoadfactor()
{
	return loadFactor*1.0 / Size * 100;
}

//**************************************
//this function gets a search key and
// it would delete the book which has
// the same isbn as the target key
//**************************************
bool Hash::Delete(string key)
{
	bool flag = false;

	//hash the search key into an address to locate the
	//position of the book in the hash table.
	int index = hashFunction(key, Size, prime[0], prime[1]);

	//this variable is used to traverse the hash table
	int i = index;

	//traverse the hash table from the first possible position to
	//the end of the hash table and delete the book if found
	while (i<Size && flag == false)
	{
		if (hashTable[i] != nullptr)
		{
			if (hashTable[i]->getIsbn() == key)
			{

				//remove the book from the hash table.
				hashTable[i] = nullptr;

				//delete successfully
				flag = true;

				//update the load factor
				loadFactor--;
			}
		}
		i++;
	}

	// the element is not in the region from the address
	//to the end of the hash table. It is probably in
	//the first half of the hash table.
	if (flag == false)
	{

		//traverse the first half of the hash table
		//and remove the book if found.
		int i = 0;
		while (i<index && flag == false)
		{

			//make sure the position is not empty
			if (hashTable[i] != nullptr)
			{
				if (hashTable[i]->getIsbn() == key)
				{

					//delete the book if found
					hashTable[i] = nullptr;
					flag = true;

					//update the load factor
					loadFactor--;
				}
			}
			i++;
		}
	}

	//display the success of the delete function
	if (flag == false)
	{
		cout << "No comic has this ISBN. " << endl;
	}

	return flag;
}

//***************************************
// this function gets a key and search
// for the book whose key is the same
// as the search key
//***************************************
Comic* Hash::Search(string searchKey, bool & success)
{

	//hash the search key into an address to locate the
	//position of the book in the hash table.
	int index = hashFunction(searchKey, Size, prime[0], prime[1]);

	//this pointer will point to the book if it is found
	Comic* returnPtr = nullptr;

	//this variable is used to traverse the hash table
	int i = index;

	//search the hash table from the first possible position to
	//the end of the hash table.
	while (i<Size && returnPtr == nullptr)
	{
		// make sure that the position is not empty
		if (hashTable[i] != nullptr)
		{
			//compare the value of search key with the isbn
			//of each book in the hash table
			if (hashTable[i]->getIsbn() == searchKey)
			{
				returnPtr = hashTable[i];
			}
		}
		i++;
	}

	// the element is not in the region from the address
	//to the end of the hash table. It is probably in
	//the first half of the hash table.
	if (returnPtr == nullptr)
	{

		//search the first half of the hash table
		int i = 0;
		while (i<index && returnPtr == nullptr)
		{
			if (hashTable[i] != nullptr)
			{
				if (hashTable[i]->getIsbn() == searchKey)
				{
					returnPtr = hashTable[i];
				}
			}
			i++;
		}
	}

	//if the comic is not in the hashtable, makes the bool false
	if (returnPtr == nullptr)
	{
		success = false;
	}

	//if the comic is in the hashtable, makes the bool true
	if (returnPtr != nullptr)
	{
		success = true;
	}

	return returnPtr;
}

//****************************************
//this function will display the load
//factor and the number of collision
//****************************************
void Hash::statistic()
{

	//show the load factor and the number of collision
	cout << setprecision(2) << fixed;
	cout << "\nLoad factor: " << getLoadfactor() << " %" << endl;
	cout << "Collision: " << getCollision() << endl << endl;
}

//****************************************
//this function will display all books in
//the hash table.
//****************************************
void Hash::display()
{
	for (int i = 0; i < Size; i++)
	{
		if (hashTable[i] != NULL)
		{
			cout << "|" << setw(12) << left << hashTable[i]->getIsbn();
			cout << "|" << setw(45) << left << hashTable[i]->getTitle();
			cout << "|" << setw(25) << left << hashTable[i]->getWriter();
			cout << "|" << setw(20) << left << hashTable[i]->getArtist();
			cout << "|" << setw(25) << left << hashTable[i]->getPublisher();
			cout << "|" << setw(15) << left << hashTable[i]->getGenre();
			cout << "|" << setw(20) << left << hashTable[i]->getPublishedDate() << "|" << endl;

		}
	}
}

//*************************************************************
//when the load factor of the original hash table is over 40%
//this function will hash every book from the old hash table
//into a new hash table which is doubled in size
//*************************************************************
void Hash::reHash()
{

	if (((loadFactor*1.0 / Size) * 100) >= 75.0)
	{
		int newLoadFactor = 0;
		int newCollision = 0;

		//allocate a new rehash table
		Comic** rehashTable;
		rehashTable = new Comic*[2 * Size];

		//initialize the null pointer to every element in the rehash table
		for (int i = 0; i<(2 * Size); i++)
		{
			rehashTable[i] = nullptr;
		}

		//traverse all the books in the hash table
		int index = 0;
		while (index < Size)
		{
			bool flag = false;

			//check empty position
			if (hashTable[index] != nullptr)
			{

				//hash each book in the hash table and insert
				//those books into the rehash table
				int key = hashFunction(hashTable[index]->getIsbn(), 2 * Size, prime[2], prime[3]);

				if (rehashTable[key] == nullptr)
				{
					rehashTable[key] = hashTable[index];

					//update the load factor when insert successful
					newLoadFactor++;
					flag = true;

				}

				//if the position is already occupied
				//find the empty position in the second half of the hash table
				//and insert the book in this location if found
				else
				{

					//find the empty position in the second half of the hash table
					//and insert the book in this location if found
					int i = key + 1;
					while (i<(2 * Size) && flag == false)
					{

						//update the number of collision
						newCollision++;

						//insert the book in empty position
						if (rehashTable[i] == nullptr)
						{
							rehashTable[i] = hashTable[index];

							//update the load factor
							newLoadFactor++;
							flag = true;
						}
						i++;
					}

					//if the book is not inserted in the second half of the hash table
					if (flag == false)
					{

						//find the empty position in the first half of the hash table
						//and insert the book in this location if found
						i = 0;
						while (i<key && flag == false)
						{

							//update the number of collision
							newCollision++;

							//insert the book in the empty location
							if (rehashTable[i] == nullptr)
							{
								rehashTable[i] = hashTable[index];

								//update the load factor
								newLoadFactor++;
								flag = true;
							}
							i++;
						}
					}
				}
			}
			index++;
		}

		//delete the old hash table
		delete[] hashTable;

		//assign the rehash table to the hash table
		hashTable = rehashTable;

		//update information
		Size = 2 * Size;
		loadFactor = newLoadFactor;
		collision = newCollision;

		//delete the rehash table and free the memory
		delete[]rehashTable;
	}
}

//*********************************
//this is the destructive function
//it will delete the hash table
//and free the memory
//*********************************
Hash::~Hash()
{
	delete[] hashTable;
}
