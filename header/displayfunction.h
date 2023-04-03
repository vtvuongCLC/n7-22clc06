#ifndef _DISPLAY_FUNCTION_H
#define _DISPLAY_FUNCTION_H
#include "structlist.h"

bool validInfo(Info infoparam,char gender);

void AddStudentManual(Student* &listStudent, string yearName, string className, int &numStudent);
void AddStudentCSV(Student* &listStudent, string yearName, string className, int &numStudent);
void AddStudent(Student* &listStudent, string yearName, string className, int &numStudent);
void AddClass(StudyClass* &listClass);
string getYearData(Schoolyear* listYear);
void AddYear(Schoolyear* &listYear);

Schoolyear* navigateYear(Schoolyear* listYear, int userindex);
StudyClass* navigateClass(StudyClass* listClass, int userindex);

void DisplayBirth(BirthDate InputBirth);
void DisplayStudentList(Student* listStudent);
void DisplaySemester(Semester* SemesterList);
void DisplayClassList(StudyClass* listClass, int &max);
void DisplayYearList(Schoolyear* listYear, int &max);

void StudyClassManager(StudyClass* curClass, string yearName);
void ClassesManager(Schoolyear* curYear);
void SchoolYearManager(DataBase &DB, Schoolyear* curYear);

void StaffGUI(DataBase &DB);

#endif