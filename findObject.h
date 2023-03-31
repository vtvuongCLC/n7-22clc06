#ifndef _FIND_OBJECT_H_
#define _FIND_OBJECT_H_
#include "header3OfTu.h"

void viewInfoOfCourse(CourseInfo infoThisCourse);
void viewListOfCourses(Semester* curSemester);
void viewAllListOfCourses(Schoolyear* firstYear);
Course* findTheCourse(Course* pCourse, string NameCourse, string IDCourse, string NameClass);
bool checkExistStudentInCourse(CourseStudentList* listStudent, string studID);
void updateCourseInformation(Semester* curSemester);
// StudyClass* findStudyClass(StudyClass* classHead, string className);
// Student* findStudent(Student* studentHead, string IDStudent);
// void exportListStudentsInCourse(Course thisCourse);
// int countStudentIn1Course(Course* thisCourse);
// Scoreboard* findStudentInScoreboard(Scoreboard* thisBoard, string studentID);
// void addStudentToCourse(Semester* curSemester);
// void displayStudentInCourse(Course* thisCourse);
// void removeStudentFromCourse(Semester* curSemester);
// void removeCourse(Semester* curSemester);
// void deleteAllStudentsOfCourse(Course* thisCourse);
#endif
