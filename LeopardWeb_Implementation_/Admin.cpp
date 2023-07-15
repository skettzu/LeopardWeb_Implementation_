#include "Admin.h"

using std::endl;

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

// constructor

Admin::Admin() {
	first_name = "Bob";
	last_name = "Smith";
	ID = 0000;
}

Admin::Admin(string first) {
	first_name = first;
	last_name = "Smith";
	ID = 0000;
}

Admin::Admin(string first, string last) {
	first_name = first;
	last_name = last;
	ID = 0000;
}

Admin::Admin(string first, string last, int in_ID) {
	first_name = first;
	last_name = last;
	ID = in_ID;
}

// method

void Admin::addCourse(sqlite3* DB, string course) {
	string query = "INSERT INTO COURSES VALUES(" + course + ");";	// Create Query to Add to Course to DB
	int exit = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);	// Execute the Query
	if (exit != SQLITE_OK) {
		cout << "Insert Error: " << sqlite3_errmsg(DB) << endl;
	}
	else {
		cout << "Added Course Successfully!" << endl;
	}
}
void Admin::removeCourse(sqlite3* DB, int CRN) {
	string query = "DELETE FROM COURSES WHERE CRN = " + std::to_string(CRN);	// Create Query to Remove Course from DB
	int exit = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);	// Execute the Query
	if (exit != SQLITE_OK) {
		cout << "Delete Error: " << sqlite3_errmsg(DB) << endl;
	}
	else {
		cout << "Removed Course Successfully!" << endl;
	}
}
void Admin::addUser() {
	cout << "Admin's addUser has been called" << endl;
}
void Admin::removeUser() {
	cout << "Admin's removeUser has been called" << endl;
}
void Admin::addStudent() {
	cout << "Admin's addStudent has been called" << endl;
}
void Admin::removeStudent() {
	cout << "Admin's removeStudent has been called" << endl;
}
void Admin::searchRoster() {
	cout << "Admin's searchRoster has been called" << endl;
}
void Admin::printCourses() {
	cout << "Admin's printCourse has been called" << endl;
}


// destructor

Admin::~Admin() {

}