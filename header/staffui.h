#ifndef _STAFF_UI_H
#define _STAFF_UI_H
#include "structlist.h"

void CourseManager(DataBase &DB ,Course* curCourse, Semester* curSemester);
void SpecificSemesterManager(DataBase &DB, Semester* curSemester);
void SemestersListManager(DataBase &DB, string yearName);

void StudyClassScoreBoardManager(StudyClass* curClass, string yearName, Semester** HandlingArr);

void StudyClassManager(StudyClass* curClass, Semester* listSemester);
void ClassesManager(StudyClass* listClass, Semester* listSemester, string yearName, string classType);
void SchoolYearManager(DataBase &DB, Schoolyear* curYear);

void MainManagementUI(DataBase &DB);
void StaffUI(DataBase &DB,StaffAccount* toStaff, StaffAccount* staffList);

#endif