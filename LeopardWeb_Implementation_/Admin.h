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
	string get_instructor(sqlite3* LW_DB, string crn);
	string get_instructor_fname(sqlite3* LW_DB, string crn);
	void addCourse(sqlite3* DB);
	void removeCourse(sqlite3* DB, int CRN);
	void addUser(sqlite3* DB);
	void removeUser(sqlite3* DB);
	void searchRoster(sqlite3* DB);
	void link_unlink_s(sqlite3* DB, string user_name, string crn, string in_title, string in_day, string in_location, string in_duration, string start, string end);
	void unlink_i(sqlite3* DB, string user_name, string crn);

	// destructor
	~Admin();
};
