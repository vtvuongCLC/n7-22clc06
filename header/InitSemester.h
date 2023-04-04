#ifndef _INITSEMESTER_H
#define _INITSEMESTER_H
#include "structlist.h"

//Semester* FindUninitSem(Schoolyear* year);
void LinkEnrolledCourse(Student *&curStudent, Course *curCourse, CourseStudent* curCourseStudent);

bool FindStudentIndex(Schoolyear* listYear,CourseStudent* &CourseStud, string yearName,string className, string StudID,Course* curCourse);

bool UploadListofStud(Course* &curCourse, Schoolyear* listYear);

void EnterCourseData(Course* &firstCour);

void InitSemester(Semester* &Sem,int index);

void LinkAndInit(Semester* &curSemester, Schoolyear* listYear);
#endif
