#ifndef _ULTILITY_FUNCTION
#define _ULTILITY_FUNCTION
#include "structlist.h"

bool validInfo(Info infoparam,char gender);

void AddStudentManual(Student* &listStudent, string yearName, string className, int &numStudent);
void AddStudentCSV(Student* &listStudent, string yearName, string className, int &numStudent);
void AddStudent(Student* &listStudent, string yearName, string className, int &numStudent);
void AddClass(StudyClass* &listClass);
string getYearData(Schoolyear* listYear);
void AddYear(DataBase &DB);

Schoolyear* navigateYear(Schoolyear* listYear, int userindex);
StudyClass* navigateClass(StudyClass* listClass, int userindex);
void QuickPtrBinder(DataBase &DB);
void BridgingList(DataBase &DB);
void SaveData(DataBase DB);
void ClearData(DataBase &DB);

#endif