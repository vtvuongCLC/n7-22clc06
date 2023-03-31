#include "findObject.h"

void viewInfoOfCourse(CourseInfo infoThisCourse){

    cout << left << setw(15) << infoThisCourse.courseID 
             << left << setw(25) << infoThisCourse.courseName 
             << left << setw(15) << infoThisCourse.className
             << left << setw(25) << infoThisCourse.Teacher
             << left << setw(3)  << infoThisCourse.credit
             << left << setw(4)  << infoThisCourse.maxStudent  
             << left << setw(3)  << infoThisCourse.CourseDate.day
                                 << ", " << infoThisCourse.CourseDate.session;                                 
}

void viewListOfCourses(Semester* curSemester){ 
    Course* pCourse = curSemester->CourseList;
    if(!pCourse){
        cout << "This semester hasn't yet been added course!!! First, please add the course to this semester";
        return;
    }
    cout << "The courses list in semester " << curSemester->semesterIndex << endl << endl;
    while(pCourse){
        viewInfoOfCourse(pCourse->infoThisCourse);
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

        Semester* firstSemester = firstYear->SemesterList;

        while(firstSemester){

            viewListOfCourses(firstSemester);
            firstSemester = firstSemester->nextSemester;
        }
        firstYear = firstYear->nextYear;
    }
}
Course* findTheCourse(Course* pCourse, string NameCourse, string IDCourse, string NameClass){
    while(pCourse){
        if(NameCourse == pCourse->infoThisCourse.courseName 
            && IDCourse == pCourse->infoThisCourse.courseID 
            && NameClass == pCourse->infoThisCourse.className) 
        break;
        pCourse = pCourse->nextCourse;
    }
    return pCourse;
} 

bool checkExistStudentInCourse(CourseStudentList* listStudent, string studID){
    while(listStudent){
        //listStudent->toStudent = function returns the pointer to student in the list of studyclass
        if(listStudent->toStudent->dInfo.StudentID == studID) return true;
        listStudent = listStudent->nextStudent;
    }
    return false;
}
void updateCourseInformation(Semester* curSemester){

    string courseName, courseID, className;
    cout << "Enter the course name you want to add student: ";
    getline(cin, courseName);

    cout << "Enter the course ID you want to add student: ";
    getline(cin, courseID);

    cout << "Enter the class name of course you want to add student: ";
    getline(cin, className);

    Course* thisCourse = findTheCourse(curSemester->CourseList, courseName, courseID, className);

    if(thisCourse){
        while(true){

            cout << left << setw(15) << "Course ID" 
                 << left << setw(25) << "Course Name" 
                 << left << setw(15) << "Class Name"
                 << left << setw(25) << "Teacher"
                 << left << setw(3)  << "Credit"
                 << left << setw(4)  << "Max Students"   
                 << left << setw(3)  << "Day, Session" << endl;
             
            viewInfoOfCourse(thisCourse->infoThisCourse);
            
            cout << endl;
            cout << "The current course name is " << thisCourse->infoThisCourse.courseName << endl;
            cout << "The current course ID is " << thisCourse->infoThisCourse.courseID << endl;
            cout << "The current class name is " << thisCourse->infoThisCourse.className << endl;
            cout << "The teacher name is " << thisCourse->infoThisCourse.Teacher << endl;
            cout << "The number of credits is " << thisCourse->infoThisCourse.credit << endl;
            cout << "The maximum number of students in the course is " << thisCourse->infoThisCourse.maxStudent << endl;
            cout << "The day of week and the session that the course will be performed are " << thisCourse->infoThisCourse.CourseDate.day << ", "
                                                                                             << thisCourse->infoThisCourse.CourseDate.session << endl; 
            cout << "0.Update finish\n1.Course name\n2.Course ID\n3.Class name\n4.Credits\n5.Max Students\n6.Day and session\nEnter the choice number to edit: ";
            
            int choice; cin >> choice;
            cin.ignore();

            switch(choice){
                
                case 1: 
                    cout << "Enter the new course name: ";
                    getline(cin, thisCourse->infoThisCourse.courseName);
                    break;
                case 2:
                    cout << "Enter the new course ID: ";
                    getline(cin, thisCourse->infoThisCourse.courseID);
                    break;
                case 3:
                    cout << "Enter the new class name: ";
                    getline(cin, thisCourse->infoThisCourse.className);
                    break;
                case 4:
                    cout << "Enter the new credit: ";
                    do{
                        cin >> thisCourse->infoThisCourse.credit;
                        if(thisCourse->infoThisCourse.credit <= 0) cout << "The number of credits must > 0\n";
                    }while(thisCourse->infoThisCourse.credit <= 0);
                    cin.ignore();
                    break;
                case 5:
                    int numMaxStudents;
                    cout << "Enter the number of max students (must bigger than current): ";
                    do{
                        cin >> numMaxStudents;
                    } while(numMaxStudents < thisCourse->infoThisCourse.maxStudent);

                    thisCourse->infoThisCourse.maxStudent = numMaxStudents;
                    cin.ignore();
                    break;
                case 6:
                    cout << "< 2 or > 7. Go back"   << endl
                         << "2. Monday"    << endl
                         << "3. Tueday"    << endl
                         << "4. Wednesday" << endl
                         << "5. Thursday"  << endl
                         << "6. Friday"    << endl
                         << "7. Saturday"  << endl
                         << "Enter the selection of day of the week: ";

                         int day; cin >> day;

                         switch(day){
                            case 2: thisCourse->infoThisCourse.CourseDate.day = "MON"; break;
                            case 3: thisCourse->infoThisCourse.CourseDate.day = "TUE"; break;
                            case 4: thisCourse->infoThisCourse.CourseDate.day = "WED"; break;
                            case 5: thisCourse->infoThisCourse.CourseDate.day = "THU"; break;
                            case 6: thisCourse->infoThisCourse.CourseDate.day = "FRI"; break;
                            case 7: thisCourse->infoThisCourse.CourseDate.day = "SAT"; break;
                            default: break;
                         }

                    cout << "< 1 or > 4. Go back" << endl
                         << "1. S1 (07:30)" << endl
                         << "2. S2 (09:30)" << endl
                         << "3. S3 (13:30)" << endl
                         << "4. S4 (15:30)" << endl
                         << "Enter the selection of the session: ";
                         
                         int session; cin >> session;

                         switch(day){
                            case 1: thisCourse->infoThisCourse.CourseDate.session = "S1 (07:30)"; break;
                            case 2: thisCourse->infoThisCourse.CourseDate.session = "S2 (09:30)"; break;
                            case 3: thisCourse->infoThisCourse.CourseDate.session = "S3 (13:30)"; break;
                            case 4: thisCourse->infoThisCourse.CourseDate.session = "S4 (15:30)"; break;
                            default: break;
                         }
                         cin.ignore();
                    break;
                default: return;
            }
            cout << "\nThe new update course information\n";
        }
    }
    else cout << "This course doesn't exist.\n";
}

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

