//written by Huy Phan
//This is a hash header file.
//the hash resolution is: linear probe
#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "Comic.h"

class Hash
{
private:
	int loadFactor;
	int prime[4]; 
	int collision;
	int Size;
	Comic** hashTable;
public:

	//constructor
	Hash(int);
	//destructor
	~Hash();

	//this is the hash algorithm
	int hashFunction(string, int, int, int);
	int badHash(string, int);

	//these two are the get functions
	double getLoadfactor();
	int getCollision(){ return collision; }

	//this function add new book into the hash table
	void Insert(const Comic & newEntry);
	void Insert2(const Comic & newEntry);

	//this function will traverse the hash table
	//and delete the book that needs to be removed
	bool Delete(string);

	//this function search for a target book
	Comic* Search(string, bool&);

	//this is the rehash function
	void reHash();

	//this is the statistic function
	void statistic();
	void display();

};

#endif // HASH_H_INCLUDED
