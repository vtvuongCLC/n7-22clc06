#ifndef _STRUCTLIST_H
#define _STRUCTLIST_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//SUPPORT STRUCTS
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
    struct Schoolyear;
    struct StudyClass;
    struct Student;

    struct Semester;
    struct Course;
    struct CourseStudent;
    struct EnrolledCourse;

//STRUCT IMPLEMENTATION

    //ACCOUNTS
    struct StaffAccount{
        string username;
        string password;
        string name;
        StaffAccount* nextAccount = nullptr;
    };

    //DATABASE INFORMATION
    struct DataBase {
        string      YearFile     = "Schoolyear";
        string      SemesterFile = "Semester";
        int         numYear      = 0;
        
        Semester*    SemesterList   = nullptr;

        Schoolyear*  YearList = nullptr;
        Schoolyear** quickSchoolPtr = nullptr;
    };

    //SCHOOLYEARS
    struct Schoolyear {
        int    index;

        int start,end;
        string year;
        
        int numCLC  = 0;
        int numAPCS = 0;
        int numVP   = 0;
        StudyClass*** qClassPtr  = nullptr;

        StudyClass*   listCLC    = nullptr;
        StudyClass*   listAPCS   = nullptr;
        StudyClass*   listVP     = nullptr;

        
        
        Schoolyear*  nextYear      = nullptr;
        Schoolyear*  prevYear      = nullptr;
    };

    //CLASSES
    struct StudyClass {
        string year;
        string className;
        string classType;
        int    numStudent = 0;

        Student*    listStudent     = nullptr;
        Student**   quickStudentPtr = nullptr;
        StudyClass* nextClass       = nullptr;
    };

    //STUDENTS
    struct SemEnrollCourse{
        int semester;
        string year;
        EnrolledCourse* CourseList          = nullptr;
        EnrolledCourse* lastEnrolledCourse  = nullptr;
        SemEnrollCourse* nextSem            = nullptr;
    };
    struct Student {
        int No;
        string yearName;
        string className;
        string password;
        string programtype;
        Info   dInfo;

        double ovrGPA;

        SemEnrollCourse* pSemester  = nullptr;
        Student*        nextStudent = nullptr;
    };

    //SEMESTERS 
    struct Semester {
        int    index;
        int    semester;
        string year;
        string start, end;

        int    numCourse = 0;
        Course**  HandlingCourse = nullptr;
        Course*   CourseList     = nullptr;

        Semester* nextSemester   = nullptr;
    };

    //COURSES
    struct Course {
        int        courseIndex;
        int        numCurStudents = 0;
        CourseInfo thisCourseInfo;
        
        CourseStudent* listStudent = nullptr;
        Course*        nextCourse  = nullptr;
        Course*        prevCourse  = nullptr;
    };
    struct CourseStudent {
        int        no;
        int        yearIndex;
        int        classtypeIndex;
        int        classIndex;
        int        studentIndex;

        Scoreboard savedScore;

        Student*       ptoStudent  = nullptr;

        CourseStudent* nextStudent = nullptr;
        CourseStudent* prevStudent = nullptr;
    };
    struct EnrolledCourse {
        
        Scoreboard*     Score      = nullptr;
        Course*         ptoCourse  = nullptr;
        EnrolledCourse* nextCourse = nullptr;
        EnrolledCourse* prevCourse = nullptr;
    };
#endif
