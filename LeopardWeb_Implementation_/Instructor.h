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

	void addCourse(sqlite3* DB, string user_crn);
	void dropCourse(sqlite3* DB, string user_crn);
	void printRoster(sqlite3* DB);
	void printSchedule();
	void printClassList();

	// destructor
	~Instructor();

};
