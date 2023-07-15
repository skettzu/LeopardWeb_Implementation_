#include "User.h"

using std::endl;

// constructor

User::User() {
	first_name = "Bob";
	last_name = "Smith";
	ID = 0000;
}

User::User(string first) {
	first_name = first;
	last_name = "Smith";
	ID = 0000;
}

User::User(string first, string last) {
	first_name = first;
	last_name = last;
	ID = 0000;
}

User::User(string first, string last, int in_ID) {
	first_name = first;
	last_name = last;
	ID = in_ID;
}

// method
static int callback(void* data, int argc, char** argv, char** azColName) {
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

void User::setFirstName(string first) {
	first_name = first;
}
void User::setLastName(string last) {
	last_name = last;
}
void User::setID(int in_ID) {
	ID = in_ID;
}
void User::printAllInfo() {
	cout << "First name is " << first_name << endl;
	cout << "Last name is " << last_name << endl;
	cout << "ID is " << ID << endl;
}

void User::searchAllCourse(sqlite3* DB) {
	//cout << "Student's searchCourse has been called" << endl;
	int exit = 1;
	string search_all = "SELECT * FROM COURSES;";
	exit = sqlite3_exec(DB, search_all.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Search Failed" << endl;
	}
	else cout << "Search Success" << endl;
}

void User::searchByParameter(sqlite3* DB, string user_parameter) {
	int exit = 1;
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
		
		if (exit != SQLITE_OK) {
			cout << "Search Error" << endl;
		}
		//else cout << "Search Success" << endl;
		
	}
	else cout << "Search Success" << endl;
}
int User::Login(sqlite3* LW_DB, string usr, string pwd) {
	string query = "SELECT 1 FROM CREDENTIAL WHERE (Username = '" + usr + "' AND Password = '" + pwd + "'); ";	// SQL statement selecting 1 if there is the username + pwd combo
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;
		return 0;
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}
	int count = sqlite3_column_int(stmt, 0); // Get the count from the result set
	if (count > 0) {
		// print welcome statement
		cout << "Welcome ";
		query = ("SELECT Firstname FROM CREDENTIAL WHERE Username = '" + usr + "';");
		rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
		if (rc != SQLITE_OK) {
			cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;
			return 0;
		}
		rc = sqlite3_step(stmt); // Execute the statement
		if (rc != SQLITE_ROW) {
			cout << "Cannot compile statement" << endl;
			return 0;
		}
		cout << sqlite3_column_text(stmt, 0);	// get resulting name from result set
		cout << " to LeopardWeb!" << endl;
		sqlite3_finalize(stmt);
		return 1;
	}
}

// destructor

User::~User() {

}