#include <iostream>
#include <sqlite3.h>
#include <string>
#include <stdio.h>

using namespace std;


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

int check_credential(sqlite3* LW_DB, string usr, string pwd) {
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
	else {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}

}

static int check_class(sqlite3* LW_DB, string usr) {
	/*
	Returned values as follows:
	Instructor is 1 
	Admin is 2
	Student is 3
	*/
	// check if instructor
	string query = "SELECT 1 FROM CREDENTIAL WHERE (Username = '" + usr + "' AND UserType = 'Instructor'); ";	// SQL statement selecting 1 if there is the username + UserType combo
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;
		return 0;
	}
	rc = sqlite3_step(stmt); // Execute the statement
	
	int count = sqlite3_column_int(stmt, 0); // Get the count from the result set
	if (count > 0) {
		return 1;
	}
	// check if admin
	query = "SELECT 1 FROM CREDENTIAL WHERE (Username = '" + usr + "' AND UserType = 'Admin'); ";	// SQL statement selecting 1 if there is the username + UserType combo
	rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;
		return 0;
	}
	rc = sqlite3_step(stmt); // Execute the statement

	count = sqlite3_column_int(stmt, 0); // Get the count from the result set
	if (count > 0) {
		return 2;
	}
	// check if student
	query = "SELECT 1 FROM CREDENTIAL WHERE (Username = '" + usr + "' AND UserType = 'Student'); ";	// SQL statement selecting 1 if there is the username + UserType combo
	rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;
		return 0;
	}
	rc = sqlite3_step(stmt); // Execute the statement
	
	count = sqlite3_column_int(stmt, 0); // Get the count from the result set
	if (count > 0) {
		return 3;
	}
}
int main() {
	// Database 
	sqlite3* LW_DB;
	int exit = 1;
	// Don't forget to close db at the end of program
	exit = sqlite3_open("LeopardWeb_Implementation.db", &LW_DB); // open the database
	if (exit != SQLITE_OK) {
		cout << "error";
	}
	else {
		cout << "open success" << endl;
	}
	char* messageError;
	// Login Screen
	string username;
	string pwd;
	cout << "Welcome to LeopardWeb! Please Login Using Your Credentials: " << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> pwd;
	if (check_credential(LW_DB, username, pwd) == 0) {	// check credential using sqlite3_column_int()
		return 0;
	}
	// display menu according to User Type
	if (check_class(LW_DB, username) == 1) {	// Instructor Menu
		cout << "1. Add Course to Semester Schedule" << endl;
		cout << "2. Remove Course to Semester Schedule" << endl;
		cout << "3. Assemble and Print Course Roster" << endl;
		cout << "4. Search All Courses" << endl;
		cout << "5. Search Course Based on Parameter" << endl;
		cout << "6. Logout" << endl;
	}
	else if (check_class(LW_DB, username) == 2) {		// Admin Menu
		cout << "1. Add Course from System" << endl;
		cout << "2. Remove Course from System" << endl;
		cout << "3. Search All Courses" << endl;
		cout << "4. Search Course Based on Parameter" << endl;
		cout << "5. Logout" << endl;
	}
	else if (check_class(LW_DB, username) == 3) {		// Student Menu
		cout << "1. Add Course to Semester Schedule" << endl;
		cout << "2. Remove Course to Semester Schedule" << endl;
		cout << "3. Search All Courses" << endl;
		cout << "4. Search Course Based on Parameter" << endl;
		cout << "5. Logout" << endl;
	}
	else {
		return 0;
	}
	return 0;
}

