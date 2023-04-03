#ifndef _FIND_OBJECT_H_
#define _FIND_OBJECT_H_
#include "structlist.h"

void viewInfoOfCourse(CourseInfo infoThisCourse);
void viewListOfCourses(Semester* curSemester);
void viewAllListOfCourses(Schoolyear* firstYear);
Course* findTheCourse(Course* pCourse, string NameCourse, string IDCourse, string NameClass);
CourseStudent* findStudentInCourse(CourseStudent* listStudent, string studID);
void updateCourseInformation(Semester* curSemester);
void addStudentToCourse(Semester* curSemester, Schoolyear* curYear);
void displayStudentInCourse(Course* thisCourse);
void removeEnrollCourse(Student* removedStudent, Course* pCourse);
void removeStudentFromCourse(Semester* curSemester, Schoolyear* curYear);
void removeCourse(Semester* curSemester);
#endif
