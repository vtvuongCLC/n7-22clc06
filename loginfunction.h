#ifndef _LOGIN_FUNCTION_H
#define _LOGIN_FUNCTION_H
#include "structlist.h"
#include <string>
using namespace std;

    bool pass_student(Student* user,string &pass);
    bool login_student(string &id,string &pass, Student* user);
    int login();
    bool login_staff(string AccountStaff,string passStaff);
    
#endif