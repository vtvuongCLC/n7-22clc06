#ifndef _STRUCTLIST_H
#define _STRUCTLIST_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//SUPPORT INFO STRUCTS
struct BirthDate {
    int day;
    int month;
    int year;
};
struct dDate {
    string day;
    string session;
};
struct Scoreboard {
    double totalMark   = 0;
    double otherMark   = 0;
    double midtermMark = 0;
    double finalMark   = 0;
};      
struct Info {
    string    StudentID;
    string    FirstName;
    string    LastName;
    string    Gender;
    BirthDate Birth;
    string    SocialID;
};
struct CourseInfo {
    string courseID;
    string courseName;
    string className;
    string Teacher;
    int    maxStudent;
    int    credit;
    dDate  CourseDate;
};

//FUNCTIONAL STRUCTS

//STRUCTS PROTOTYPES
struct Course;

//STRUCT IMPLEMENTATION
struct EnrolledCourse {
    
    Scoreboard*     Score      = nullptr;
    Course*         ptoCourse  = nullptr;
    EnrolledCourse* nextCourse = nullptr;
    EnrolledCourse* prevCourse = nullptr;
};
struct Student {
    int No;
    string yearName;
    string className;
    string password;
    Info   dInfo;

    EnrolledCourse* CourseList  = nullptr;
    EnrolledCourse* lastEnrolledCourse  = nullptr;
    Student*        nextStudent = nullptr;
};
struct StudyClass {
    string className;
    int    numStudent = 0;

    Student*    listStudent     = nullptr;
    Student**   quickStudentPtr = nullptr;
    StudyClass* nextClass       = nullptr;
};
struct CourseStudent {
    int        no;
    int        yearIndex;
    int        classIndex;
    int        studentIndex;
    Scoreboard savedScore;

    Student*       ptoStudent  = nullptr;
    CourseStudent* nextStudent = nullptr;
    CourseStudent* prevStudent = nullptr;
};
struct Course {
    int        courseIndex;
    int        numCurStudents;
    string     year;
    string     semester;
    CourseInfo thisCourseInfo;
    
    CourseStudent* listStudent = nullptr;
    Course*        nextCourse  = nullptr;
    Course*        prevCourse  = nullptr;
};
struct Semester {
    int    index;
    int    semester;
    string year;
    string start, end;

    Course*   CourseList   = nullptr; 
    Semester* nextSemester = nullptr;
};
struct Schoolyear {
    int    index;
    int    numClass = 0;
    string year;
    
    StudyClass*  listClass     = nullptr;
    StudyClass** quickClassPtr = nullptr;
    Schoolyear*  nextYear      = nullptr;
};

struct DataBase {
    string      YearFile     = "Schoolyear";
    string      SemesterFile = "Semester";
    int         numYear      = 0;

    Schoolyear*  YearList       = nullptr;
    Schoolyear** quickSchoolPtr = nullptr;
    Semester*    SemesterList   = nullptr; // up to 3
};
#endif
