#pragma once
#include <string>

using namespace std;

class User
{
protected:
	int id;
	string first_name;
	string last_name;
public:
	User();
	User(int in_id, string f_name, string l_name);

	void set_id(int in_id);
	void set_fname(string f_name);
	void set_lname(string l_name);

	void print_all();

	~User();
	
};

