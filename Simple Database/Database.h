#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>

template <class T>
class Database {
public:
	Database<T>();
	void start();

	// run initialize if your db file does not already exist
	void initialize();

private:
	fstream database;
	char fileName[50];
	ostream & print(ostream &);
	void add(T&);
	bool find(const T&);
	bool find(const string &);
	void modify(const T&);
	void modify(const string &);
	void erase(const string &);
	friend ostream & operator <<(ostream & out, Database & db)
	{
		return db.print(out);
	}
};

template <class T>
Database<T>::Database()
{
}

template <class T>
void Database<T>::start()
{
	cout << "Database File Name: ";
	cin.getline(fileName, 50);
	bool flag = true;
	T tmp;
	string index;
	while (flag)
	{
		cout << "1) Add\n2) Find\n3) Modify\n4) Delete\n5) Print All Records\n6) Exit" << endl;
		char c;
		cin >> c;
		cin.ignore();
		switch (c)
		{
		case '1':
			cin >> tmp;
			add(tmp);
			cout << "Adding record." << endl;
			break;
		case '2':
			cout << "Input record index:";
			cin >> index;
			cin.ignore();
			if (find(index))
				cout << "Record found." << endl;
			else
				cout << "Record not found." << endl;
			break;
		case '3':
			cout << "Existing record index: ";
			cin >> index;
			cin.ignore();
			modify(index);
			cout << "Modifying record." << endl;
			break;
		case '4':
			cout << "Existing record index: ";
			cin >> index;
			cin.ignore();
			erase(index);
			break;
		case '5':
			print(cout);
			break;
		case '6':
			cout << "Program exiting." << endl;
			database.close();
			flag = false;
			break;
		default:
			cout << "Invalid Input. Try again." << endl;
		}
	}
}

template<class T>
void Database<T>::initialize()
{
	database.open(fileName, ios_base::out | ios_base::binary);
	database.close();
}

template <class T>
ostream & Database<T>::print(ostream & out)
{
	database.open(fileName, ios_base::in);
	T tmp;
	while (true)
	{
		tmp.readFromFile(database);
		if (!database.eof())
			out << tmp << endl << endl;
		else break;
	}
	database.clear();
	database.close();
	return out;
}

template <class T>
void Database<T>::add(T & t)
{
	database.open(fileName, ios_base::in | ios_base::out | ios_base::app | ios_base::binary);
	if (database.is_open())
	{
		t.writeToFile(database);
		database.clear();
		database.close();
	}
	else
	{
		cout << "Database could not be opened." << endl;
		database.clear();
	}
}

template <class T>
bool Database<T>::find(const T & t)
{
	database.open(fileName, ios_base::in | ios_base::out | ios_base::binary);
	if (database.is_open())
	{
		T tmp;
		while (true)
		{
			tmp.readFromFile(database);
			if (!database.eof())
			{
				if (tmp == t)
				{
					database.clear();
					database.close();
					return true;
				}
			}
			else 
			{
				database.clear();
				database.close();
				return false;
			}
		}
	}
	else
	{
		cout << "Database could not be opened." << endl;
		database.clear();
		return false;
	}
}

template <class T>
bool Database<T>::find(const string & index)
{
	database.open(fileName, ios_base::in);
	if (database.is_open())
	{
		T tmp;
		while (true)
		{
			tmp.readFromFile(database);
			if (!database.eof())
			{
				if (index == tmp.getIndex())
				{
					database.clear();
					database.close();
					return true;
				}
			}
			else
			{
				database.clear();
				database.close();
				return false;
			}
		}
	}
	else
	{
		database.clear();
		cout << "Database could not be opened." << endl;
		return false;
	}
}

template <class T>
void Database<T>::modify(const T & t)
{
	database.open(fileName, ios_base::in | ios_base::out | ios_base::binary);
	if (database.is_open())
	{
		T tmp;
		while (true)
		{
			auto a = database.tellp();
			tmp.readFromFile(database);
			if (!database.eof())
			{
				if (tmp == t)
				{
					database.seekp(a);
					t.writeToFile(database);
					database.clear();
					database.close();
					cout << "Record successfully updated." << endl;
					return;
				}
			}
			else
			{
				database.clear();
				database.close();
				cout << "Record does not exist." << endl;
				return;
			}
		}
	}
	else
	{
		cout << "Database could not be opened." << endl;
		database.clear();
	}
}

template <class T>
void Database<T>::modify(const string & index)
{
	database.open(fileName, ios_base::in | ios_base::out | ios_base::binary);
	if (database.is_open())
	{
		T tmp;
		while (true)
		{
			auto a = database.tellp();
			tmp.readFromFile(database);
			if (!database.eof())
			{
				if (tmp.getIndex() == index)
				{
					T updatedRecord;
					cout << "Update Record\n" << endl;
					cin >> updatedRecord;
					cin.ignore();
					database.seekp(a);
					updatedRecord.writeToFile(database);
					database.clear();
					database.close();
					cout << "Record successfully updated." << endl;
					return;
				}
			}
			else
			{
				database.clear();
				database.close();
				cout << "Record does not exist." << endl;
				return;
			}
		}
	}
	else
	{
		cout << "Database could not be opened." << endl;
		database.clear();
	}
}

template <class T>
void Database<T>::erase(const string & str)
{
	// write db to swap excluding record(s) to be erased
	fstream swap("swap", ios_base::out | ios_base::binary);
	database.open(fileName, ios_base::in | ios_base::binary);
	T tmp;
	while (true)
	{
		tmp.readFromFile(database);
		if (!database.eof())
		{
			if (tmp.getIndex() != str)
			{
				tmp.writeToFile(swap);
			}
		}
		else
		{
			database.clear();
			database.close();
			swap.clear();
			swap.close();
			break;
		}
	}

	// rename swap to db name and delete old file
	remove(fileName);
	rename("swap", fileName);
}

#endif