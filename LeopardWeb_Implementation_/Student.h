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
	void addCourse(sqlite3* DB, string user_crn, string student_name, string in_crn, string in_title, string in_day, string in_location, string in_duration, string start, string end);
	void dropCourse(sqlite3* DB, string user_crn);
	void printSchedule(sqlite3* DB, string student_name);
	void checkConflict(sqlite3* DB, string user_name);
	string get_day(sqlite3* LW_DB, string usr_name);
	string get_time(sqlite3* LW_DB, string usr_name);
	string get_crn(sqlite3* LW_DB, string usr_name);
	string get_dur(sqlite3* LW_DB, string usr_name);
	string get_etime(sqlite3* LW_DB, string usr_name);

	//destructor
	~Student();

};