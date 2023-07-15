#pragma once
#include "User.h"

class Instructor :
	public User {
	// attributes

public:
	// construstor

	Instructor();
	Instructor(string first);
	Instructor(string first, string last);
	Instructor(string first, string last, int ID);

	// method

	void searchAllCourse(sqlite3* DB);
	void searchByParameter(sqlite3* DB);
	void addCourse(sqlite3* DB, string user_crn);
	void dropCourse(sqlite3* DB);
	void printRoster(sqlite3* DB);
	void printSchedule();
	void printClassList();

	// destructor
	~Instructor();

};
