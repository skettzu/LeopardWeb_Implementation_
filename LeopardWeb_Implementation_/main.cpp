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
	string query;
	// Login Screen
	string username;
	string pwd;
	cout << "Welcome to LeopardWeb! Please Login Using Your Credentials: " << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> pwd;
	query = ("SELECT EXISTS(SELECT Username FROM CREDENTIAL WHERE Username = '" + username + "';)");
	//query = ("SELECT Username FROM CREDENTIAL WHERE Username = '" + username + "';");
	cout << query << endl;
	exit = sqlite3_exec(LW_DB, query.c_str(), callback, NULL, &messageError);
	if (exit != 0) {
		cout << "Incorrect Username" << endl;
		sqlite3_free(messageError);
	}
	else cout << "Correct Username" << endl; 
	query = ("SELECT Password FROM CREDENTIAL WHERE Password = '" + pwd + "';");
	cout << query << endl;
	exit = sqlite3_exec(LW_DB, query.c_str(), callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		cout << "Incorrect Password" << endl;
		sqlite3_free(messageError);
	}
	else cout << "Correct Password" << endl;
	
	
	return 0;
}