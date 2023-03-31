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
    double totalMark = 0;
    double otherMark = 0;
    double midtermMark = 0;
    double finalMark = 0;
};      
struct Info {
    string StudentID;
    string FirstName;
    string LastName;
    string Gender;
    BirthDate Birth;
    string SocialID;
};
struct CourseInfo {
    string courseID;
    string courseName;
    string className;
    string Teacher;
    int credit;
    dDate CourseDate;
};

//FUNCTIONAL STRUCTS
struct EnrolledCourse {
    int no;
    Scoreboard Score;
    Course* thisCourse = nullptr;
    EnrolledCourse* nextCourse = nullptr;
};
struct Student {
    int No;
    string yearName;
    string className;
    string password;
    Info dInfo;
    EnrolledCourse* CourseList = nullptr;
    Student* nextStudent = nullptr;
};
struct StudyClass {
    string className;
    int numStudent = 0;
    Student* listStudent = nullptr;
    Student** quickStudentPtr= nullptr;
    StudyClass* nextClass = nullptr;
};
struct CourseStudentList {
    int classIndex;
    int studentIndex;
    Student** toStudent = nullptr;
    CourseStudentList* nextStudent = nullptr;
};
struct Course {
    CourseInfo thisCourse;
    int maxStudent;
    CourseStudentList* listStudent = nullptr;
    Course* nextCourse = nullptr;
};
struct Semester {
    string start, end;
    int semesterIndex;
    string semester;
    Course* CourseList = nullptr;
    Semester* nextSemester = nullptr;
};
struct Schoolyear {
    string year;
    Semester* SemesterList = nullptr;
    int numClass = 0;
    StudyClass* listClass = nullptr;
    StudyClass** quickClassPtr = nullptr;
    Schoolyear* nextYear = nullptr;
};
#endif
