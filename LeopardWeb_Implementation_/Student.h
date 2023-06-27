#pragma once
#include "user.h"

class Student :
    public User
{
public:
    Student();

    void search_course();
    void add_course();
    void drop_course();
    void print_schedule();
};

