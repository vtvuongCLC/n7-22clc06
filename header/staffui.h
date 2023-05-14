#ifndef _STAFF_UI_H
#define _STAFF_UI_H
#include "structlist.h"

void CourseManager(DataBase &DB ,Course* curCourse, Semester* curSemester);
void SpecificSemesterManager(DataBase &DB, Semester* curSemester);
void SemestersListManager(DataBase &DB, string yearName);

void StudyClassScoreBoardManager(Schoolyear* listYear, StudyClass* curClass, Semester* listSemester);

void StudyClassManager(Schoolyear* listYear ,StudyClass* curClass, Semester* listSemester);
void ClassesManager(Schoolyear* listYear, StudyClass* &listClass, Semester* listSemester, string yearName, string classType, int &numClass);

void SchoolYearManager(DataBase &DB, Schoolyear* curYear);

void MainManagementUI(DataBase &DB);
void StaffUI(DataBase &DB,StaffAccount* toStaff, StaffAccount* staffList);

#endif