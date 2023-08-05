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

	virtual void addCourse(sqlite3* DB, string i_name);
	virtual void dropCourse(sqlite3* DB, string user_crn, string i_name);
	void printRoster(sqlite3* DB);
	virtual void printSchedule(sqlite3* DB, string i_name);

	// destructor
	~Instructor();

};
