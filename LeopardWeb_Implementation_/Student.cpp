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

// method

void Student::searchCourse() {
	cout << "Student's searchCourse has been called" << endl;
}
void Student::addCourse() {
	cout << "Student's addCourse has been called" << endl;
}
void Student::dropCourse() {
	cout << "Student's dropCourse has been called" << endl;
}
void Student::printSchedule() {
	cout << "Student's printSchedule has been called" << endl;
}
// destructor

Student::~Student() {

}