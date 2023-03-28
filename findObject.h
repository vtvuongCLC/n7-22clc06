#ifndef _FIND_OBJECT_H_
#define _FIND_OBJECT_H_
#include "header3.h"

void viewListCourses(Semester* curSemester);
Course* findTheCourse(Course* thisCourse, string nameCourse);
void updateCourseInformation(Semester* curSemester);
// SchoolYear* findSchoolYear(SchoolYear* yearHead, string yearName);
StudyClass* findStudyClass(StudyClass* classHead, string className);
Student* findStudent(Student* studentHead, string IDStudent);
void exportListStudentsInCourse(Course thisCourse);
int countStudentIn1Course(Course* thisCourse);
Scoreboard* findStudentInScoreboard(Scoreboard* thisBoard, string studentID);
void addStudentToCourse(Semester* curSemester);
void displayStudentInCourse(Course* thisCourse);
void removeStudentFromCourse(Semester* curSemester);
void removeCourse(Semester* curSemester);
void deleteAllStudentsOfCourse(Course* thisCourse);
#endif