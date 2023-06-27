#include "Student.h"
#include <iostream>

using namespace std;

Student::Student() {

}

void Student::search_course() {
	cout << "Search course function has beed called" << endl;
}
void Student::add_course() {
	cout << "Add course function has been called" << endl;
}
void Student::drop_course() {
	cout << "Drop course function has been called" << endl;
}
void Student::print_schedule() {
	cout << "Print schedule function has been called" << endl;
}