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