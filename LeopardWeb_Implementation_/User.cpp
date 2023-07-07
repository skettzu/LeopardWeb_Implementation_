#include "User.h"

using std::endl;

// constructor

User::User() {
	first_name = "Bob";
	last_name = "Smith";
	ID = 0000;
}

User::User(string first) {
	first_name = first;
	last_name = "Smith";
	ID = 0000;
}

User::User(string first, string last) {
	first_name = first;
	last_name = last;
	ID = 0000;
}

User::User(string first, string last, int in_ID) {
	first_name = first;
	last_name = last;
	ID = in_ID;
}

// method

void User::setFirstName(string first) {
	first_name = first;
}
void User::setLastName(string last) {
	last_name = last;
}
void User::setID(int in_ID) {
	ID = in_ID;
}
void User::printAllInfo() {
	cout << "First name is " << first_name << endl;
	cout << "Last name is " << last_name << endl;
	cout << "ID is " << ID << endl;
}

// destructor

User::~User() {

}