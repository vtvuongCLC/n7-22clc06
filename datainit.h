#ifndef _DATAINIT_H
#define _DATAINIT_H
    #include "header.h"
    #include <string>
    using namespace std;
    bool IsemptyFile(string fileName);
    bool validInfo(Info infoparam,char gender);

    void LoadYearFromFile(string YearFile, Schoolyear* &listYear);
    void LoadClassFromfile(string yearName, StudyClass* &listClass);
    void LoadStudentListFromFile(string yearName, string className, Student* &listStudent);
    void LoadData(string YearFile, Schoolyear* &listYear);

    void AddYear(Schoolyear* &listYear);
    void AddClass(StudyClass* &listClass);
    void AddStudentManual(Student* &listStudent, string yearName, string className);
    void AddStudentCSV(Student* &listStudent, string yearName, string className);
    void AddStudent(Student* &listStudent, string yearName, string className);

    void InitBaseData(Schoolyear* &listYear);
    void SaveData(string YearFile, Schoolyear* ListYear);
    void ClearData(Schoolyear* &listYear);

    Schoolyear* navigateYear(Schoolyear* listYear, int userindex);
    StudyClass* navigateClass(StudyClass* listClass, int userindex);

    void DisplayYearList(Schoolyear* listYear, int &max);
    void DisplayClassList(StudyClass* listClass, int &max);
    void DisplayBirth(BirthDate InputBirth);
    void DisplayStudentList(Student* listStudent);

    void StudyClassManage(StudyClass* InputClass, string yearName);
    void ListClassManage(Schoolyear* InputYear);
    void SchoolYearManage(Schoolyear *DataList);
#endif