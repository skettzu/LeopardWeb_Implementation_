#include <iostream>
#include <sqlite3.h>
#include <string>
#include <stdio.h>
#include "Admin.h"
#include "Student.h"
#include "Instructor.h"
#include "User.h"

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
string get_fname(sqlite3* LW_DB, string usr) {
	string query = "SELECT Firstname FROM CREDENTIAL WHERE Username = '" + usr + "';";	// SQL statement selecting User's first name
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "User Doesn't exist" << endl;	// Check if User exists
	}
	size_t length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
	int size = length * sizeof(unsigned char);  // calculate the total size

	string result = "";
	for (int i = 0; i < size; i++) {
		char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
		result = result + temp;	// append temp to resulting string
	}
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}
string get_lname(sqlite3* LW_DB, string usr) {
	string query = "SELECT Lastname FROM CREDENTIAL WHERE Username = '" + usr + "';";	// SQL statement selecting User's first name
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "User Doesn't exist" << endl;	// Check if User exists
	}
	size_t length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
	int size = length * sizeof(unsigned char);  // calculate the total size

	string result = "";
	for (int i = 0; i < size; i++) {
		char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
		result = result + temp;	// append temp to resulting string
	}
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}
int get_WID(sqlite3* LW_DB, string usr) {
	string query = "SELECT WID FROM CREDENTIAL WHERE Username = '" + usr + "';";	// SQL statement selecting User's first name
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "User Doesn't exist" << endl;	// Check if User exists
	}
	int result = sqlite3_column_int(stmt, 0);	// grab WID from resulting table
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
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
	int user_input = 10;
	while (1) {
		if (check_class(LW_DB, username) == 1) {	// Instructor Menu
			string fname = get_fname(LW_DB, username);
			string lname = get_lname(LW_DB, username);
			int WID = get_WID(LW_DB, username);
			Instructor instructor(fname, lname, WID);

			cout << "1. Add Course to Semester Schedule" << endl;
			cout << "2. Remove Course to Semester Schedule" << endl;
			cout << "3. Assemble and Print Course Roster" << endl;
			cout << "4. Search All Courses" << endl;
			cout << "5. Search Course Based on Parameter" << endl;
			cout << "6. Logout" << endl;
			cin >> user_input;
			switch (user_input) {
			case 1:
				instructor.addCourse(LW_DB);
				break;
			case 2:
				instructor.dropCourse(LW_DB);
				break;
			case 3:
				instructor.printRoster(LW_DB);
				break;
			case 4:
				instructor.searchAllCourse(LW_DB);
				break;
			case 5:
				instructor.searchByParameter(LW_DB);
				break;
			case 6:
				sqlite3_close(LW_DB); // close the database
				cout << "Logged out!" << endl;
				return 0;
				break;
			}
		}
		else if (check_class(LW_DB, username) == 2) {		// Admin Menu
			string fname = get_fname(LW_DB, username);
			string lname = get_lname(LW_DB, username);
			int WID = get_WID(LW_DB, username);
			Admin user(fname, lname, WID);
			string in_course;
			
			cout << "1. Add Course from System" << endl;
			cout << "2. Remove Course from System" << endl;
			cout << "3. Search All Courses" << endl;
			cout << "4. Search Course Based on Parameter" << endl;
			cout << "5. Logout" << endl;
			cin >> user_input;
			switch (user_input) {
			case 1:
				int in_CRN, in_Time, in_yr, in_cred;
				char in_Title, in_Day, in_Dept, in_Sem;
				cout << "What is the CRN, 'Title', 'Department', Time, 'Day', 'Semester', year, credit for your course?" << endl;
				cout << "Please input each element separated by commas, with '' surrounding the each input that requires" << endl;
				cin.ignore();
				getline(cin, in_course);	
				user.addCourse(LW_DB, in_course);
				break;
			case 2:
				int rem_CRN;
				cout << "What is the CRN of the course you would like to remove?" << endl;
				cin >> rem_CRN;
				user.removeCourse(LW_DB, rem_CRN);
				break;
			case 3:
				user.searchAllCourse(LW_DB);
				break;
			case 4:
				user.searchByParameter(LW_DB);
				break;
			case 5:
				sqlite3_close(LW_DB); // close the database
				cout << "Logged out!" << endl;
				return 0;
				break;
			}
		}
		else if (check_class(LW_DB, username) == 3) {		// Student Menu
			string fname = get_fname(LW_DB, username);
			string lname = get_lname(LW_DB, username);
			int WID = get_WID(LW_DB, username);
			//cout << fname << " " << lname << " " << WID << endl;
			Student student(fname, lname, WID);

			cout << "1. Add Course to Semester Schedule" << endl;
			cout << "2. Remove Course to Semester Schedule" << endl;
			cout << "3. Search All Courses" << endl;
			cout << "4. Search Course Based on Parameter" << endl;
			cout << "5. Logout" << endl;
			cin >> user_input;
			switch (user_input) {
			case 1:
				student.addCourse(LW_DB);
				break;
			case 2:
				student.dropCourse(LW_DB);
				break;
			case 3:
				student.searchAllCourse(LW_DB);
				break;
			case 4:
				student.searchByParameter(LW_DB);
				break;
			case 5:
				sqlite3_close(LW_DB); // close the database
				cout << "Logged out!" << endl;
				return 0;
				break;
			}
		}
		else {
			return 0;
		}
	}
	return 0;
}

