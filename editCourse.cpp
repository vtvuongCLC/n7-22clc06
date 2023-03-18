#include "findObject.h"

void viewListCourses(Semester* curSemester){ 
    Course* pCourse = curSemester->Courselist;
    if(!pCourse){
        cout << "This semester hasn't yet been added course!!! First, please add the course to this semester";
        return;
    }
    cout << "The list of courses in semester " << curSemester->semesterIndex << endl;
    while(pCourse != nullptr){

        cout << pCourse->courseID << " " 
             << pCourse->courseName << " " 
             << pCourse->className << " " 
             << pCourse->Teacher << " " 
             << pCourse->credit << " " 
             << pCourse->maxStudent << " " 
             << pCourse->CourseDate.day << ", " 
             << pCourse->CourseDate.session << endl;

        pCourse = pCourse->nextCourse;
    }
}

Course* findTheCourse(Course* thisCourse, string NameCourse, string IDCourse, string NameClass){
    while(thisCourse != nullptr){
        if(NameCourse == thisCourse->courseName 
            && IDCourse == thisCourse->courseID 
            && NameClass == thisCourse->className) 
        break;
        thisCourse = thisCourse->nextCourse;
    }
    return thisCourse;
} 

void updateCourseInformation(Semester* curSemester){
    string nameCourse;
    cout << "Please enter the course name you want to update: ";
    getline(cin, nameCourse);

    Course* thisCourse = findTheCourse(curSemester->Courselist, nameCourse);

    if(thisCourse){
        while(true){
            int choice;
            cout << "The current course ID is " << thisCourse->courseID << endl;
            cout << "The current class name is " << thisCourse->className << endl;
            cout << "The teacher name is " << thisCourse->Teacher << endl;
            cout << "The number of credits is " << thisCourse->credit << endl;
            // cout << "The maximum number of students in the course is " << thisCourse->maxStudent << endl;
            cout << "The day of week and the session that the course will be performed are " << thisCourse->CourseDate.day << ", " << thisCourse->CourseDate.session << endl;
            cout << "0.Update finish\n1.Course name\n2.Course ID\n3.Class name\n4.Credits\n5.Day and session\nEnter the choice number to edit: ";
            cin >> choice;
            switch(choice){
                case 0: return;
                case 1: 
                    getline(cin, thisCourse->courseName);
                    break;
                case 2:
                    getline(cin, thisCourse->courseID);
                    break;
                case 3:
                    getline(cin, thisCourse->className);
                    break;
                case 4:
                    do{
                        cin >> thisCourse->credit;
                        if(thisCourse->credit <= 0) cout << "The number of credits must > 0\n";
                    }while(thisCourse->credit <= 0);
                    break;
                case 5:
                    getline(cin, thisCourse->CourseDate.day);
                    getline(cin, thisCourse->CourseDate.session);
                    break;
            }
        }
    }
    else cout << "This course isn't exist.\n";
}

SchoolYear* findSchoolYear(SchoolYear* yearHead, int year){
    while(yearHead){
        if(yearHead->yearStart == year) break;
        yearHead = yearHead->prevYear;
    }
    return yearHead;
}

StudyClass* findStudyClass(StudyClass* classHead, string className){
    while(classHead){
        if(classHead->nameStudyClass == className) break;
        classHead = classHead->nextClass;
    }
    return classHead;
}

Student* findStudent(Student* studentHead, string IDStudent){
    while(studentHead){
        if(studentHead->This_Student.StudentID == IDStudent) break;
        studentHead = studentHead->nextStudent;
    }
    return studentHead;
}


void exportListStudentsInCourse(Course thisCourse){
    ofstream ofs;
    ofs.open(thisCourse.courseName + '-' + thisCourse.courseID + '-' + thisCourse.className);
    while(thisCourse.thisCourseScore){
        ofs << thisCourse.thisCourseScore->No << "," 
            << thisCourse.thisCourseScore->StudentID << "," 
            << thisCourse.thisCourseScore->StudentName << "," 
            << thisCourse.thisCourseScore->Midterm << "," 
            << thisCourse.thisCourseScore->OtherMark << "," 
            << thisCourse.thisCourseScore->Final << endl;
        thisCourse.thisCourseScore = thisCourse.thisCourseScore->nextBoard;
    }
    ofs.close();
}
int countStudentIn1Course(Course* thisCourse){
    int countStudent = 0;
    while(thisCourse->thisCourseScore){
        thisCourse->thisCourseScore = thisCourse->thisCourseScore->nextBoard;
        countStudent++;
    }
    return countStudent;
}
void addStudentToCourse(Semester* curSemester){
    string courseName, courseID, className;
    cout << "Enter the course name you want to add student: ";
    getline(cin, courseName);
    cout << "Enter the course ID you want to add student: ";
    getline(cin, courseID);
    cout << "Enter the class name of course you want to add student: ";
    getline(cin, className);

    Course* thisCourse = findTheCourse(curSemester->Courselist, courseName, courseID, className);
    int numStudent = countStudentIn1Course(thisCourse);

    if(numStudent >= thisCourse->maxStudent){
        cout << "The course is having maximum student!!! You cannot add student to this course.\n";
        return;
    }

    // còn phần check xem student có tồn tại hay không
    string studentName, studentID; 
    int no;
    cout << "Enter the student name you want to add: ";
    getline(cin, studentName);
    cout << "Enter the student ID you want to add: ";
    getline(cin, studentID);
    cout << "Enter the number of No you want to add: ";
    cin >> no;

    Scoreboard* tmp = new Scoreboard;
    tmp->nextBoard = thisCourse->thisCourseScore->nextBoard;
    tmp->No = no;
    tmp->StudentID = studentID;
    tmp->StudentName = studentName;
    thisCourse->thisCourseScore = tmp;
}