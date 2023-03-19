#ifndef _NSTRUCT_H
#define _NSTRUCT_H
#include <iostream>
#include <string>
#include <fstream>

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
    double OtherMark;
    double Midterm;
    double Final;
    Scoreboard* nextBoard = nullptr;
};
struct Info {
    int No;
    string StudentID;
    string FirstName;
    string LastName;
    string Gender;
    BirthDate Birth;
    string SocialID;
    Info* pNext = nullptr;
};
struct Student {
    string yearName;
    string className;
    Info dInfo;
    Student* nextStudent = nullptr;
    Student* prevStudent = nullptr;
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
    Student* StudentList = nullptr;
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
struct StudyClass {
    string className;
    Student* pStudent = nullptr;
    StudyClass* nextClass = nullptr;
};
struct Schoolyear {
    string year;
    Semester* firstSem = nullptr;
    StudyClass* listClass = nullptr;
    Schoolyear* nextYear = nullptr;
};
#endif