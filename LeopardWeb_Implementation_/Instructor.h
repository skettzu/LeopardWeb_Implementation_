#pragma once
#include "User.h"
class Instructor :
    public User
{
public:
    Instructor();

    virtual void print_schedule();
    void print_classlist();
    void search_course();
};

