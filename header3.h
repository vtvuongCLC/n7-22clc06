#ifndef _NSTRUCT_H
#define _NSTRUCT_H
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
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
    int No;
    string StudentID;
    string StudentName;
    string studyClassName;
    double OtherMark = 0;
    double Midterm = 0;
    double Final = 0;
    Scoreboard* nextBoard = nullptr;
    Scoreboard* prevBoard = nullptr;
};

struct Course {
    string courseID;
    string courseName;
    string className;
    string Teacher;
    int credit;
    int maxStudent;
    dDate CourseDate;
    Scoreboard* thisCourseScore = nullptr;
    double ovrGPA;
    Course* nextCourse = nullptr;
    Course* prevCourse = nullptr;
};
struct Semester {
    string start, end;
    int semesterIndex;
    Course* Courselist = nullptr;
    double GPA;
    Semester* nextSem = nullptr;
};
struct Info {
    int No;
    string StudentID;
    string FirstName;
    string LastName;
    string Gender;
    BirthDate Birth;
    string SocialID;
};
struct Student {
    string yearName;
    string className;
    string password;
    Info dInfo;
    Student* nextStudent = nullptr;
};
struct StudyClass {
    string className;
    Student* listStudent = nullptr;
    StudyClass* nextClass = nullptr;
};
struct Schoolyear {
    string year;
    Semester* firstSem = nullptr;
    StudyClass* listClass = nullptr;
    Schoolyear* nextYear = nullptr;
};
#endif
