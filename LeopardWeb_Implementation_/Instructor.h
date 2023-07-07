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
	void printSchedule();
	void printClassList();
	void searchCourse();

	// destructor
	~Instructor();

};
