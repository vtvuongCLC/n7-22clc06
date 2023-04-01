#include "header3OfTu.h"
#ifdef _INITSEMESTER_H
#define _INITSEMESTER_H

Semester* FindUninitSem(Schoolyear* year);
void LinkEnrolledCourse(Student *&curStudent, Course *curCourse);
bool FindStudentIndex(StudyClass* firstClass,CourseStudentList* &CourseStud, string className, string StudID,Course* curCourse);
bool UploadListofStud(Course* &curCourse,StudyClass* curClass);
void EnterCourseData(Course*& firstCour);
void InitSemester(Semester*& Sem, int i);
void LinkAndInit(Schoolyear*& Year);
#endif
