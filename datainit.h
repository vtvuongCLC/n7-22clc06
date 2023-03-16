#ifndef _DATAINIT_H
#define _DATAINIT_H
    #include "header.h"
    #include <string>
    using namespace std;
    bool IsemptyFile(string fileName);
    void InitSchoolYear(string ListYearFile);
    bool validInfo(Info infoparam,char gender);
    void AddStudentManual(string className);
    void AddStudentCSV(string className);
    int countLine(string ListYearFile);
    void LoadClass(string YearName, StudyClass* ptrCls);
    void DisplayClass(StudyClass* ptrCls,int n);
    void ClassManage(string YearName);
    void LoadYear(string ListYearFile,Schoolyear* ptrS);
    void DisplayYear(Schoolyear* ptrS, int n);
    void SchoolYearManage(string ListYearFile); //<--- MAIN FUNCTION OF THIS SECTOR
#endif