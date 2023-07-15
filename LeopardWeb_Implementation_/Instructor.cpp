#include "Instructor.h"

using std::endl;

// constructor

Instructor::Instructor() {
	first_name = "Bob";
	last_name = "Smith";
	ID = 0000;
}

Instructor::Instructor(string first) {
	first_name = first;
	last_name = "Smith";
	ID = 0000;
}

Instructor::Instructor(string first, string last) {
	first_name = first;
	last_name = last;
	ID = 0000;
}

Instructor::Instructor(string first, string last, int in_ID) {
	first_name = first;
	last_name = last;
	ID = in_ID;
}

// method
static int callback(void* data, int argc, char** argv, char** azColName) {
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

void Instructor::printSchedule() {
	cout << "Instructor's printSchedule has been called" << endl;
}
void Instructor::printClassList() {
	cout << "Instructor's printClassList has been called" << endl;
}

void Instructor::addCourse(sqlite3* DB, string user_crn) {
	//cout << "Student's addCourse has been called" << endl;
	int exit = 1;
	string insert_s_course;
	insert_s_course = "INSERT INTO INSTRUCTOR_SCHEDULE SELECT CRN, Title, day, location, duration, sections FROM COURSES WHERE CRN = " + user_crn + ";";
	//cout << insert_s_course << endl;
	exit = sqlite3_exec(DB, insert_s_course.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Insert Failed" << sqlite3_errmsg(DB) << endl;
	}
	else cout << "Insert Success" << endl;
}

void Instructor::dropCourse(sqlite3* DB, string user_crn) {
	//cout << "Student's dropCourse has been called" << endl;
	int exit = 1;
	string delete_s_course;
	delete_s_course = "DELETE FROM INSTRUCTOR_SCHEDULE WHERE CRN = " + user_crn + ";";
	exit = sqlite3_exec(DB, delete_s_course.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Delete Failed" << endl;
	}
	else cout << "Delete Success" << endl;
}

void Instructor::printRoster(sqlite3* DB) {
	//cout << "Student's dropCourse has been called" << endl;
	int exit = 1;
	string user_crn;
	string print_roster = "SELECT * FROM INSTRUCTOR_SCHEDULE;";
	exit = sqlite3_exec(DB, print_roster.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Print Failed" << endl;
	}
	else cout << "Print Success" << endl;
}

// destructor

Instructor::~Instructor() {

}
