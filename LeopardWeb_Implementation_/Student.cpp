#include "Student.h"

using std::endl;
using std::string;

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
string Student::get_day(sqlite3* LW_DB, string usr_name) {
	string query = "SELECT Day FROM STUDENT_SCHEDULE WHERE Student = '" + usr_name +"';";	// SQL statement selecting User's first name
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Course Doesn't exist" << endl;
	}
	size_t length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
	int size = length * sizeof(unsigned char);  // calculate the total size
	string result = "";
	for (int i = 0; i < size; i++) {
		char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
		result = result + temp;	// append temp to resulting string
	}
	while (1) {
		rc = sqlite3_step(stmt); // Step through resulting row
		if (rc != SQLITE_ROW) {
			cout << endl;
			break;
		}
		length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
		size = length * sizeof(unsigned char);  // calculate the total size
		result = result + " ";
		for (int i = 0; i < size; i++) {
			char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
			result = result + temp;	// append temp to resulting string
		}
	}
	
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}

string Student::get_time(sqlite3* LW_DB, string usr_name) {
	string query = "SELECT time FROM STUDENT_SCHEDULE WHERE Student = '" + usr_name + "';";	// SQL statement selecting User's first name
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Course Doesn't exist" << endl;
	}
	size_t length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
	int size = length * sizeof(unsigned char);  // calculate the total size
	string result = "";
	for (int i = 0; i < size; i++) {
		char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
		result = result + temp;	// append temp to resulting string
	}
	while (1) {
		rc = sqlite3_step(stmt); // Step through resulting row
		if (rc != SQLITE_ROW) {
			cout << endl;
			break;
		}
		length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
		size = length * sizeof(unsigned char);  // calculate the total size
		result = result + " ";
		for (int i = 0; i < size; i++) {
			char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
			result = result + temp;	// append temp to resulting string
		}
	}

	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}

string Student::get_crn(sqlite3* LW_DB, string usr_name) {
	string query = "SELECT CRN FROM STUDENT_SCHEDULE WHERE Student = '" + usr_name + "';";	// SQL statement selecting User's first name
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(LW_DB, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(LW_DB) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Course Doesn't exist" << endl;
	}
	size_t length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
	int size = length * sizeof(unsigned char);  // calculate the total size
	string result = "";
	for (int i = 0; i < size; i++) {
		char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
		result = result + temp;	// append temp to resulting string
	}
	while (1) {
		rc = sqlite3_step(stmt); // Step through resulting row
		if (rc != SQLITE_ROW) {
			cout << endl;
			break;
		}
		length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
		size = length * sizeof(unsigned char);  // calculate the total size
		result = result + " ";
		for (int i = 0; i < size; i++) {
			char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
			result = result + temp;	// append temp to resulting string
		}
	}

	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}

void Student::checkConflict(sqlite3* DB, string user_name) {
	// Only need to check if day is the same 
	// If other start time <= start time < other end time there is conflict 
	cout << "The Day is " << this->get_day(DB, user_name) << endl;
	cout << "The time is " << this->get_time(DB, user_name) << endl;
	cout << "The CRNs is " << this->get_crn(DB, user_name) << endl;
}
void Student::addCourse(sqlite3* DB, string user_crn, string student_name, string in_crn, string in_title, string in_day, string in_location, string in_duration, string start, string end) {
	//cout << "Student's addCourse has been called" << endl;
	int exit = 1;
	string insert_s_course;
	//insert_s_course = "INSERT INTO STUDENT_SCHEDULE SELECT CRN, Title, day, location, duration FROM COURSES WHERE CRN = " + user_crn + ";"; //Insert into student schedule query
	insert_s_course = "INSERT INTO STUDENT_SCHEDULE VALUES ("+in_crn+", '"+in_title+"', '" + in_day + "', '" + in_location + "', " + in_duration + ", '" + student_name + "', " + start + ", " + end + "); ";

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


void Student::printSchedule(sqlite3* DB, string student_name) {
	int exit = 1;
	//print failed
	//string print_schedule = "SELECT CRN, Class, Day, Location, Duration FROM STUDENT_SCHEDULE WHERE Student = '" + student_name + "';";
	string print_schedule = "SELECT * FROM STUDENT_SCHEDULE WHERE Student = '" + student_name + "';";
	cout << print_schedule << endl;
	exit = sqlite3_exec(DB, print_schedule.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Print Schedule Failed" << endl;
	}
	else cout << "Print Schdule Success" << endl;
}
// destructor
Student::~Student() {

}