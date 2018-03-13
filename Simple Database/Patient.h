#pragma once
#include "Record.h"

class Patient : public Record {
public:
	Patient();
	Patient(const Patient &);
	Patient & operator = (const Patient &);
	bool operator == (const Patient &) const;
	string getIndex() const
	{
		return (string)SSN;
	}
	void writeToFile(fstream &);
	void readFromFile(fstream &);
	int size() const;

protected:
	char * carrierName, *doctorName;
	const int carrierLength, doctorLength;
	ostream & writeToConsole(ostream&);
	friend ostream & operator << (ostream & out, Patient & p)
	{
		return p.writeToConsole(out);
	}
	istream& readFromConsole(istream&);
	friend istream & operator >> (istream & in, Patient & p)
	{
		return p.readFromConsole(in);
	}
};