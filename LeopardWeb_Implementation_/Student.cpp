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
void Student::searchAllCourse(sqlite3* DB) {
	//cout << "Student's searchCourse has been called" << endl;
	int exit = 1;
	string search_all = "SELECT * FROM COURSES;";
	exit = sqlite3_exec(DB, search_all.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Search Failed" << endl;
	}
	else cout << "Search Success" << endl;
}

void Student::searchByParameter(sqlite3* DB) {
	int exit = 1;
	cout << "Enter parameter to seach course: ";
	string user_parameter;
	cin >> user_parameter;
	cin.ignore();
	//string search_parameter = ("SELECT * FROM COURSES WHERE Title = '" + user_parameter + "' OR department = '" + user_parameter + "' OR day = '" + user_parameter + "' OR semester = '" + user_parameter + "' OR CRN = " + user_parameter + " OR time = " + user_parameter + " OR year = " + user_parameter + " OR credits = " + user_parameter + "; ");
	//search for integer parameter
	string search_parameter = ("SELECT * FROM COURSES WHERE CRN = " + user_parameter + " OR time = " + user_parameter + " OR year = " + user_parameter + " OR credits = " + user_parameter + "; ");
	//cout << search_parameter << endl;
	exit = sqlite3_exec(DB, search_parameter.c_str(), callback, NULL, NULL);

	if (exit != SQLITE_OK) {
		//cout << "Search Error" << endl;
		//search for string parameter
		search_parameter = ("SELECT * FROM COURSES WHERE Title = '" + user_parameter + "' OR department = '" + user_parameter + "' OR day = '" + user_parameter + "' OR semester = '" + user_parameter + "';");
		//cout << search_parameter << endl;
		exit = sqlite3_exec(DB, search_parameter.c_str(), callback, NULL, NULL);
		/*
		if (exit != SQLITE_OK) {
			cout << "Search Error" << endl;
		}
		else cout << "Search Success" << endl;
		*/
	}
	//else cout << "Search Success" << endl;
}

void Student::addCourse(sqlite3* DB) {
	//cout << "Student's addCourse has been called" << endl;
	int exit = 1;
	string user_crn;
	string insert_s_course;
	cout << "Enter CRN to register: ";
	cin >> user_crn;
	insert_s_course = "INSERT INTO STUDENT_SCHEDULE SELECT CRN, Title, day, location, duration FROM COURSES WHERE CRN = " + user_crn + ";";
	//cout << insert_s_course << endl;
	exit = sqlite3_exec(DB, insert_s_course.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Insert Failed" << endl;
	}
	else cout << "Insert Success" << endl;
}

void Student::dropCourse(sqlite3* DB) {
	//cout << "Student's dropCourse has been called" << endl;
	int exit = 1;
	string user_crn;
	string delete_s_course;
	cout << "Enter CRN to drop course: ";
	cin >> user_crn;
	delete_s_course = "DELETE FROM STUDENT_SCHEDULE WHERE CRN = " + user_crn + ";";
	exit = sqlite3_exec(DB, delete_s_course.c_str(), callback, NULL, NULL);
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