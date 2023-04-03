#ifndef _INITSEMESTER_H
#define _INITSEMESTER_H
#include "structlist.h"

Semester* FindUninitSem(Schoolyear* year);
void LinkEnrolledCourse(Student *&curStudent, Course *curCourse);
bool FindStudentIndex(StudyClass* firstClass,CourseStudent* &CourseStud, string className, string StudID,Course* curCourse);
bool UploadListofStud(Course* &curCourse,StudyClass* curClass);
void EnterCourseData(Course*& firstCour);
void InitSemester(Semester*& Sem, int i);
void LinkAndInit(Schoolyear*& Year);
#endif
