#ifndef _LOGIN_FUNCTION_H
#define _LOGIN_FUNCTION_H
#include "structlist.h"
using namespace std;

	int login_student(string id, string pass, Schoolyear* DataBase);
	bool login_staff(string AccountStaff, string passStaff);
	int login(Schoolyear *DataBase);

#endif