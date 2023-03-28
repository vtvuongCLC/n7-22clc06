#ifndef _NSTRUCT_H
#define _NSTRUCT_H
#include <string>
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
struct ListCourse{
    Course* thisCourse;
    Scoreboard thisScoreCourse;
    ListCourse* nextCourse = nullptr;
    ListCourse* prevCourse = nullptr;
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
    ListStudent* firstStudent;
};
struct Semester {
    string start, end;
    int semesterIndex;
    ListCourse* firstCourse = nullptr;
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
struct Student {
    string yearName;
    string className;
    string password;
    Info dInfo;
    ListCourse* firstCourse;   
};
struct ListStudent{
    int No;
    Student* thisStudent;   
    ListStudent* nextStudent;
};
struct StudyClass{
    string className;
    ListStudent* firstStudent = nullptr;
    StudyClass* nextClass = nullptr;
};
struct Schoolyear {
    string year;
    Semester* firstSem = nullptr;
    StudyClass* listClass = nullptr;
    Schoolyear* nextYear = nullptr;
};
#endif
