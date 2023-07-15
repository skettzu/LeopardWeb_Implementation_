#include "Student.h"

using std::endl;

// constructor

Student::Student() {
	first_name = "Bob";
	last_name = "Smith";
	ID = 0000;
}

Student::Student(string first) {
	first_name = first;
	last_name = "Smith";
	ID = 0000;
}

Student::Student(string first, string last) {
	first_name = first;
	last_name = last;
	ID = 0000;
}

Student::Student(string first, string last, int in_ID) {
	first_name = first;
	last_name = last;
	ID = in_ID;
}

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

// method

void Student::addCourse(sqlite3* DB, string user_crn) {
	//cout << "Student's addCourse has been called" << endl;
	int exit = 1;
	string insert_s_course;
	insert_s_course = "INSERT INTO STUDENT_SCHEDULE SELECT CRN, Title, day, location, duration FROM COURSES WHERE CRN = " + user_crn + ";"; //Insert into student schedule query
	//cout << insert_s_course << endl;
	exit = sqlite3_exec(DB, insert_s_course.c_str(), callback, NULL, NULL); //execute query
	if (exit != SQLITE_OK) {
		cout << "Insert Failed" << endl;
	}
	else cout << "Insert Success" << endl;
}

void Student::dropCourse(sqlite3* DB, string user_crn) {
	//cout << "Student's dropCourse has been called" << endl;
	int exit = 1;
	string delete_s_course;
	delete_s_course = "DELETE FROM STUDENT_SCHEDULE WHERE CRN = " + user_crn + ";"; //delete course from schdule query
	exit = sqlite3_exec(DB, delete_s_course.c_str(), callback, NULL, NULL); //execute query
	//test
	if (exit != SQLITE_OK) {
		cout << "Delete Failed" << endl;
	}
	else cout << "Delete Success" << endl;
}

void Student::printSchedule() {
	cout << "Student's printSchedule has been called" << endl;
}
// destructor

Student::~Student() {

}