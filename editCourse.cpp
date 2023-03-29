#include "findObject.h"

void viewInfoOfCourse(Course* thisCourse){

    cout << left << setw(15) << thisCourse->courseID 
             << left << setw(25) << thisCourse->courseName 
             << left << setw(15) << thisCourse->className
             << left << setw(25) << thisCourse->Teacher
             << left << setw(3)  << thisCourse->credit 
             << left << setw(4)  << thisCourse->maxStudent 
             << left << setw(3)  << thisCourse->CourseDate.day
                                 << ", " << thisCourse->CourseDate.session << endl;

}

void viewListOfCourses(Semester* curSemester){ 
    Course* pCourse = curSemester->firstCourse;
    if(!pCourse){
        cout << "This semester hasn't yet been added course!!! First, please add the course to this semester";
        return;
    }
    cout << "The courses list in semester " << curSemester->semesterIndex << endl << endl;
    while(pCourse){
        viewInfoOfCourse(pCourse);
        pCourse = pCourse->nextCourse;
    }
}

void viewAllListOfCourses(Schoolyear* firstYear){
    while(firstYear){

        cout << "The courses list of " << firstYear->year << " year students " << endl;
        cout << left << setw(15) << "Course ID" 
             << left << setw(25) << "Course Name" 
             << left << setw(15) << "Class Name"
             << left << setw(25) << "Teacher"
             << left << setw(3)  << "Credit" 
             << left << setw(4)  << "Max Students" 
             << left << setw(3)  << "Day, Session" << endl;

        Semester* firstSemester = firstYear->firstSem;

        while(firstSemester){

            viewListCourses(firstSemester);
            firstSemester = firstSemester->nextSem;
        }
        firstYear = firstYear->nextYear;
    }
}

Course* findTheCourse(Course* pCourse, string NameCourse, string IDCourse, string NameClass){
    while(pCourse){
        if(NameCourse == pCourse->courseName 
            && IDCourse == pCourse->courseID 
            && NameClass == pCourse->className) 
        break;
        pCourse = pCourse->nextCourse;
    }
    return pCourse;
} 


// StudyClass* findStudyClass(StudyClass* pClass, string name){
//     while(pClass){
//         if(pClass->className == name) break;
//         pClass = pClass->nextClass;
//     }
//     return pClass;
// }

// Student* findStudent(Student* pStudent, string IDStudent){ 
//     while(pStudent){
//         if(pStudent->dInfo.StudentID == IDStudent) break;
//         pStudent = pStudent->nextStudent;
//     }
//     return pStudent;
// }


// void exportListStudentsInCourse(Course* thisCourse){
//     ofstream ofs;
//     ofs.open(thisCourse->courseName + '-' + thisCourse->courseID + '-' + thisCourse->className + ".csv");
//     while(thisCourse->thisCourseScore){
//         ofs << thisCourse->thisCourseScore->No << "," 
//             << thisCourse->thisCourseScore->StudentID << "," 
//             << thisCourse->thisCourseScore->StudentName << "," 
//             << thisCourse->thisCourseScore->Midterm << "," 
//             << thisCourse->thisCourseScore->OtherMark << "," 
//             << thisCourse->thisCourseScore->Final << endl;
//         thisCourse->thisCourseScore = thisCourse->thisCourseScore->nextBoard;
//     }
//     ofs.close();
// }
// int countStudentIn1Course(Course* thisCourse){
//     int countStudent = 0;
//     while(thisCourse->thisCourseScore){
//         thisCourse->thisCourseScore = thisCourse->thisCourseScore->nextBoard;
//         countStudent++;
//     }
//     return countStudent;
// }
// Scoreboard* findStudentInScoreboard(Scoreboard* thisBoard, string studentID){
//     while(thisBoard){
//         if(studentID == thisBoard->StudentID) break;
//         thisBoard = thisBoard->nextBoard;
//     }
//     return thisBoard;
// }
// void addStudentToCourse(Semester* curSemester){
//     string courseName, courseID, className;
//     cout << "Enter the course name you want to add student: ";
//     getline(cin, courseName);
//     cout << "Enter the course ID you want to add student: ";
//     getline(cin, courseID);
//     cout << "Enter the class name of course you want to add student: ";
//     getline(cin, className);

//     Course* thisCourse = findTheCourse(curSemester->Courselist, courseName, courseID, className);
//     if(!thisCourse) {
//         cout << "This course doesn't exist!\n";
//         return;
//     }
//     int numStudent = countStudentIn1Course(thisCourse);

