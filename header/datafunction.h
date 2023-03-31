#ifndef _DATA_FUNCTION_H
#define _DATA_FUNCTION_H
#include <string>
#include "structlist.h"
using namespace std;

bool validInfo(Info infoparam,char gender);
bool IsemptyFile(string fileName);

void LoadYearFromFile(string YearFile, Schoolyear* &listYear);
void LoadClassFromfile(string yearName, StudyClass* &listClass, int &numClass);
void LoadStudentListFromFile(string yearName, string className, Student* &listStudent, int &numStudent);
void LoadData(string YearFile, Schoolyear* &listYear);

void AddYear(Schoolyear* &listYear);
void AddClass(StudyClass* &listClass);
void AddStudentManual(Student* &listStudent, string yearName, string className, int &numStudent);
void AddStudentCSV(Student* &listStudent, string yearName, string className, int &numStudent);
void AddStudent(Student* &listStudent, string yearName, string className, int &numStudent);

void InitBaseData(Schoolyear* &listYear);
void SaveData(string YearFile, Schoolyear* ListYear);
void ClearData(Schoolyear* &listYear);
void QuickPtrBinder(Schoolyear* &listYear);

Schoolyear* navigateYear(Schoolyear* listYear, int userindex);
StudyClass* navigateClass(StudyClass* listClass, int userindex);

#endif