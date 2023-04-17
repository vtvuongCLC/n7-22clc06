#ifndef _STUDENT_UI_H
#define _STUDENT_UI_H
#include "structlist.h"
    void DisplayInfoStudent(Student* listStudent);
    void DisplayCourseList1Student(Student* pStudent, int semester, string year);
    void DisplayScoreboard1Student(Student* pStudent, int semester, string year);
    void StudentUI(Student* curStudent, DataBase DB);
#endif