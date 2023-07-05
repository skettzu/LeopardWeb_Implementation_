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
	string query = "SELECT 1 FROM CREDENTIAL WHERE Username = '" + usr + "';";	// SQL statement selecting 1 and inserting into result set if username is found else select 0
	sqlite3_stmt* stmt;
	int result;
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
	}
	else {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}

	query = ("SELECT 1 FROM CREDENTIAL WHERE Password = '" + pwd + "';");	// SQL statement selecting 1 and inserting into result set if password is found else select 0

	rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;
		return 0;
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}

	count = sqlite3_column_int(stmt, 0); // Get the count from the result set
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
		return 1;
	}
	else {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}

}

int main() {
	// Database 
	sqlite3* LW_DB;
	int exit = 1;

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
	check_credential(LW_DB, username, pwd);	// check credential using sqlite3_column_int()

	return 0;
}

