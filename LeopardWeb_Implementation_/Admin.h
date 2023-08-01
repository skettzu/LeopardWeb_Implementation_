#pragma once
#include "User.h"

class Admin :
	public User {
	// attributes

public:
	// construstor

	Admin();
	Admin(string first);
	Admin(string first, string last);
	Admin(string first, string last, int ID);

	// method
	void addCourse(sqlite3* DB, string course);
	void removeCourse(sqlite3* DB, int CRN);
	void addStudent(sqlite3* DB, string user_info, string user_type);
	void removeUser(sqlite3* DB, string in_id);
	void searchRoster(sqlite3* DB);

	// destructor
	~Admin();

};
