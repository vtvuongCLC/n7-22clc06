#ifndef _LOGIN_FUNCTION_H
#define _LOGIN_FUNCTION_H
#include "structlist.h"
	
	bool login_student(Schoolyear* SchoolyearList, Student* &toStudent, StudyClass* &toStudyClass);
	bool login_staff(StaffAccount* staffList, StaffAccount* &toStaff);

#endif