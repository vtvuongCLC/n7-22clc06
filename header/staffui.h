#ifndef _STAFF_UI_H
#define _STAFF_UI_H
#include "structlist.h"

void CourseManager(DataBase &DB ,Course* curCourse, Semester* curSemester);
void SpecificSemesterManager(DataBase &DB, Semester* curSemester);
void SemestersListManager(DataBase &DB, string yearName);

void StudyClassScoreBoardManager(StudyClass* curClass, string yearName, Semester** HandlingArr);

void StudyClassManager(StudyClass* curClass, string yearName, Semester* listSemester);
void ClassesManager(Schoolyear* curYear, Semester* listSemester);
void SchoolYearManager(DataBase &DB, Schoolyear* curYear);

void StaffUI(DataBase &DB);

#endif