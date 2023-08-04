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
string Admin::get_instructor(sqlite3* LW_DB, string crn) {
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
void Admin::addUser(sqlite3* DB) {
	string insert_user, insert_credential;
	string user_type;
	string user_id, user_fname, user_lname, gradyear, hireyear, major, email, p_title, p_dept;
	//string default_pwd = "12345";
	cout << "Who do you want to add to the system? (I for Instructor, S for Student): ";
	cin >> user_type;
	if (user_type == "s" || user_type == "S") {
		cout << "Enter student ID: ";
		cin >> user_id;
		cout << "Enter student's first name: ";
		cin >> user_fname;
		cout << "Enter student's last name: ";
		cin >> user_lname;
		cout << "Enter student's expected graduate year: ";
		cin >> gradyear;
		cout << "Enter student's major: ";
		cin >> major;
		cout << "Enter student's email: ";
		cin >> email;

		insert_user = "INSERT INTO STUDENT VALUES (" + user_id + ", '" + user_fname + "', '" + user_lname + "', " + gradyear + ", '" + major + "', '" + email + "');";
		int exit = sqlite3_exec(DB, insert_user.c_str(), callback, NULL, NULL);
		if (exit == SQLITE_OK) {
			cout << "Student Added Successfully" << endl;
			insert_credential = "INSERT INTO CREDENTIAL VALUES (" + user_id + ", '" + email + "', '12345' , '" + user_fname + "', '" + user_lname + "', 'Student');";
			//cout << insert_credential;
			int exit_1 = sqlite3_exec(DB, insert_credential.c_str(), callback, NULL, NULL);
			if (exit_1 == SQLITE_OK) {
				cout << "Student Added to Credential Successfully	|	Default Password is 12345" << endl;
			}
			else cout << "Add Student's Credential Failed" << endl;
		}
		else cout << "Add Student Failed" << endl;
	}
	else if (user_type == "i" || user_type == "I") {
		cout << "Enter Instructor's ID: ";
		cin >> user_id;
		cout << "Enter instructor's first name: ";
		cin >> user_fname;
		cout << "Enter instructor's last name: ";
		cin >> user_lname;
		cout << "Enter instructor's title: ";
		cin.ignore();
		getline(cin, p_title);
		cout << "Enter instructor's hire year: ";
		cin >> hireyear;
		cout << "Enter instructor's department: ";
		cin >> p_dept;
		cout << "Enter instructor's email: ";
		cin >> email;
		insert_user = "INSERT INTO INSTRUCTOR VALUES (" + user_id + ", '" + user_fname + "', '" + user_lname + "', '" + p_title + "', " + hireyear + ", '" + p_dept + "', '" + email + "');";
		//cout << insert_user << endl;
		int exit = sqlite3_exec(DB, insert_user.c_str(), callback, NULL, NULL);
		if (exit == SQLITE_OK) {
			cout << "Instructor Added Successfully" << endl;
			insert_credential = "INSERT INTO CREDENTIAL VALUES (" + user_id + ", '" + email + "', '12345' , '" + user_fname + "', '" + user_lname + "', 'Instructor');";
			//cout << insert_credential;
			int exit_1 = sqlite3_exec(DB, insert_credential.c_str(), callback, NULL, NULL);
			if (exit_1 == SQLITE_OK) {
				cout << "Instructor Added to Credential Successfully	|	Default Password is 12345" << endl;
			}
			else cout << "Add Instructor's Credential Failed" << endl;
		}
		else cout << "Add Instructor Failed" << endl;
	}
	else {
		cout << "Invalid Input" << endl;
		this->addUser(DB);
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
	else cout << "Remove Successfully" << endl;
	
	string remove_credential = "DELETE FROM CREDENTIAL WHERE WID = " + in_id + ";";
	int exit_1 = sqlite3_exec(DB, remove_credential.c_str(), callback, NULL, NULL);
	if (exit_1 != SQLITE_OK) {
		cout << "Remove Credential Failed" << endl;
	}
	else cout << "Remove Credential Sucessfully" << endl;

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
	string instructor_name = this->get_instructor(DB, crn);
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
