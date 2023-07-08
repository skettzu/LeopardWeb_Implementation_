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

void Admin::searchAllCourse(sqlite3* DB) {
	//cout << "Student's searchCourse has been called" << endl;
	int exit = 1;
	string search_all = "SELECT * FROM COURSES;";
	exit = sqlite3_exec(DB, search_all.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Search Failed" << endl;
	}
	else cout << "Search Success" << endl;
}

void Admin::searchByParameter(sqlite3* DB) {
	int exit = 1;
	cout << "Enter parameter to seach course: ";
	string user_parameter;
	cin >> user_parameter;
	cin.ignore();
	//string search_parameter = ("SELECT * FROM COURSES WHERE Title = '" + user_parameter + "' OR department = '" + user_parameter + "' OR day = '" + user_parameter + "' OR semester = '" + user_parameter + "' OR CRN = " + user_parameter + " OR time = " + user_parameter + " OR year = " + user_parameter + " OR credits = " + user_parameter + "; ");
	//search for integer parameter
	string search_parameter = ("SELECT * FROM COURSES WHERE CRN = " + user_parameter + " OR time = " + user_parameter + " OR year = " + user_parameter + " OR credits = " + user_parameter + "; ");
	//cout << search_parameter << endl;
	exit = sqlite3_exec(DB, search_parameter.c_str(), callback, NULL, NULL);

	if (exit != SQLITE_OK) {
		//cout << "Search Error" << endl;
		//search for string parameter
		search_parameter = ("SELECT * FROM COURSES WHERE Title = '" + user_parameter + "' OR department = '" + user_parameter + "' OR day = '" + user_parameter + "' OR semester = '" + user_parameter + "';");
		//cout << search_parameter << endl;
		exit = sqlite3_exec(DB, search_parameter.c_str(), callback, NULL, NULL);
		/*
		if (exit != SQLITE_OK) {
			cout << "Search Error" << endl;
		}
		else cout << "Search Success" << endl;
		*/
	}
	//else cout << "Search Success" << endl;
}


// destructor

Admin::~Admin() {

}