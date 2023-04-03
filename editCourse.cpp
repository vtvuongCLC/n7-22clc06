#include "header/findObject.h"

void viewInfoOfCourse(CourseInfo infoThisCourse){

    cout << " " << left << setw(15) << infoThisCourse.courseID 
                << left << setw(20) << infoThisCourse.courseName 
                << left << setw(15) << infoThisCourse.className
                << left << setw(25) << infoThisCourse.Teacher
                << left << setw(3)  << infoThisCourse.credit
                << left << setw(4)  << infoThisCourse.maxStudent  
                << left << setw(3)  << infoThisCourse.CourseDate.day
                            << ", " << infoThisCourse.CourseDate.session << endl;                                 
}

void viewListOfCoursesIn1Semester(Semester* curSemester){
    system("cls"); 
    Course* pCourse = curSemester->CourseList;
    if(!pCourse){
        cout << "This semester hasn't yet been added course!!! First, please add the course to this semester";
        return;
    }
    cout << "The courses list in semester " << curSemester->semester << " year " << curSemester->year << endl << endl;
    while(pCourse){
        cout << "----------------------------------------------------------------------\n";
        cout << "The courses list of semester " << curSemester->semester << " year " << curSemester->year << endl;
        cout << left << setw(15) << "Course ID" 
             << left << setw(25) << "Course Name" 
             << left << setw(15) << "Class Name"
             << left << setw(25) << "Teacher"
             << left << setw(3)  << "Credit"
             << left << setw(4)  << "Max Students"  
             << left << setw(3)  << "Day, Session" 
             << left << setw(4)  << "Number Current Students" << endl;

        viewInfoOfCourse(pCourse->thisCourseInfo);
        cout << left << setw(4)  << pCourse->numCurStudents;
        pCourse = pCourse->nextCourse;
    }
}

void viewAllListOfCourses(Semester* curSemester){
    while(curSemester){

        while(curSemester){
            Course* pCourse = curSemester->CourseList;
            if(!pCourse){
                cout << "This semester hasn't yet been added course!!! First, please add the course to this semester";
                return;
            }
            cout << "The courses list in semester " << curSemester->semester << " year " << curSemester->year << endl << endl;
            while(pCourse){
                cout << "----------------------------------------------------------------------\n";
                cout << "The courses list of semester " << curSemester->semester << " year " << curSemester->year << endl;
                cout << left << setw(15) << "Course ID" 
                     << left << setw(25) << "Course Name" 
                     << left << setw(15) << "Class Name"
                     << left << setw(25) << "Teacher"
                     << left << setw(3)  << "Credit"
                     << left << setw(4)  << "Max Students"  
                     << left << setw(3)  << "Day, Session" << endl;
                viewInfoOfCourse(pCourse->thisCourseInfo);
                pCourse = pCourse->nextCourse;
            }
        }
    }
}

Course* findTheCourse(Semester* pSemester, string year, string semester, string NameCourse, string IDCourse, string NameClass){
    while(pSemester){
        if(pSemester->year == year && pSemester->semester == semester) break;
        pSemester = pSemester->nextSemester;
    }
    if(pSemester == nullptr) return nullptr;

    Course* pCourse = pSemester->CourseList;
    while(pCourse){
        if(NameCourse  == pCourse->thisCourseInfo.courseName 
          && IDCourse  == pCourse->thisCourseInfo.courseID 
          && NameClass == pCourse->thisCourseInfo.className) 
        break;
        pCourse = pCourse->nextCourse;
    }
    return pCourse;
} 

