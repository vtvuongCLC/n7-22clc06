#ifndef _ULTILITY_FUNCTION
#define _ULTILITY_FUNCTION
#include "structlist.h"

bool validInfo(BirthDate birth,char gender);

void AddStudentManual(Student* &listStudent, string yearName, string className, string classType, int &numStudent);
void AddStudentCSV(Student* &listStudent, string yearName, string className, string classType, int &numStudent);
void AddStudent(Student* &listStudent, string yearName, string className, string classType, int &numStudent);
void AddClass(StudyClass* &listClass, string yearName, string classType);
Schoolyear* getYearData(Schoolyear* listYear);
void AddYear(DataBase &DB);

Schoolyear* navigateYear(Schoolyear* listYear, int userindex);
StudyClass* navigateClass(StudyClass* listClass, int userindex);
Course* navigateCourse(Course* listCourse, int userindex);
Student* navigateStudent(Student* listStudent, int userindex);

CourseStudent* FindStudentIndex(Schoolyear* listYear,string yearName, string className, int classtype, string StudID,Course* curCourse, Semester* curSemester);
CourseStudent* findStudentInCourse(CourseStudent* listStudent, string studID);
Course* findTheCourse(Semester* pSemester, string year, int semester, string NameCourse, string IDCourse, string NameClass);

void StudentPtrBinder(Student** quickStudentPtr, Student* listStudent);
void ClassPtrBinder(StudyClass** quickClassPtr, StudyClass* listClass);
void QuickPtrBinder(DataBase &DB);
void QuickPtrDebinder(DataBase &DB);

void LinkEnrolledCourse(Student *&curStudent, Course *curCourse, CourseStudent* curCourseStudent, Semester* curSemester);
void getCourseListForHandlingArr(string curYearName, Semester* listSemester, Semester** HandlingArr, int &k);

void UpdateStudentInfo(Student *curStudent);
void UpdateCourseInfo(CourseInfo &curCourseInfo);
bool UploadListofStud(Course* &curCourse, Semester* curSemester, Schoolyear* listYear);
void NewCourse(Course* &firstCour);
void InitSemester(Semester* &Sem, int semester, string year);
void addStudentToCourse(Course* curCourse,Semester* curSemester, Schoolyear* curYear);

void removeEnrollCourse(Student* removedStudent, Course* pCourse, Semester* curSemester);
void removeStudentFromCourse(Course* curCourse, Semester* curSemester, Schoolyear* curYear);
void removeCourse(Semester* curSemester);

void ExportCourseStudent(Course* curCourse);
bool importCourseScore(Course* &curCourse);
void ChangeStudentScore(CourseStudent* listCourseStudent);

void ChangePasswordStaff(StaffAccount* curStaff);
void ChangePasswordStudent(Student* curStudent);
int searchStudentAccount(string username, string password, StudyClass* listClass, Student* &toStudent, StudyClass* &toStudyClass);
#endif