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
bool studentExistInCourse(Course* thisCourse, string studentID);
void addStudentToCourse(Semester* curSemester);
void displayStudentInCourse(Course* thisCourse);
#endif
