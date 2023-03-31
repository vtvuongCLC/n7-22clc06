#ifndef _DISPLAY_FUNCTION_H
#define _DISPLAY_FUNCTION_H
#include "structlist.h"

    void DisplayYearList(Schoolyear* listYear, int &max);
    void DisplayClassList(StudyClass* listClass, int &max);
    void DisplayBirth(BirthDate InputBirth);
    void DisplayStudentList(Student* listStudent);

    void StudyClassManage(StudyClass* InputClass, string yearName);
    void ListClassManage(Schoolyear* InputYear);
    void SchoolYearManage(Schoolyear *DataList);
    void StaffGUI(Schoolyear* DataBase);
    void StudentGUI(Schoolyear* DataBase);
#endif