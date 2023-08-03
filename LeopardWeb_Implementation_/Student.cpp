#include "Student.h"

using std::endl;
using std::string;

int day_size;
int time_size;
int crn_size;
int dur_size;
int etime_size;

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
	string query = "SELECT Day FROM STUDENT_SCHEDULE WHERE Student = '" + usr_name + "';";	// SQL statement selecting User's first name
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
	day_size = day_size + size;	// update total size
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
		day_size = day_size + size;	// update total size
		result = result + " ";
		day_size++;
		for (int i = 0; i < size; i++) {
			char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
			result = result + temp;	// append temp to resulting string
		}
	}
	result = result + " ";
	day_size++;
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}

string Student::get_time(sqlite3* LW_DB, string usr_name) {
	string query = "SELECT starttime FROM STUDENT_SCHEDULE WHERE Student = '" + usr_name + "';";	// SQL statement selecting User's first name
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
	time_size = time_size + size;	// update total size
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
		time_size = time_size + size;	// update total size
		result = result + " ";
		time_size++;	// update total size
		for (int i = 0; i < size; i++) {
			char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
			result = result + temp;	// append temp to resulting string
		}
	}

	result = result + " ";
	time_size++;
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
	crn_size = crn_size + size;	// update total size
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
		crn_size = crn_size + size;	// update total size
		crn_size++;	// update total size
		result = result + " ";
		for (int i = 0; i < size; i++) {
			char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
			result = result + temp;	// append temp to resulting string
		}
	}

	result = result + " ";
	crn_size++;
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}

string Student::get_dur(sqlite3* LW_DB, string usr_name) {
	string query = "SELECT Duration FROM STUDENT_SCHEDULE WHERE Student = '" + usr_name + "';";	// SQL statement selecting User's first name
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
	dur_size = dur_size + size;	// update total size
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
		dur_size = dur_size + size;	// update total size
		dur_size++;	// update total size
		result = result + " ";
		for (int i = 0; i < size; i++) {
			char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
			result = result + temp;	// append temp to resulting string
		}
	}

	result = result + " ";
	dur_size++;
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}

string Student::get_etime(sqlite3* LW_DB, string usr_name) {
	string query = "SELECT endtime FROM STUDENT_SCHEDULE WHERE Student = '" + usr_name + "';";	// SQL statement selecting User's first name
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
	etime_size = etime_size + size;	// update total size
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
		etime_size = etime_size + size;	// update total size
		etime_size++;	// update total size
		result = result + " ";
		for (int i = 0; i < size; i++) {
			char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
			result = result + temp;	// append temp to resulting string
		}
	}

	result = result + " ";
	etime_size++;
	sqlite3_finalize(stmt); // Finalize the statement
	return result;
}

