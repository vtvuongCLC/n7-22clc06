#include "header3.h"
#ifdef _INITSEMESTER_H
#define _INITSEMESTER_H

Semester* isInit(Schoolyear* year);
bool UploadListofStud(Course* &curCour, string CoursName);
void EnterCourseData(Course*& firstCour);
void InitSemester(Semester*& Sem, int i);
void LinkAndInit(Schoolyear*& Year);
#endif
