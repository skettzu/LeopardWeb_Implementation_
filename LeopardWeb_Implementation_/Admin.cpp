#include "Admin.h"

using std::endl;

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

// constructor

Admin::Admin() {
	first_name = "Bob";
	last_name = "Smith";
	ID = 0000;
}

Admin::Admin(string first) {
	first_name = first;
	last_name = "Smith";
	ID = 0000;
}

Admin::Admin(string first, string last) {
	first_name = first;
	last_name = last;
	ID = 0000;
}

Admin::Admin(string first, string last, int in_ID) {
	first_name = first;
	last_name = last;
	ID = in_ID;
}
string get_instructor(sqlite3* LW_DB, string crn) {
	string query = "SELECT Instructor FROM COURSES WHERE CRN = " + crn + ";";	// SQL statement selecting User's first name
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
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}

// method

void Admin::addCourse(sqlite3* DB, string course) {
	string query = "INSERT INTO COURSES VALUES(" + course + ");";	// Create Query to Add to Course to DB
	int exit = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);	// Execute the Query
	if (exit != SQLITE_OK) {
		cout << "Insert Error: " << sqlite3_errmsg(DB) << endl;
	}
	else {
		cout << "Added Course Successfully!" << endl;
	}
}
void Admin::removeCourse(sqlite3* DB, int CRN) {
	string query = "DELETE FROM COURSES WHERE CRN = " + std::to_string(CRN);	// Create Query to Remove Course from DB
	int exit = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);	// Execute the Query
	if (exit != SQLITE_OK) {
		cout << "Delete Error: " << sqlite3_errmsg(DB) << endl;
	}
	else {
		cout << "Removed Course Successfully!" << endl;
	}
}
void Admin::addStudent(sqlite3* DB, string user_info, string user_type) {
	string insert_student, insert_instructor;
	if (user_type == "Student") {
		//Insert into student table
		insert_student = "INSERT INTO STUDENT VALUES (" + user_info + ");";
		int exit = sqlite3_exec(DB, insert_student.c_str(), callback, NULL, NULL);	// Execute the Query
		if (exit != SQLITE_OK) {
			cout << "Insert Error: " << sqlite3_errmsg(DB) << endl;
		}
		else {
			cout << "Added Course Successfully!" << endl;
		}
	}
	else if (user_type == "Instructor") {
		insert_instructor = "INSERT INTO INSTRUCTOR VALUES (" + user_info + ");";
		int exit = sqlite3_exec(DB, insert_instructor.c_str(), callback, NULL, NULL);	// Execute the Query
		if (exit != SQLITE_OK) {
			cout << "Insert Error: " << sqlite3_errmsg(DB) << endl;
		}
		else {
			cout << "Added Course Successfully!" << endl;
		}
	}
}
void Admin::removeUser(sqlite3* DB, string in_id) {
	string remove_user = "DELETE FROM STUDENT WHERE ID = " + in_id + ";";
	int exit = sqlite3_exec(DB, remove_user.c_str(), callback, NULL, NULL);	// Execute the Query
	if (exit != SQLITE_OK) {
		remove_user = "DELETE FROM INSTRUCTOR WHERE ID = " + in_id + ";";
		exit = sqlite3_exec(DB, remove_user.c_str(), callback, NULL, NULL);	// Execute the Query
		if (exit != SQLITE_OK) {
			cout << "Delete Error: " << sqlite3_errmsg(DB) << endl;
		}
		else {
			cout << "Removed Successfully!" << endl;
		}
	}
	else {
		cout << "Removed Successfully!" << endl;
	}
}
void Admin::searchRoster(sqlite3* DB) {
	string user_crn;
	cout << "Enter CRN to print course: ";
	cin >> user_crn;
	string print_roster = "SELECT Student FROM STUDENT_SCHEDULE WHERE CRN = " + user_crn + ";";
	int exit = sqlite3_exec(DB, print_roster.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		cout << "Print Failed" << endl;
	}
	else cout << "Print Success" << endl;
}

void Admin::link_unlink_s(sqlite3* DB, string user_name, string crn, string in_title, string in_day, string in_location, string in_duration){
	string link_s;
	int exit = 1;
	link_s = "DELETE FROM STUDENT_SCHEDULE WHERE CRN = " + crn + " AND Student = '" + user_name + "';";
	exit = sqlite3_exec(DB, link_s.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK) {
		//cout << "Unlink Failed" << endl;
		link_s = "INSERT INTO STUDENT_SCHEDULE VALUES (" + crn + ", '" + in_title + "', '" + in_day + "', '" + in_location + "', " + in_duration + ", '" + user_name + "'); ";
		exit = sqlite3_exec(DB, link_s.c_str(), callback, NULL, NULL);
		if (exit != SQLITE_OK) {
			cout << "Link and unlink failed" << endl;
		}
		else cout << "Link Success" << endl;
	}
	else cout << "Unlink Success" << endl;
}

void Admin::unlink_i(sqlite3* DB, string user_name, string crn) {
	string unlink;
	string link;
	string instructor_name = get_instructor(DB, crn);
	//cout << instructor_name << endl;
	if (instructor_name != "N/A"){
		unlink = "UPDATE COURSES SET Instructor = 'N/A' WHERE CRN = " + crn + " AND Instructor = '" + user_name + "';";
		int exit = sqlite3_exec(DB, unlink.c_str(), callback, NULL, NULL);
		if (exit != SQLITE_OK) {
			cout << "Unlink failed" << endl;
		}
		else cout << "Unlink Success" << endl;
	}
	else if (instructor_name == "N/A") {
		link = "UPDATE COURSES SET Instructor = '" + user_name + "' WHERE CRN = " + crn + ";";
		int exit = sqlite3_exec(DB, link.c_str(), callback, NULL, NULL);
		//cout << link << endl;
		if (exit != SQLITE_OK) {
			cout << "Link failed: " << endl;
		}
		else cout << "Link Success" << endl;
	}
}

// destructor

Admin::~Admin() {

}