void addStudentToCourse(Semester* curSemester, StudyClass* pClass){
    string courseName, courseID, className;
    cout << "Enter the course name you want to add student: ";
    getline(cin, courseName);
    cout << "Enter the course ID you want to add student: ";
    getline(cin, courseID);
    cout << "Enter the class name of course you want to add student: ";
    getline(cin, className);

    Course* pCourse = findTheCourse(curSemester->CourseList, courseName, courseID, className);
    if(!pCourse) {
        cout << "This course doesn't exist!\n";
        return;
    }

    if(pCourse->numCurStudents >= pCourse->infoThisCourse.maxStudent ){
        cout << "The course is having maximum student!!! You cannot add student to this course.\n";
        return;
    }

    string studentName, studentID, nameStudyClass;
    cout << "Enter the student name you want to add: ";
    getline(cin, studentName);
    cout << "Enter the student ID you want to add: ";
    getline(cin, studentID);
    cout << "Enter the name of study class of student you want to add: ";
    getline(cin, nameStudyClass);
    if(checkExistStudentInCourse(pCourse->listStudent, studentID) == true){
        cout << "This student has existed in this course!\n";
        return;
    }

    CourseStudentList* newStudent = new CourseStudentList;
    if(/* !function to return index classstudy and studID of the pointer Student */1){
        delete newStudent;
        cout << "The student hasn't existed in system!!!\n";
        return;
    }
    newStudent->nextStudent = pCourse->listStudent;
    if(pCourse->listStudent){
        pCourse->listStudent->prevStudent = newStudent;
    }
    pCourse->listStudent = newStudent;

    // need the function to return the pointer to the student
    // pCourse->listStdent->toStudent = function

    cout << "Enter the no number of the student in this course: ";
    cin >> pCourse->listStudent->toStudent->No;
    EnrolledCourse* tmp = new EnrolledCourse;
    tmp->thisCourse = pCourse;
    tmp->nextCourse = pCourse->listStudent->toStudent->CourseList;
    if(pCourse->listStudent->toStudent->CourseList) {
        tmp->nextCourse->prevCourse = tmp;
    } 
    pCourse->listStudent->toStudent->CourseList = tmp;
}

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