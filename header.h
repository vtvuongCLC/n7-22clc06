#ifndef _NSTRUCT_H
#define _NSTRUCT_H
#include <iostream>
#include <string>
#include <fstream>

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
    string nameStudyClass;
    Student* pStudent = nullptr;
    StudyClass* nextClass = nullptr;
};
struct SchoolYear{
    int yearStart, yearEnd;
    StudyClass* pClass;
    SchoolYear* prevYear;
    Semester* SemesterList;
};


void getInfo(Info &student, ifstream& ifs);
void getStudent(StudyClass &ClassToAdd);
void viewListCourses(Semester* curSemester);
Course* findTheCourse(Course* thisCourse, string nameCourse);
#endif