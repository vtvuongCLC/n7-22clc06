#ifndef _ULTILITY_FUNCTION
#define _ULTILITY_FUNCTION
#include "structlist.h"

bool validInfo(Info infoparam,char gender);

void AddStudentManual(Student* &listStudent, string yearName, string className, int &numStudent);
void AddStudentCSV(Student* &listStudent, string yearName, string className, int &numStudent);
void AddStudent(Student* &listStudent, string yearName, string className, int &numStudent);
void AddClass(StudyClass* &listClass);
string getYearData(Schoolyear* listYear);
void AddYear(DataBase &DB);

Schoolyear* navigateYear(Schoolyear* listYear, int userindex);
StudyClass* navigateClass(StudyClass* listClass, int userindex);
Course* navigateCourse(Course* listCourse, int userindex);
bool FindStudentIndex(Schoolyear* listYear,CourseStudent* &CourseStud, string yearName,string className, string StudID,Course* curCourse);
CourseStudent* findStudentInCourse(CourseStudent* listStudent, string studID);
Course* findTheCourse(Semester* pSemester, string year, int semester, string NameCourse, string IDCourse, string NameClass);

void QuickPtrBinder(DataBase &DB);
void LinkEnrolledCourse(Student *&curStudent, Course *curCourse, CourseStudent* curCourseStudent);

void UpdateCourseInfo(CourseInfo &curCourseInfo);
bool UploadListofStud(Course* &curCourse, Schoolyear* listYear);
void NewCourse(Course* &firstCour);
void InitSemester(Semester* &Sem, int semester, string year);
void addStudentToCourse(Course* curCourse, Schoolyear* curYear);

void removeEnrollCourse(Student* removedStudent, Course* pCourse);
void removeStudentFromCourse(Course* curCourse, Schoolyear* curYear);
void removeCourse(Semester* curSemester);
#endif