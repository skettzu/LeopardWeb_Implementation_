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
	void addCourse(sqlite3* DB, int CRN, string Title, string Dept, int Time, string Day, string Sem, int yr, int cred);
	void removeCourse(sqlite3* DB, int CRN);
	void addUser();
	void removeUser();
	void addStudent();
	void removeStudent();
	void searchRoster();
	void printCourses();

	// destructor
	~Admin();

};
