#pragma once
#pragma warning(disable : 4996)
#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Record
{
public:
	Record();
	Record(Record &);
	~Record();
	Record & operator = (const Record &);
	bool operator == (const Record &) const;
	string getIndex() const
	{
		return (string)SSN;
	}
	void writeToFile(fstream &) const;
	void readFromFile(fstream &);
	int size() const;

protected:
	ostream & writeToConsole(ostream &)const;
	istream & readFromConsole(istream &);
	friend ostream & operator << (ostream & out, Record & r) {
		return r.writeToConsole(out);
	}
	friend istream & operator >> (istream & in, Record & r) {
		return r.readFromConsole(in);
	}

	const int firstNameLength, lastNameLength, cityLength;
	char SSN[10], ZIP[6], *firstName, *lastName, *city;
};

#endif