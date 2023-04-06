#ifndef _SEMESTER_AND_COURSE_H_
#define _SEMESTER_AND_COURSE_H_
#include "structlist.h"

//FUNCTION TO MANAGE SEMESTER
//Semester* FindUninitSem(Schoolyear* year);
void LinkEnrolledCourse(Student *&curStudent, Course *curCourse, CourseStudent* curCourseStudent);
bool FindStudentIndex(Schoolyear* listYear,CourseStudent* &CourseStud, string yearName,string className, string StudID,Course* curCourse);
bool UploadListofStud(Course* &curCourse, Schoolyear* listYear);
void InitSemester(Semester* &Sem, int semester, string year);
//void LinkAndInit(Semester* &curSemester, Schoolyear* listYear);

//FUNCTION TO MANAGE COURSE 
void EnterCourseData(Course* &firstCour);
void viewInfoOfCourse(CourseInfo infoThisCourse);
void viewListOfCoursesIn1Semester(Semester* curSemester);
void viewAllListOfCourses(Semester* curSemester);
Course* findTheCourse(Semester* pSemester, string year, int semesterIdx, string NameCourse, string IDCourse, string NameClass);
void updateCourseInformation(Semester* curSemester);
CourseStudent* findStudentInCourse(CourseStudent* listStudent, string studID);
void addStudentToCourse(Semester* curSemester, Schoolyear* curYear);
void displayStudentInCourse(Course* thisCourse);
void removeEnrollCourse(Student* removedStudent, Course* pCourse);
void removeStudentFromCourse(Semester* curSemester, Schoolyear* curYear);
void removeCourse(Semester* curSemester);
void printListCoursesOfAStudent(Student* thisStudent, string semester, string year);

void menu1Year(DataBase* DB);
#endif