void Student::checkConflict(sqlite3* DB, string user_name) {
	// Only need to check if day is the same 
	// If other start time <= start time < other end time there is conflict 
	string days[30];
	string times[30];
	string CRNs[30];
	string durs[30];
	string etimes[30];
	string tot_days;
	string tot_times;
	string tot_crns;
	string tot_durs;
	string tot_etimes;
	tot_days = this->get_day(DB, user_name);
	tot_times = this->get_time(DB, user_name);
	tot_etimes = this->get_etime(DB, user_name);
	tot_crns = this->get_crn(DB, user_name);
	tot_durs = this->get_dur(DB, user_name);
	string temp;
	int temp_i = 0;
	for (int j = 0; j < day_size; j++) {
		if (tot_days[j] == ' ') {
			days[temp_i] = temp;
			temp = "";
			temp_i++;
			j++;
		}
		temp.push_back(tot_days[j]);
	}
	/*
	cout << "The days are:" << endl;
	for (int i = 0; i < temp_i; i++) {
		cout << days[i] << endl;
	}
	*/

	/*
	SOMETHING IS WRONG WITH PUSHING BACK INT INTO STRING, FIND OUT WHY
	*/
	temp_i = 0;
	for (int j = 0; j < time_size; j++) {
		if (tot_times[j] == ' ') {
			times[temp_i] = temp;
			temp = "";
			temp_i++;
			j++;
		}
		temp.push_back(tot_times[j]);
	}

	cout << "The times are:" << endl;
	for (int i = 0; i < temp_i; i++) {
		cout << times[i] << endl;
	}

	temp_i = 0;
	for (int j = 0; j < crn_size; j++) {
		if (tot_crns[j] == ' ') {
			CRNs[temp_i] = temp;
			temp = "";
			temp_i++;
			j++;
		}
		temp.push_back(tot_crns[j]);
	}
	/*
	cout << "The CRNs are:" << endl;
	for (int i = 0; i < temp_i; i++) {
		cout << CRNs[i] << endl;
	}
	*/
	temp_i = 0;
	for (int j = 0; j < dur_size; j++) {
		if (tot_durs[j] == ' ') {
			durs[temp_i] = temp;
			temp = "";
			temp_i++;
			j++;
		}
		temp.push_back(tot_durs[j]);
	}
	/*
	cout << "The Durations are:" << endl;
	for (int i = 0; i < temp_i; i++) {
		cout << durs[i] << endl;
	}
	*/
	temp_i = 0;
	for (int j = 0; j < etime_size; j++) {
		if (tot_etimes[j] == ' ') {
			etimes[temp_i] = temp;
			temp = "";
			temp_i++;
			j++;
		}
		temp.push_back(tot_etimes[j]);
	}
	cout << "The End times are:" << endl;
	for (int i = 0; i < temp_i; i++) {
		cout << etimes[i] << endl;
	}

	// Start of Conflict Checking
	// Columns: Day
	// Rows: Indices of those with that day
	int day_ind[5][5] = { { 1000, 1000, 1000, 1000, 1000 },
						{1000, 1000, 1000, 1000, 1000 },
						{1000, 1000, 1000, 1000, 1000 },
						{1000, 1000, 1000, 1000, 1000 },
						{1000, 1000, 1000, 1000, 1000 } };

	int temp_m = 0, temp_t = 0, temp_w = 0, temp_th = 0, temp_f = 0;
	for (int i = 0; i < 30; i++) {
		// First Check for matching days
		if (days[i] == "") {
			break;
		}
		if (days[i] == "Monday") {
			day_ind[temp_m][0] = i;
			temp_m++;
		}
		if (days[i] == "Tuesday") {
			day_ind[temp_t][1] = i;
			temp_t++;
		}
		if (days[i] == "Wednesday") {
			day_ind[temp_w][2] = i;
			temp_w++;
		}
		if (days[i] == "Thursday") {
			day_ind[temp_th][3] = i;
			temp_th++;
		}
		if (days[i] == "Friday") {
			day_ind[temp_th][4] = i;
			temp_f++;
		}
	}

	cout << "Day Indices Table:" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << day_ind[i][j] << " ";
		}
		cout << endl;
	}

	// Then using indices table check if there are time conflicts 
	int CRN_ind[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 };
	int CRN_i = 0;
	// If other start time <= start time < other end time there is conflict
	for (int i = 0; i < 5; i++) {
		if (day_ind[0][i] == 1000) {
			break;
		}
		for (int j = 1; j < 5; j++) {
			if (day_ind[j][i] == 1000) {
				break;
			}
			if ((stoi(times[day_ind[0][i]])) == (stoi(times[day_ind[j][i]]))) {		// if start times are the same
				CRN_ind[CRN_i] = day_ind[j][i];
				CRN_i++;
				cout << "Index added " << endl;
			}
			if ((stoi(times[day_ind[0][i]]) > stoi(times[day_ind[j][i]])) && ((stoi(times[day_ind[0][i]]) < stoi(etimes[day_ind[j][i]])))) {		// if start time is within compared start time and compared end time
				CRN_ind[CRN_i] = day_ind[j][i];
				CRN_i++;
				cout << "Index added " << endl;
			}
			if ((stoi(times[day_ind[j][i]]) > stoi(times[day_ind[0][i]])) && ((stoi(times[day_ind[j][i]]) < stoi(etimes[day_ind[0][i]])))) {		// if other start time is within this start time and this end time
				CRN_ind[CRN_i] = day_ind[j][i];
				CRN_i++;
				cout << "Index added " << endl;
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		cout << "These are the following CRNs with conflicts: " << endl;
		cout << CRNs[CRN_ind[i]];
	}
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