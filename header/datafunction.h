#ifndef _DATA_FUNCTION_H
#define _DATA_FUNCTION_H
#include <string>
#include "structlist.h"
using namespace std;

bool IsemptyFile(string fileName);

void LoadYearFromFile(string YearFile, Schoolyear* &listYear);
void LoadClassFromfile(string yearName, StudyClass* &listClass, int &numClass);
void LoadStudentListFromFile(string yearName, string className, Student* &listStudent, int &numStudent);
void LoadSemesterFromFile(string yearName, Semester* &listSemester);
void LoadCourseInfoFromFile(Course* &aCourse, string semester, string start, string end);
void LoadCourseStudentFromFile(CourseStudent* &listStudent, string CourseID, string className);
void LoadData(DataBase &DB, string YearFile);

void SaveYearToFile(string YearFile, Schoolyear* ListYear);
void SaveClassToFile(string yearName, StudyClass* listClass);
void SaveStudentListToFile(string className, Student* listStudent);
void SaveSemesterToFile(string yearName, Semester* listSem);
bool findStudentScoreBoard(EnrolledCourse* enrolledlist, Course* curCourse, Scoreboard result);
void SaveCourseStudentToFile(Course* aCourse);
void SaveCourseInfoToFile(Semester* curSem);
void SaveData(string YearFile, Schoolyear* ListYear);
void ClearData(Schoolyear* &listYear);
void QuickPtrBinder(Schoolyear* &listYear);

#endif