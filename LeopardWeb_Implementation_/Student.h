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
	void searchCourse();
	void addCourse();
	void dropCourse();
	void printSchedule();

	//destructor
	~Student();


};
