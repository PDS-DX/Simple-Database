// Patient derives from Record
#include "Patient.h"
#include "Database.h"

using namespace std;


int main()
{
	Database<Patient> db;
	db.start();

    return 0;
}

