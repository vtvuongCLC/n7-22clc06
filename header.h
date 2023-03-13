#ifndef _NSTRUCT_H
#define _NSTRUCT_H
#include <string>
using namespace std;
struct BirthDate{
    int day;
    int month;
    int year;
};
struct dDate{
    string day;
    string session;
};
struct Scoreboard{
    int No;
    string StudentID;
    string StudentName;
    double OtherMark;
    double Midterm;
    double Final;
    Scoreboard* nextBoard = nullptr;
};

struct Course{
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
};
struct Semester{
    int semesterIndex;
    Course* Courselist;
    double GPA;
};
struct Info{
    string StudentID;
    string FirstName;
    string LastName;
    bool isMale;
    BirthDate Birth;
    string SocialID;
};
struct Student{
    int No;
    Info This_Student;
    string mainClass;
    Semester* SemesterList = nullptr;
    Student* nextStudent = nullptr;
};
struct StudyClass{
    Student* pStudent = nullptr;
    StudyClass* nextClass = nullptr;
};
struct Schoolyear{
    int yearStart, yearEnd;
    StudyClass* pClass = nullptr;
    Schoolyear* nextYear = nullptr; 
};
#endif