//
//  Comic.h
//
//  This is the header file for the class Comic.
//
//  Minh An Cao & Huy Phan
//

#ifndef Comic_h
#define Comic_h

using namespace std;

#include <string>
#include <iostream>


class Comic
{
private:
    string isbn;
    string title;
    string writer;
    string publisher;
    string genre;
    string artist;
    string publishedDate;

public:
	//constructors
	Comic() { isbn = ""; title = ""; writer = ""; publisher = ""; genre = ""; artist = ""; publishedDate = ""; }
	Comic(string num, string name, string author, string pub, string type, string drawer, string date)
	{
		isbn = num; title = name; writer = author; publisher = pub; genre = type; artist = drawer; publishedDate = date;
	}
	//~Comic(); //destructor

	//get functions
	string getIsbn() { return isbn; }
	string getTitle() { return title; }
	string getWriter() { return writer; }
	string getPublisher() { return publisher; }
	string getGenre() { return genre; }
	string getArtist() { return artist; }
	string getPublishedDate() { return publishedDate; }

	//set functions
	void setIsbn(string num) { isbn = num; }
	void setTitle(string name) {
		name = uppercaseFirstLetters(name);
		title = name;
	}
	void setWriter(string author) {
		writer = uppercaseFirstLetters(writer);
		writer = author;
	}
	void setPublisher(string name) {
		name = uppercaseFirstLetters(name);
		publisher = name;
	}
	void setGenre(string type) {
		type = uppercaseFirstLetters(type);
		genre = type;
	}
	void setArtist(string drawer) {
		drawer = uppercaseFirstLetters(drawer);
		artist = drawer;
	}
	void setPublishedDate(string date) {
		date = uppercaseFirstLetters(date);
		publishedDate = date;
	}
	
	//overloading operator functions
	void operator = (const Comic &right);
	bool operator ==(const Comic &right);           //overload the == operator
	bool operator > (const Comic &right);     //overload the > operator
	bool operator < (const Comic &right);     //overload the < operator
	bool operator != (const Comic &right);    //overload the != operator
	

    void display()
    {
        cout << Comic::isbn << endl;
        cout << Comic::title << endl;
        cout << Comic::writer << endl;
        cout << Comic::publisher << endl;
        cout << Comic::genre << endl;
        cout << Comic::artist << endl;
        cout << Comic::publishedDate << endl;
    }

	//function to make the first letter in a word capitalized
	string uppercaseFirstLetters(string name)
	{
	    for (int i = 0; i < name.length(); i++)
        {
            if (islower(name[0]))
                name[0] = toupper(name[0]);

            if (name[i + 1] != NULL && name[i] == ' ' && islower(name[i + 1]))
                name[i + 1] = toupper(name[i + 1]);
        }

        return name;
	}

};

#endif



