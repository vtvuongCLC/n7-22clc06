#ifndef _DISPLAY_FUNCTION_H
#define _DISPLAY_FUNCTION_H
#include "structlist.h"

void DisplayBirth(BirthDate InputBirth);
void DisplayStudentList(Student* listStudent);
void DisplayClassList(StudyClass* listClass, int &max);
void DisplayYearList(Schoolyear* listYear, int &max);

void DisplayCourseStudentList(CourseStudent* listCourseStudent);
void DisplayCourseList(Course* listCourse, int &max);
bool DisplaySemesterList(Semester* SemesterList,Semester** &handlingArr, string yearName, int &max);

void CourseManager(DataBase &DB ,Course* curCourse);
void SpecificSemesterManager(DataBase &DB, Semester* curSemester);
void SemestersListManager(DataBase &DB, string yearName);

void StudyClassManager(StudyClass* curClass, string yearName);
void ClassesManager(Schoolyear* curYear);
void SchoolYearManager(DataBase &DB, Schoolyear* curYear);

void StaffGUI(DataBase &DB);

#endif