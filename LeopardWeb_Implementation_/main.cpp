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

int check_credential(sqlite3* LW_DB, string usr, string pwd) {	// By Derek
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
static int check_class(sqlite3* LW_DB, string usr) {	// By Derek
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
string get_fname(sqlite3* LW_DB, string usr) {	// By Derek
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
string get_lname(sqlite3* LW_DB, string usr) {	// By Derek
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
int get_WID(sqlite3* LW_DB, string usr) {	// By Derek
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

// User Test Cases
void user_test_cases() {
	// Put All Tests That Pertain to All Classes In This Method
	sqlite3* DB_Test;
	int exit = 1;
	exit = sqlite3_open("LeopardWeb_Implementation.db", &DB_Test); // open the database
	if (exit != SQLITE_OK) {
		cout << "error";
	}
	else {
		cout << "open success" << endl;
	}
	User default_test("Jonathan", "Smith", 8888888);
	bool check = true;
	// Login Test:
	// *********************Start of Login Test Cases***********************
	// Student Login:
	string s_username = "dhuang9";
	string s_pwd = "bob1";
	if (default_test.Login(DB_Test, s_username, s_pwd) == 0) {
		cout << "Student Test Failed" << endl;
		check = false;
	}
	else {
		cout << "Student Test Passed!" << endl;
	}
	// Admin Login:
	string a_username = "bob123";
	string a_pwd = "bob";
	if (default_test.Login(DB_Test, a_username, a_pwd) == 0) {
		cout << "Admin Test Failed" << endl;
		check = false;
	}
	else {
		cout << "Admin Test Passed!" << endl;
	}
	// Instructor Login:
	string i_username = "hphan6";
	string i_pwd = "bob2";
	if (default_test.Login(DB_Test, i_username, i_pwd) == 0) {
		cout << "Instructor Test Failed" << endl;
		check = false;
	}
	else {
		cout << "Instructor Test Passed!" << endl;
	}
	// Check to see if tests are giving false positive
	if (default_test.Login(DB_Test, "username", "password") == 1) {
		cout << "Tests are faulty!" << endl;
		check = false;
	}
	else {
		cout << "Tests are valid!" << endl;
	}
	if (check == false) {
		cout << "Login Test Has Failed!" << endl;
	}
	else {
		cout << "All Login Tests Passed!" << endl;
	}
	// Search All Courses 
	
	// Logout Test (DB Close)
	exit = sqlite3_close(DB_Test); // close the database
	if (exit == SQLITE_OK) {
		cout << "Logout Successful" << endl;
	}
	else {
		cout << "Logout Error: ";
		cout << to_string(exit) << endl;
		
	}
	// *********************End of Login Test Cases***********************

}
// Admin Test Cases
void admin_test_cases() {
	// Add/Remove Test Cases:

}
// Instructor Test Cases
void prof_test_cases() {
	sqlite3* DB_Test;
	int exit = 1;
	exit = sqlite3_open("LeopardWeb_Implementation.db", &DB_Test); // open the database
	if (exit != SQLITE_OK) {
		cout << "error";
	}
	else {
		cout << "open success" << endl;
	}
	User default_test("Jonathan", "Smith", 8888888);
	bool check = true;

	string p_username = "hphan6";
	string p_pwd = "bob2";
	int p_wid = get_WID(DB_Test, p_username);

	Instructor instructor(p_username, p_pwd, p_wid);
	instructor.Login(DB_Test, p_username, p_pwd);

	string crn_test = "33946";
	instructor.addCourse(DB_Test, crn_test);


}
// Student Test Cases
void student_test_cases() {

}

int main() {
	// Run All Test Cases Before Program Is Ran
	//user_test_cases();
	//admin_test_cases();
	prof_test_cases();
	//student_test_cases();

	// Default User
	User default_usr("Bob");
	// Database 
	sqlite3* LW_DB;
	int exit = 1;
	// Don't forget to close db at the end of program
	exit = sqlite3_open("LeopardWeb_Implementation.db", &LW_DB); // open the database
	if (exit != SQLITE_OK) {
		cout << "error" << endl;
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
	if (default_usr.Login(LW_DB, username, pwd) == 0) {	// check credential using sqlite3_column_int()
		return 0;
	}
	// display menu according to User Type
	int user_input = 10;
	while (1) {
		if (check_class(LW_DB, username) == 1) {	// Instructor Menu
			string i_username;
			string i_pwd;
			string fname = get_fname(LW_DB, username); //get first name of the instructor
			string lname = get_lname(LW_DB, username); //get last name of the instructor
			int WID = get_WID(LW_DB, username); // get WID of the instructor
			Instructor instructor(fname, lname, WID); //create an instructor object

			cout << "1. Add Course to Semester Schedule" << endl;
			cout << "2. Remove Course to Semester Schedule" << endl;
			cout << "3. Assemble and Print Course Roster" << endl;
			cout << "4. Search All Courses" << endl;
			cout << "5. Search Course Based on Parameter" << endl;
			cout << "6. Logout" << endl;
			cout << "7. Close LeopardWeb" << endl;
			cin >> user_input;
			string user_crn;
			switch (user_input) {
			case 1:
				//call add course method for instructor
				cout << "Enter CRN: ";
				cin >> user_crn;
				instructor.addCourse(LW_DB, user_crn);
				break;
			case 2:
				//call droup course method for instructor
				instructor.dropCourse(LW_DB);
				break;
			case 3:
				//call instructor's print roster method
				instructor.printRoster(LW_DB);
				break;
			case 4:
				//instructor search all course
				instructor.searchAllCourse(LW_DB);
				break;
			case 5:
				//instructor search course by parameter
				instructor.searchByParameter(LW_DB);
				break;
			case 6:
				//log out	// By Derek
				cout << "Logged out!" << endl;
				// login screen
				cout << "Welcome to LeopardWeb! Please Login Using Your Credentials: " << endl;
				cout << "Username: ";
				cin >> i_username;
				username = i_username;
				cout << "Password: ";
				cin >> i_pwd;
				pwd = i_pwd;
				instructor.Login(LW_DB, i_username, i_pwd); // Relogin
				break;
			case 7:
				// Close program
				sqlite3_close(LW_DB); // close the database
				cout << "LeopardWeb Closed!" << endl;
				return 0;
			}
		}
		else if (check_class(LW_DB, username) == 2) {		// Admin Menu
			string a_username;
			string a_pwd;
			string fname = get_fname(LW_DB, username); //get first name of admin
			string lname = get_lname(LW_DB, username); //get last name of admin
			int WID = get_WID(LW_DB, username);  //get WID of admin
			Admin user(fname, lname, WID); //create admin object
			string in_course;
			
			cout << "1. Add Course from System" << endl;
			cout << "2. Remove Course from System" << endl;
			cout << "3. Search All Courses" << endl;
			cout << "4. Search Course Based on Parameter" << endl;
			cout << "5. Logout" << endl;
			cout << "6. Close LeopardWeb" << endl;
			cin >> user_input;
			switch (user_input) {
			case 1:
				int in_CRN, in_Time, in_yr, in_cred;	// By Derek
				char in_Title, in_Day, in_Dept, in_Sem;
				cout << "What is the CRN, 'Title', 'Department', Time, 'Day', 'Semester', year, credit for your course?" << endl;
				cout << "Please input each element separated by commas, with '' surrounding the each input that requires" << endl;
				cin.ignore();
				getline(cin, in_course);	
				user.addCourse(LW_DB, in_course);
				break;
			case 2:
				int rem_CRN;	// By Derek
				cout << "What is the CRN of the course you would like to remove?" << endl;
				cin >> rem_CRN;
				user.removeCourse(LW_DB, rem_CRN);
				break;
			case 3:
				//admin search and print all course
				user.searchAllCourse(LW_DB);
				break;
			case 4:
				//admin search and print course by parameter
				user.searchByParameter(LW_DB);
				break;
			case 5:
				//log out	// By Derek
				cout << "Logged out!" << endl;
				// login screen
				cout << "Welcome to LeopardWeb! Please Login Using Your Credentials: " << endl;
				cout << "Username: ";
				cin >> a_username;
				username = a_username;
				cout << "Password: ";
				cin >> a_pwd;
				pwd = a_pwd;
				user.Login(LW_DB, a_username, a_pwd); // Relogin
				break;
			case 6:
				// Close program
				sqlite3_close(LW_DB); // close the database
				cout << "LeopardWeb Closed!" << endl;
				return 0;
			}
		}
		else if (check_class(LW_DB, username) == 3) {		// Student Menu
			string s_username;
			string s_pwd;
			string fname = get_fname(LW_DB, username); // get student first name
			string lname = get_lname(LW_DB, username); //get student last name
			int WID = get_WID(LW_DB, username); //get student WID
			//cout << fname << " " << lname << " " << WID << endl;
			Student student(fname, lname, WID); //create student object

			cout << "1. Add Course to Semester Schedule" << endl;
			cout << "2. Remove Course to Semester Schedule" << endl;
			cout << "3. Search All Courses" << endl;
			cout << "4. Search Course Based on Parameter" << endl;
			cout << "5. Logout" << endl;
			cout << "6. Close LeopardWeb" << endl;
			cin >> user_input;
			switch (user_input) {
			case 1:
				//student add course to schedule
				student.addCourse(LW_DB);
				break;
			case 2:
				//student drop course from schedule
				student.dropCourse(LW_DB);
				break;
			case 3:
				//student search all course
				student.searchAllCourse(LW_DB);
				break;
			case 4:
				//student search course by parameter
				student.searchByParameter(LW_DB);
				break;
			case 5:
				//log out	// By Derek
				cout << "Logged out!" << endl;
				// login screen
				cout << "Welcome to LeopardWeb! Please Login Using Your Credentials: " << endl;
				cout << "Username: ";
				cin >> s_username;
				username = s_username;
				cout << "Password: ";
				cin >> s_pwd;
				pwd = s_pwd;
				student.Login(LW_DB, s_username, s_pwd); // Relogin
				break;
			case 6: 
				// Close program
				sqlite3_close(LW_DB); // close the database
				cout << "LeopardWeb Closed!" << endl;
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	return 0;
}

