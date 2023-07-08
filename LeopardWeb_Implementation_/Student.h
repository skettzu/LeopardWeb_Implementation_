#pragma once
#include "User.h"


class Student :
	public User {

public:
	// constructor
	Student();
	Student(string first);
	Student(string first, string last);
	Student(string first, string last, int ID);
	// method
	void searchAllCourse(sqlite3* DB);
	void searchByParameter(sqlite3* DB);
	void addCourse(sqlite3* DB);
	void dropCourse(sqlite3* DB);
	void printSchedule();

	//destructor
	~Student();

};
