#ifndef _DATA_FUNCTION_H
#define _DATA_FUNCTION_H
#include "structlist.h"
#include <string>
using namespace std;

bool IsemptyFile(string fileName);

void LoadStaffData(StaffAccount* &staffList);
void LoadYearFromFile(string YearFile, Schoolyear* &listYear, int &numYear);
void LoadClassFromfile(string yearName, string classType, StudyClass* &listClass, int &numClass);
void LoadStudentListFromFile(string yearName, string className,string classType, Student* &listStudent, int &numStudent);
void LoadSchoolData(DataBase &DB);

void LoadSemesterFromFile(string SemesterFile, Semester* &listSemester);
void LoadCourseInfoFromFile(Semester* curSemester);
void LoadCourseStudentFromFile(Course* aCourse, int semester, string year, Schoolyear** quickPtr);
void LoadSemesterSector(DataBase &DB);

void SaveStaffData(StaffAccount* staffList);
void SaveYearToFile(string YearFile, Schoolyear* ListYear);
void SaveClassToFile(string yearName, string classType, StudyClass* listClass);
void SaveStudentListToFile(string className, Student* listStudent);

void SaveCourseStudentToFile(Course* aCourse);
void SaveCourseInfoToFile(Semester* curSemester);
void SaveSemesterToFile(string SemesterFile, Semester* listSemester);

void ClearStaffList(StaffAccount* &staffList);
void ClearData(DataBase &DB);

#endif