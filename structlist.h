#ifndef _STRUCTLIST_H
#define _STRUCTLIST_H

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
struct SharedCourseInfo {
    string courseID;
    string courseName;
    string className;
    string Teacher;
    int credit;
    dDate CourseDate;
};
struct EnrolledCourse {
    SharedCourseInfo CourseInfo;
    Scoreboard Score;
    EnrolledCourse* nextCourse = nullptr;
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
    Student** quickStudentPtr= nullptr;
    StudyClass* nextClass = nullptr;
};
struct StudentLoc {
    int classIndex;
    int studentIndex;
};
struct Course {
    SharedCourseInfo thisCourse;
    int maxStudent;
    Student* listStudent = nullptr;
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
    int numClass;
    StudyClass* listClass = nullptr;
    StudyClass** quickClassPtr = nullptr;
    Schoolyear* nextYear = nullptr;
};
#endif
