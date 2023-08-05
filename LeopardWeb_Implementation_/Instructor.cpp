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

void Instructor::printSchedule(sqlite3* DB, string i_name) {
	//cout << "Instructor's printSchedule has been called" << endl;
	string print_schedule = "SELECT * FROM COURSES WHERE Instructor = '" + i_name + "';";
	cout << print_schedule << endl;
	int exit = sqlite3_exec(DB, print_schedule.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Print Failed" << endl;
	}
	else cout << "Print Success" << endl;
}

void Instructor::addCourse(sqlite3* DB, string i_name) {
	//cout << "Student's addCourse has been called" << endl;
	int exit = 1;
	string insert_course;
	string CRN, title, dept, start_time, day, semester, year, credit, location, section, end_time, duration;
	cout << "Enter CRN of the course: ";
	cin >> CRN;
	cout << "Enter Title of the course: ";
	cin >> title;
	cout << "Enter department: ";
	cin >> dept;
	cout << "Enter day of the course: ";
	cin >> day;
	cout << "Enter location: ";
	cin.ignore();
	getline(cin, location);
	cout << "Enter semeseter of the course: ";
	cin >> semester;
	cout << "Enter year: ";
	cin >> year;
	cout << "Enter credit for the course: ";
	cin >> credit;
	cout << "Enter section: ";
	cin >> section;
	cout << "Enter start time (integer): ";
	cin >> start_time;
	cout << "Enter end time (integer): ";
	cin >> end_time;
	cout << "Enter duration of the course: ";
	cin >> duration;
	insert_course = "INSERT INTO COURSES VALUES (" + CRN + ", '" + title + "', '" + i_name + "', '" + dept + "', " + start_time + ", '" + day + "', '" + semester + "', " + year + ", " + credit + ", '" + location + "', " + duration + ", " + section + ", " + end_time + ");";
	//insert_s_course = "INSERT INTO INSTRUCTOR_SCHEDULE SELECT CRN, Title, day, location, duration, sections FROM COURSES WHERE CRN = " + user_crn + ";";
	//cout << insert_s_course << endl;
	exit = sqlite3_exec(DB, insert_course.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Insert Failed" << sqlite3_errmsg(DB) << endl;
	}
	else cout << "Insert Success" << endl;
}

void Instructor::dropCourse(sqlite3* DB, string user_crn, string i_name) {
	//cout << "Student's dropCourse has been called" << endl;
	int exit = 1;
	string delete_course;
	delete_course = "DELETE FROM INSTRUCTOR_SCHEDULE WHERE CRN = " + user_crn + " AND Instructor = '" + i_name + "'; ";
	exit = sqlite3_exec(DB, delete_course.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Delete Failed" << endl;
	}
	else cout << "Delete Success" << endl;
}

void Instructor::printRoster(sqlite3* DB) {
	//cout << "Student's dropCourse has been called" << endl;
	int exit = 1;
	string user_crn;
	cout << "Enter CRN to print roster: ";
	cin >> user_crn;
	string print_roster = "SELECT Student FROM STUDENT_SCHEDULE WHERE CRN = " + user_crn + "; ";
	exit = sqlite3_exec(DB, print_roster.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Print Failed" << endl;
	}
	else cout << "Print Success" << endl;
}

// destructor

Instructor::~Instructor() {

}
