#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>

using std::cout;
using std::cin;
using std::string;

class User {
protected:
	// attributes
	string first_name;
	string last_name;
	int ID;
public:
	// Constructor

	User();
	User(string first);
	User(string first, string last);
	User(string first, string last, int ID);

	// Method

	void setFirstName(string first);
	void setLastName(string last);
	void setID(int ID);
	void printAllInfo();
	int Login(sqlite3* LW_DB, string usr, string pwd);
	void searchAllCourse(sqlite3* DB);
	void searchByParameter(sqlite3* DB, string user_parameter);

	// Destructor
	~User();

};