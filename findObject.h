#ifndef _FIND_OBJECT_H_
#define _FIND_OBJECT_H_
#include "header.h"

void viewListCourses(Semester* curSemester);
Course* findTheCourse(Course* thisCourse, string nameCourse);
SchoolYear* findSchoolYear(SchoolYear* yearHead, string yearName);
StudyClass* findStudyClass(StudyClass* classHead, string className);
Student* findStudent(Student* studentHead, string IDStudent);
void exportListStudentsInCourse(Course thisCourse);
int countStudentIn1Course(Course* thisCourse);
#endif
