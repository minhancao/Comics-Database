#include "Comic.h"

void Comic::operator=(const Comic & right)
{
	isbn = right.isbn;
	title = right.title;
	writer = right.writer;
	publisher = right.publisher;
	genre = right.genre;
	artist = right.artist;
	publishedDate = right.publishedDate;
}

bool Comic::operator==(const Comic & right)
{
	bool flag = false;
	if (isbn == right.isbn)
	{
		flag = true;
	}
	return flag;
}

bool Comic::operator>(const Comic & right)
{
	bool flag = false;
	if (isbn>right.isbn)
	{
		flag = true;
	}
	return flag;
}

bool Comic::operator<(const Comic & right)
{
	bool flag = false;
	if (isbn<right.isbn)
	{
		flag = true;
	}
	return flag;
}

bool Comic::operator!=(const Comic & right)
{
	bool flag = false;
	if (isbn != right.isbn)
	{
		flag = true;
	}
	return flag;
}

