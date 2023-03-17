#include "header.h"

void viewListCourses(Semester* curSemester){ 
    Course* pCourse = curSemester->Courselist;
    if(!pCourse){
        cout << "This semester hasn't yet been added course!!! First, please add the course to this semester";
        return;
    }
    cout << "The list of courses in semester " << curSemester->semesterIndex << endl;
    while(pCourse != nullptr){
        cout << pCourse->courseID << " " << 
                pCourse->courseName << " " << 
                pCourse->className << " " << 
                pCourse->Teacher << " " << 
                pCourse->credit << " " << 
                pCourse->maxStudent << " " << 
                pCourse->CourseDate.day << ", " << 
                pCourse->CourseDate.session << endl;
        pCourse = pCourse->nextCourse;
    }
}

Course* findTheCourse(Course* thisCourse, string nameCourse){
    while(thisCourse != nullptr){
        if(nameCourse == thisCourse->courseName) break;
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

