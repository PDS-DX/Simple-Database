#include "Record.h"


Record::Record() : firstNameLength(20), lastNameLength(20), cityLength(50) {
	firstName = new char[firstNameLength + 1];
	lastName = new char[lastNameLength + 1];
	city = new char[cityLength + 1];
	for (char & c : ZIP)
		c = '\0';
	for (char & c : SSN)
		c = '\0';
}

Record::Record(Record & r) : firstNameLength(20), lastNameLength(20), cityLength(50) {
	firstName = new char[firstNameLength + 1];
	lastName = new char[lastNameLength + 1];
	city = new char[cityLength + 1];
	strncpy(SSN, r.SSN, 9);
	strncpy(ZIP, r.ZIP, 5);
	strncpy(firstName, r.firstName, r.firstNameLength);
	strncpy(lastName, r.lastName, r.lastNameLength);
	strncpy(city, r.city, r.cityLength);
}

Record::~Record() {
	if (firstName)
		delete[] firstName;
	if (lastName)
		delete[] lastName;
	if (city)
		delete[] city;
}

Record & Record::operator = (const Record & r)
{
	strncpy(SSN, r.SSN, 9);
	strncpy(ZIP, r.ZIP, 5);
	strncpy(firstName, r.firstName, r.firstNameLength);
	strncpy(lastName, r.lastName, r.lastNameLength);
	strncpy(city, r.city, r.cityLength);
	return *this;
}

bool Record::operator == (const Record & r) const
{
	if 
	(
		(
			SSN == r.SSN &&
			ZIP == r.ZIP &&
			firstName == r.firstName &&
			lastName == r.lastName &&
			city == r.city
		) == 0
	)
		return true;
	else
		return false;
}

void Record::writeToFile(fstream & file) const {
	file.write(SSN, 9);
	file.write(firstName, firstNameLength);
	file.write(lastName, lastNameLength);
	file.write(city, cityLength);
	file.write(ZIP, 5);
}

void Record::readFromFile(fstream & file) {
	file.read(SSN, 9);
	file.read(firstName, firstNameLength);
	file.read(lastName, lastNameLength);
	file.read(city, cityLength);
	file.read(ZIP, 5);
}

ostream & Record::writeToConsole(ostream & out) const {
	out << "SSN: " << SSN << endl;
	out << "First Name: " << firstName << endl;
	out << "Last Name: " << lastName << endl;
	out << "City: " << city << endl;
	out << "ZIP: " << ZIP;

	return out;
}

istream & Record::readFromConsole(istream & in) {
	char s[80];

	cout << "SSN: ";
	in.getline(s, 80);
	strncpy(SSN, s, 9);

	cout << "First Name: ";
	in.getline(s, 80);
	strncpy(firstName, s, firstNameLength);

	cout << "Last Name: ";
	in.getline(s, 80);
	strncpy(lastName, s, lastNameLength);

	cout << "City: ";
	in.getline(s, 80);
	strncpy(city, s, cityLength);

	cout << "ZIP: ";
	in.getline(s, 80);
	strncpy(ZIP, s, 5);

	return in;
}

int Record::size() const
{
	return 9 + 5 + firstNameLength + lastNameLength + cityLength;
}

