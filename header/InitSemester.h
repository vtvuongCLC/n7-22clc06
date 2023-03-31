#ifndef _INITSEMESTER_H
#define _INITSEMESTER_H
#include "structlist.h"
Semester* FindUninitSem(Schoolyear* year);
void FindStudentIndex(StudyClass* firstClass,CourseStudentList* &curCourse, string className, string StudID);
bool UploadListofStud(Course* &curCourse,StudyClass* curClass);
void EnterCourseData(Course*& firstCour);
void InitSemester(Semester*& Sem, int i);
void LinkAndInit(Schoolyear*& Year);
#endif
