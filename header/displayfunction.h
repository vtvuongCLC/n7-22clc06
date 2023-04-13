#ifndef _DISPLAY_FUNCTION_H
#define _DISPLAY_FUNCTION_H
#include "structlist.h"

void DisplayBirth(BirthDate InputBirth);
void DisplayStudentList(Student* listStudent);
void DisplayClassList(StudyClass* listClass, int &max);
void DisplayYearList(Schoolyear* listYear, int &max);

void DisplayCourseStudentList(CourseStudent* listCourseStudent);
void DisplayCourseList(Course* listCourse, int &max);
void DisplayCourseList1Student(Student* pStudent, int semester, string year);

bool DisplaySemesterList(Semester* SemesterList,Semester** &handlingArr, string yearName, int &max);
void DisplayScoreboard1Student(Student* pStudent, int semester, string year);
void DisplayScoreboardCourse(Course* pCourse);

void CourseManager(DataBase &DB ,Course* curCourse, Semester* curSemester);
void SpecificSemesterManager(DataBase &DB, Semester* curSemester);
void SemestersListManager(DataBase &DB, string yearName);

void DisplayScoreBoardUI(Course* listCourse, bool &nextStep);
void DisplayScoreBoard(StudyClass* curClass, Course* listCourse, int semester);
void StudyClassScoreBoardManager(StudyClass* curClass, string yearName, Semester** HandlingArr);

void StudyClassManager(StudyClass* curClass, string yearName, Semester* listSemester);
void ClassesManager(Schoolyear* curYear, Semester* listSemester);
void SchoolYearManager(DataBase &DB, Schoolyear* curYear);

void StaffGUI(DataBase &DB);

#endif