void updateCourseInformation(Semester* curSemester){

    string courseName, courseID, className;
    cout << "Enter the course name you want to add student: ";
    getline(cin, courseName);

    cout << "Enter the course ID you want to add student: ";
    getline(cin, courseID);

    cout << "Enter the class name of course you want to add student: ";
    getline(cin, className);

    Course* thisCourse = findTheCourse(curSemester, curSemester->year, curSemester->semester, courseName, courseID, className);

    if(thisCourse){
        while(true){

            cout << left << setw(15) << "Course ID" 
                 << left << setw(25) << "Course Name" 
                 << left << setw(15) << "Class Name"
                 << left << setw(25) << "Teacher"
                 << left << setw(3)  << "Credit"
                 << left << setw(4)  << "Max Students"   
                 << left << setw(3)  << "Day, Session" << endl;
             
            viewInfoOfCourse(thisCourse->thisCourseInfo);
            
            cout << endl;
            cout << "The current course name is " << thisCourse->thisCourseInfo.courseName << endl;
            cout << "The current course ID is " << thisCourse->thisCourseInfo.courseID << endl;
            cout << "The current class name is " << thisCourse->thisCourseInfo.className << endl;
            cout << "The teacher name is " << thisCourse->thisCourseInfo.Teacher << endl;
            cout << "The number of credits is " << thisCourse->thisCourseInfo.credit << endl;
            cout << "The maximum number of students in the course is " << thisCourse->thisCourseInfo.maxStudent << endl;
            cout << "The day of week and the session that the course will be performed are " << thisCourse->thisCourseInfo.CourseDate.day << ", "
                                                                                             << thisCourse->thisCourseInfo.CourseDate.session << endl; 
            cout << "0.Update finish\n1.Course name\n2.Course ID\n3.Class name\n4.Credits\n5.Max Students\n6.Day and session\nEnter the choice number to edit: ";
            
            int choice; cin >> choice;
            cin.ignore();

            switch(choice){
                
                case 1: 
                    cout << "Enter the new course name: ";
                    getline(cin, thisCourse->thisCourseInfo.courseName);
                    break;

                case 2:
                    cout << "Enter the new course ID: ";
                    getline(cin, thisCourse->thisCourseInfo.courseID);
                    break;

                case 3:
                    cout << "Enter the new class name: ";
                    getline(cin, thisCourse->thisCourseInfo.className);
                    break;

                case 4:
                    cout << "Enter the new credit: ";
                    do{
                        cin >> thisCourse->thisCourseInfo.credit;
                        if(thisCourse->thisCourseInfo.credit <= 0) cout << "The number of credits must > 0\n";
                    }while(thisCourse->thisCourseInfo.credit <= 0);
                    cin.ignore();
                    break;

                case 5:
                    int numMaxStudents;
                    cout << "Enter the number of max students (must bigger than current): ";
                    do{
                        cin >> numMaxStudents;
                    } while(numMaxStudents < thisCourse->thisCourseInfo.maxStudent);

                    thisCourse->thisCourseInfo.maxStudent = numMaxStudents;
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
                            case 2: thisCourse->thisCourseInfo.CourseDate.day = "MON"; break;
                            case 3: thisCourse->thisCourseInfo.CourseDate.day = "TUE"; break;
                            case 4: thisCourse->thisCourseInfo.CourseDate.day = "WED"; break;
                            case 5: thisCourse->thisCourseInfo.CourseDate.day = "THU"; break;
                            case 6: thisCourse->thisCourseInfo.CourseDate.day = "FRI"; break;
                            case 7: thisCourse->thisCourseInfo.CourseDate.day = "SAT"; break;
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
                            case 1: thisCourse->thisCourseInfo.CourseDate.session = "S1 (07:30)"; break;
                            case 2: thisCourse->thisCourseInfo.CourseDate.session = "S2 (09:30)"; break;
                            case 3: thisCourse->thisCourseInfo.CourseDate.session = "S3 (13:30)"; break;
                            case 4: thisCourse->thisCourseInfo.CourseDate.session = "S4 (15:30)"; break;
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

CourseStudent* findStudentInCourse(CourseStudent* listStudent, string studID){
    while(listStudent){
        if(listStudent->ptoStudent->dInfo.StudentID == studID) break;
        listStudent = listStudent->nextStudent;
    }
    return listStudent;
}

void LinkEnrolledCourseToCourse(Student *curStudent, Course *curCourse)
{
    EnrolledCourse* temp = curStudent->CourseList;
    curStudent->CourseList = new EnrolledCourse;
    curStudent->CourseList->nextCourse = temp;
    if(temp) temp->prevCourse = curStudent->CourseList;
    curStudent->CourseList->ptoCourse = curCourse;
}

bool FindStudentIndexInStudyClass(Schoolyear* curYear, CourseStudent* newStudent, string year, string className, string StudID,Course* curCourse){
    while(curYear){
        if(curYear->year == year) break;
        curYear = curYear->nextYear;
    }
    if(!curYear) {
        cout << "This year hasn't existed in system!!!\n";
        return false;
    }
    StudyClass* pClass = curYear->listClass;
    int idxClass = 0;
    while(pClass){
        if(pClass->className == className) break;
        idxClass++;
        pClass = pClass->nextClass;
    }
    if(!pClass){
        cout << "This study class hasn't existed in system!!!\n";
        return false;
    }
    Student* pStudent = pClass->listStudent;
    int idxStudent = 0;
    while(pStudent){
        if(pStudent->dInfo.StudentID == StudID) break;
        idxStudent++;
        pStudent = pStudent->nextStudent;
    }
    if(!pStudent){
        cout << "This student hasn't existed in system!!!\n";
        return false;
    }

    newStudent->studentIndex = idxStudent;
    newStudent->classIndex = idxClass;
    newStudent->ptoStudent = pStudent;
    LinkEnrolledCourseToCourse(newStudent->ptoStudent, curCourse);
    return true;
}

void addStudentToCourse(Semester* curSemester, Schoolyear* curYear){
    string courseName, courseID, className;
    cout << "Enter the course name you want to add student: ";
    getline(cin, courseName);
    cout << "Enter the course ID you want to add student: ";
    getline(cin, courseID);
    cout << "Enter the class name of course you want to add student: ";
    getline(cin, className);

    Course* pCourse = findTheCourse(curSemester, curSemester->year, curSemester->semester, courseName, courseID, className);
    if(!pCourse) {
        cout << "This course doesn't exist!\n";
        return;
    }

    if(pCourse->numCurStudents >= pCourse->thisCourseInfo.maxStudent ){
        cout << "The course is having maximum student!!! You cannot add student to this course.\n";
        return;
    }
    int numYears;
    string studentName, studentID, nameStudyClass, year;
    DisplayYearList(curYear, numYears);

    cout << "Enter the year number when a student start in system: ";
    getline(cin, year);
    cout << "Enter the student name you want to add: ";
    getline(cin, studentName);
    cout << "Enter the student ID you want to add: ";
    getline(cin, studentID);
    cout << "Enter the name of study class of student you want to add: ";
    getline(cin, nameStudyClass);

    CourseStudent* newStudent = findStudentInCourse(pCourse->listStudent, studentID);
        
    if(newStudent != nullptr){
        cout << "This student has enrolled to this course!\n";
        return;
    }
    newStudent = new CourseStudent;
    if(!FindStudentIndexInStudyClass(curYear, newStudent, year ,nameStudyClass, studentID, pCourse)){
        delete newStudent;
        return;
    }

    cout << "Enter the no number of the student in this course: ";
    cin >> newStudent->no;
    cin.ignore();
    newStudent->nextStudent = pCourse->listStudent;
    if(pCourse->listStudent){
        pCourse->listStudent-> prevStudent= newStudent;
    }
    pCourse->listStudent = newStudent;
    pCourse->numCurStudents++;
}

// void displayStudentInCourse(Course* thisCourse){
//     cout << "==========================================================================\nThe list student in this course\n";
//     CourseStudentList* firstStudent = thisCourse->listStudent;
//     while(firstStudent){
//         cout << left << setw(5)  << firstStudent->no
//              << left << setw(10) << firstStudent->toStudent->dInfo.StudentID
//              << left << setw(15) << firstStudent->toStudent->dInfo.LastName
//              << left << setw(10) << firstStudent->toStudent->dInfo.FirstName 
//              << left << setw(15) << firstStudent->toStudent->dInfo.SocialID
//              << left << setw(15) << firstStudent->toStudent->dInfo.Gender
//              << firstStudent->toStudent->dInfo.Birth.day << "/"
//              << firstStudent->toStudent->dInfo.Birth.month << "/"
//              << firstStudent->toStudent->dInfo.Birth.year << endl;
//         firstStudent = firstStudent->nextStudent;
//     }
// }

// void removeEnrollCourse(Student* removedStudent, Course* pCourse){
//     EnrolledCourse* tmp = removedStudent->CourseList;
//     while(tmp){
//         if(tmp->thisCourse == pCourse) break;
//         tmp = tmp->nextCourse;
//     }
//     if(tmp->prevCourse){
//        tmp->prevCourse->nextCourse = tmp->nextCourse;
//        tmp->nextCourse->prevCourse = tmp->prevCourse; 
//     }
//     else {
//         removedStudent->CourseList = tmp->nextCourse;
//         removedStudent->CourseList->prevCourse = nullptr;
//     }
//     delete tmp;

// }
// void removeStudentFromCourse(Semester* curSemester, Schoolyear* curYear){
//     string courseName, courseID, className;
//     cout << "Enter the course name you want to remove a student: ";
//     getline(cin, courseName);
//     cout << "Enter the course ID you want to remove a student: ";
//     getline(cin, courseID);
//     cout << "Enter the class name of course you want to add student: ";
//     getline(cin, className);

//     Course* pCourse = findTheCourse(curSemester->CourseList, courseName, courseID, className);
//     if(!pCourse) {
//         cout << "This course doesn't exist!\n";
//         return;
//     }

//     displayStudentInCourse(pCourse);

//     string studentName, studentID, nameStudyClass;
//     cout << "Enter the student name you want to remove: ";
//     getline(cin, studentName);
//     cout << "Enter the student ID you want to remove: ";
//     getline(cin, studentID);

//     CourseStudentList* removedStudent = findStudentInCourse(pCourse->listStudent, studentID);

//     if(removedStudent == nullptr){
//         cout << "The student hasn't enrolled to this course\n";
//         return;
//     }

//     removeEnrollCourse(removedStudent->toStudent, pCourse);
    
//     if(removedStudent->prevStudent){
//         removedStudent->prevStudent->nextStudent = removedStudent->nextStudent;
//         removedStudent->nextStudent->prevStudent = removedStudent->prevStudent;
//     }
//     else {
//         pCourse->listStudent = removedStudent->nextStudent;
//         pCourse->listStudent->prevStudent = nullptr;
//     }
//     delete removedStudent;
// }

// void printListCoursesOfAStudent(Student* thisStudent, int semesterIndex){
//     EnrolledCourse* firstCourse = thisStudent->CourseList;
//     cout << "The list of Courses you will study in this semester\n";
//     while(firstCourse){
//         if(firstCourse->thisCourse->semesterIdx == semesterIndex)
//         viewInfoOfCourse(firstCourse->thisCourse->infoThisCourse);
//         firstCourse = firstCourse->nextCourse;
//     }

// }
// void removeCourse(Semester* curSemester){
//     string courseName, courseID, className;
//     cout << "Enter the course name you want to remove a student: ";
//     getline(cin, courseName);
//     cout << "Enter the course ID you want to remove a student: ";
//     getline(cin, courseID);
//     cout << "Enter the class name of course you want to add student: ";
//     getline(cin, className);

//     Course* pCourse = findTheCourse(curSemester->CourseList, courseName, courseID, className);
//     if(!pCourse) {
//         cout << "This course doesn't exist!\n";
//         return;
//     }

//     if(pCourse == curSemester->CourseList){
//         curSemester->CourseList = curSemester->CourseList->nextCourse;
//         curSemester->CourseList->prevCourse = nullptr;
//     }
//     else {
//         pCourse->prevCourse->nextCourse = pCourse->nextCourse;
//         pCourse->nextCourse->prevCourse = pCourse->prevCourse;
//     }

//     while(pCourse->listStudent){
//         CourseStudentList* tmp = pCourse->listStudent;
//         pCourse->listStudent = pCourse->listStudent->nextStudent;
//         removeEnrollCourse(tmp->toStudent, pCourse);
//         delete tmp;
//     }

//     delete pCourse;
//     cout << "The program removed this course.\n";
// }