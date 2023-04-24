#ifndef _LOGIN_FUNCTION_H
#define _LOGIN_FUNCTION_H
#include "structlist.h"
using namespace std;

	void ChangePasswordStudent(Student* curStudent);
	int login_student(string id,string pass, Schoolyear* DataBase, Student* &toStudent, StudyClass* &toStudyClass);
	bool login_staff(string AccountStaff, string passStaff);
	int login(Schoolyear *DataBase, Student* &toStudent, StudyClass* &toStudyClass);

#endif