//     if(numStudent >= thisCourse->maxStudent){
//         cout << "The course is having maximum student!!! You cannot add student to this course.\n";
//         return;
//     }

//     // còn phần check xem student có tồn tại trong lớp sinh hoạt hay không
//     string studentName, studentID; 
//     int no;
//     cout << "Enter the student name you want to add: ";
//     getline(cin, studentName);
//     cout << "Enter the student ID you want to add: ";
//     getline(cin, studentID);
//     cout << "Enter the number of No you want to add: ";
//     cin >> no;

//     Scoreboard* studentAdd = findStudentInScoreboard(thisCourse->thisCourseScore, studentID);
//     if(studentAdd != nullptr) {
//         cout << "This student has existed in this course!\n";
//         return;
//     }
//     studentAdd = new Scoreboard;
//     studentAdd->No = no;
//     studentAdd->StudentID = studentID;
//     studentAdd->StudentName = studentName;
//     studentAdd->nextBoard = thisCourse->thisCourseScore;
//     if(thisCourse->thisCourseScore)
//         thisCourse->thisCourseScore->prevBoard = studentAdd;
//     thisCourse->thisCourseScore = studentAdd;
// }

// void displayStudentInCourse(Course* thisCourse){
//     while(thisCourse->thisCourseScore){
//         cout << left << setw(5)  << thisCourse->thisCourseScore->No
//              << left << setw(15) << thisCourse->thisCourseScore->StudentID 
//              << left << setw(40) << thisCourse->thisCourseScore->StudentName 
//              << left << setw(20) << thisCourse->thisCourseScore->studyClassName << endl;
//         thisCourse->thisCourseScore = thisCourse->thisCourseScore->nextBoard;
//     }
// }
// void removeStudentFromCourse(Semester* curSemester){
//     string courseName, courseID, className;
//     cout << "Enter the course name you want to remove student: ";
//     getline(cin, courseName);
//     cout << "Enter the course ID you want to remove student: ";
//     getline(cin, courseID);
//     cout << "Enter the class name of course you want to remove student: ";
//     getline(cin, className);

//     Course* thisCourse = findTheCourse(curSemester->Courselist, courseName, courseID, className);
//     if(thisCourse == nullptr){
//         cout << "This course doesn't exist!\n";
//         return;
//     }

//     displayStudentInCourse(thisCourse);

//     string studentID;
//     cout << "Enter the student ID you want to remove from this course: ";
//     getline(cin, studentID);
//     Scoreboard* studentRemove = findStudentInScoreboard(thisCourse->thisCourseScore, studentID);
//     if(studentRemove == nullptr){
//         cout << "This student hasn't enrroled this course!\n";
//         return;
//     }
//     Scoreboard* tmp = studentRemove->nextBoard;
//     if(studentRemove->prevBoard)    studentRemove->prevBoard->nextBoard = tmp;
//     else thisCourse->thisCourseScore = tmp;

//     if(tmp)     tmp->prevBoard = studentRemove->prevBoard;

//     delete studentRemove;

//     cout << "This student was removed from this course\n";
// }

// void deleteAllStudentsOfCourse(Course* thisCourse){
//     while(thisCourse->thisCourseScore){
//         Scoreboard* tmp = thisCourse->thisCourseScore;
//         thisCourse->thisCourseScore = thisCourse->thisCourseScore->nextBoard;
//         delete tmp;
//     }
// }

// void removeCourse(Semester* curSemester){
//     string courseName, courseID, className;
//     cout << "Enter the course name you want to remove: ";
//     getline(cin, courseName);
//     cout << "Enter the course ID you want to remove: ";
//     getline(cin, courseID);
//     cout << "Enter the class name of course you want to remove: ";
//     getline(cin, className);

//     Course* thisCourse = findTheCourse(curSemester->Courselist, courseName, courseID, className);
//     if(thisCourse == nullptr){
//         cout << "This course doesn't exist!\n";
//         return;
//     }

//     Course* tmp = thisCourse->nextCourse;
//     if(thisCourse->prevCourse)  thisCourse->prevCourse->nextCourse = tmp;
//     else curSemester->Courselist = tmp;

//     if(tmp)     tmp->prevCourse = thisCourse->prevCourse;

//     deleteAllStudentsOfCourse(thisCourse);

//     delete thisCourse;

//     cout << "This course was removed from system\n";
// }