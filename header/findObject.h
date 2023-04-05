#ifndef _FIND_OBJECT_H_
#define _FIND_OBJECT_H_
#include "structlist.h"
#include "displayfunction.h"

//void EnterCourseData(Course* &firstCour);
void InitSemester(Semester* &Sem, int semester, string year);
void viewInfoOfCourse(CourseInfo infoThisCourse);
void viewListOfCoursesIn1Semester(Semester* curSemester);
void viewAllListOfCourses(Semester* curSemester);
Course* findTheCourse(Semester* pSemester, string year, int semesterIdx, string NameCourse, string IDCourse, string NameClass);
void updateCourseInformation(Semester* curSemester);
CourseStudent* findStudentInCourse(CourseStudent* listStudent, string studID);
void LinkEnrolledCourseToCourse(Student *curStudent, Course *curCourse);
bool FindStudentIndexInStudyClass(Schoolyear* curYear, CourseStudent* newStudent, string year, string className, string StudID,Course* curCourse);
void addStudentToCourse(Semester* curSemester, Schoolyear* curYear);
void displayStudentInCourse(Course* thisCourse);
void removeEnrollCourse(Student* removedStudent, Course* pCourse);
void removeStudentFromCourse(Semester* curSemester, Schoolyear* curYear);
void removeCourse(Semester* curSemester);
void printListCoursesOfAStudent(Student* thisStudent, string semester, string year);
void menu1Year(DataBase* DB);
#endif
