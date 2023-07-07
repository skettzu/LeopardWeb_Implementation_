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

void Instructor::printSchedule() {
	cout << "Instructor's printSchedule has been called" << endl;
}
void Instructor::printClassList() {
	cout << "Instructor's printClassList has been called" << endl;
}
void Instructor::searchCourse() {
	cout << "Instructor's searchCourse has been called" << endl;
}

// destructor

Instructor::~Instructor() {

}