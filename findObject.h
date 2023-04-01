#ifndef _FIND_OBJECT_H_
#define _FIND_OBJECT_H_
#include "header3OfTu.h"
#include "InitSemester.h"

void LinkEnrolledCourse(Student *&curStudent, Course *curCourse);
bool FindStudentIndex(StudyClass* firstClass,CourseStudentList* &CourseStud, string className, string StudID,Course* curCourse);
void viewInfoOfCourse(CourseInfo infoThisCourse);
void viewListOfCourses(Semester* curSemester);
void viewAllListOfCourses(Schoolyear* firstYear);
Course* findTheCourse(Course* pCourse, string NameCourse, string IDCourse, string NameClass);
CourseStudentList* checkExistStudentInCourse(CourseStudentList* listStudent, string studID);
void updateCourseInformation(Semester* curSemester);
void addStudentToCourse(Semester* curSemester, StudyClass* pClass);
// void displayStudentInCourse(Course* thisCourse);
void removeEnrollCourse(Student* removedStudent, Course* pCourse);
void removeStudentFromCourse(Semester* curSemester);
// void removeCourse(Semester* curSemester);
// void deleteAllStudentsOfCourse(Course* thisCourse);
#endif
