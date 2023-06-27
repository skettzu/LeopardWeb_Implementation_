#pragma once
#include "User.h"
class Admin :
    public User
{
public:
    virtual void add_course();
    void remove_course();
    void add_user();
    void remove_user(); 
    void add_student();
    void remove_student();
    void search_print_roster();
    void search_print_course();
};

