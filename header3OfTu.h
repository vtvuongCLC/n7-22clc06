#ifndef _NEWSTRUCT_H
#define _NEWSTRUCT_H
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
    double totalMark = 0;
    double otherMark = 0;
    double midtermMark = 0;
    double finalMark = 0;
};      

struct Course {
    string semester;
    string courseID;
    string courseName;
    string className;
    string Teacher;
    int credit;
    int maxStudent;
    dDate CourseDate;
    Course* nextCourse;
    StudentLoc* firstStudentLoc = nullptr;
};
struct EnrolledCourse {
    Scoreboard Score;
    EnrolledCourse* nextCourse = nullptr;
    Course* thisCourse;
};
struct Semester {
    string start, end;
    int semesterIndex;
    Course* firstCourse = nullptr;
    Semester* nextSem = nullptr;
};
struct Info {
    string StudentID;
    string FirstName;
    string LastName;
    string Gender;
    BirthDate Birth;
    string SocialID;
};
struct StudentLoc {
    int no;
    int classIndex;
    int studentIndex;
    StudentLoc* nextStudentLoc;
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
    int numStudent;
    Student* listStudent = nullptr;
    Student** quickPtr = nullptr;
    StudyClass* nextClass = nullptr;
};
struct Schoolyear {
    string year;
    Semester* firstSem = nullptr;
    StudyClass* listClass = nullptr;
    Schoolyear* nextYear = nullptr;
};
#endif
