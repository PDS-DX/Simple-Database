#include "Patient.h"

Patient::Patient() : carrierLength(50), doctorLength(20)
{
	Record();
	carrierName = new char[carrierLength + 1];
	doctorName = new char[doctorLength + 1];
}

Patient::Patient(const Patient & p) : carrierLength(50), doctorLength(20)
{
	strncpy(SSN, p.SSN, 9);
	strncpy(firstName, p.firstName, p.firstNameLength);
	strncpy(lastName, p.lastName, p.lastNameLength);
	strncpy(city, p.city, p.cityLength);
	strncpy(ZIP, p.ZIP, 5);
	strncpy(carrierName, p.carrierName, p.carrierLength);
	strncpy(doctorName, p.doctorName, p.doctorLength);
}

Patient & Patient::operator = (const Patient & p)
{
	strncpy(SSN, p.SSN, 9);
	strncpy(firstName, p.firstName, p.firstNameLength);
	strncpy(lastName, p.lastName, p.lastNameLength);
	strncpy(city, p.city, p.cityLength);
	strncpy(ZIP, p.ZIP, 5);
	strncpy(carrierName, p.carrierName, p.carrierLength);
	strncpy(doctorName, p.doctorName, p.doctorLength);
	return *this;
}

bool Patient::operator == (const Patient & p) const
{
	cout << "SSN comparison: ";
	cout << strcmp(SSN, p.SSN) << endl;
	cout << "city comparison: ";
	cout << strcmp(city, p.city) << endl;
	if (
			(
			SSN == p.SSN &&
			ZIP == p.ZIP &&
			firstName == p.firstName &&
			lastName == p.lastName &&
			city == p.city &&
			carrierName == p.carrierName &&
			doctorName == p.doctorName
			) 
			== 0
		)
		return true;
	else
		return false;
}

void Patient::writeToFile(fstream & file)
{
	Record::writeToFile(file);
	file.write(carrierName, carrierLength);
	file.write(doctorName, doctorLength);
}

void Patient::readFromFile(fstream & file)
{
	Record::readFromFile(file);
	file.read(carrierName, carrierLength);
	file.read(doctorName, doctorLength);
}

istream & Patient::readFromConsole(istream & in)
{
	Record::readFromConsole(in);
	char s[80];
	
	cout << "Carrier Name: ";
	in.getline(s, 80);
	strncpy(carrierName, s, carrierLength);

	cout << "Doctor Name: ";
	in.getline(s, 80);
	strncpy(doctorName, s, doctorLength);

	return in;

}

ostream & Patient::writeToConsole(ostream & out)
{
	Record::writeToConsole(out);
	out << endl << "Carrier Name: " << carrierName << endl;
	out << "Doctor Name: " << doctorName;

	return out;
}

int Patient::size() const
{
	return Record::size() + carrierLength + doctorLength;
}