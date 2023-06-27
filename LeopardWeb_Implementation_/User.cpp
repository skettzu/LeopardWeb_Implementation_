#include "User.h"
#include <iostream>

using namespace std;

User::User() {
	id = 123456;
	first_name = "N/A";
	last_name = "N/A";
}
User::User(int in_id, string f_name, string l_name) {
	id = in_id;
	first_name = f_name;
	last_name = l_name;
}

void User::set_id(int in_id) {
	id = in_id;
}
void User::set_fname(string f_name) {
	first_name = f_name;
}
void User::set_lname(string l_name) {
	last_name = l_name;
}

void User::print_all() {
	cout << "Student ID: " << id << endl << "First name: " << first_name << endl << "Last name: " << last_name << endl;
}

User::~User() {

}