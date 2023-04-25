#ifndef _GENERAL_DISPLAY_FUNCTION
#define _GENERAL_DISPLAY_FUNCTION
#include "structlist.h"
void DisplayBirth(BirthDate InputBirth);
void DisplayScoreBoardUI(Course* listCourse, bool &nextStep);
void DisplayScoreBoard(StudyClass* curClass, Course* listCourse, int semester);
void DisplayStudentList(Student* listStudent);
void DisplayClassList(StudyClass* listClass, int &max);
void DisplayYearList(Schoolyear* listYear, int &max);
void DisplayCourseStudentList(CourseStudent* listCourseStudent);
void DisplayCourseList(Course* listCourse, int &max);
void DisplayScoreboardCourse(Course* pCourse);
bool DisplaySemesterList(Semester* SemesterList,Semester** &handlingArr, string yearName, int &max);
void DisplayInfoStudent(Student* curStudent);
void DisplayCourseList1Student(Student* pStudent, int semester, string year);
void DisplayScoreboard1Student(Student* pStudent, int semester, string year);
#endif