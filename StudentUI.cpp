#include "header/ultilityfunction.h"
#include "header/displayfunction.h"
#include "header/datafunction.h"
#include "header/loginfunction.h"

//view info of student
void DisplayInfoStudent(Student* listStudent){
    cout << left << setw(15) << listStudent->dInfo.StudentID;
    cout << left << setw(25) << listStudent->dInfo.FirstName;
    cout << left << setw(15) << listStudent->dInfo.LastName;
    listStudent->dInfo.Gender[0] = toupper(listStudent->dInfo.Gender[0]);
    cout << left << setw(11) << listStudent->dInfo.Gender;
    DisplayBirth(listStudent->dInfo.Birth);
    cout << left << setw(25) << listStudent->dInfo.SocialID << endl;
}
//14. View a list of his/her courses. He/she will study these courses in this semester.
void DisplayCourseList1Student(Student* pStudent, int semester, string year){
    EnrolledCourse* firstCourse = pStudent->CourseList;
    while(firstCourse){
        if(firstCourse->ptoCourse->year == year && firstCourse->ptoCourse->semester == semester) break;
        firstCourse = firstCourse->nextCourse;
    }
    if(firstCourse == nullptr) cout << "Student hasn't enrroled course!!!\n";

    int i = 0;
    string temp;
    while(firstCourse->ptoCourse->year == year && firstCourse->ptoCourse->semester == semester){
        i++;
        // firstCourse->ptoCourse->courseIndex = i;
        cout << left << setw(10)  << i;//firstCourse->ptoCourse->courseIndex;
        cout << left << setw(15) << firstCourse->ptoCourse->thisCourseInfo.courseID;
        cout << left << setw(20) << firstCourse->ptoCourse->thisCourseInfo.courseName;
        cout << left << setw(10) << firstCourse->ptoCourse->thisCourseInfo.className;
        if (firstCourse->ptoCourse->numCurStudents == 0)
            temp = "0";
        else
            temp = firstCourse->ptoCourse->numCurStudents;
        temp += firstCourse->ptoCourse->numCurStudents;
        temp += '/';
        temp += to_string(firstCourse->ptoCourse->thisCourseInfo.maxStudent);
        cout << left << setw(20) << temp;
        temp = firstCourse->ptoCourse->thisCourseInfo.CourseDate.day;
        temp += ", ";
        temp += firstCourse->ptoCourse->thisCourseInfo.CourseDate.session;
        cout << left << setw(20) << temp;
        cout << left << setw(30) << firstCourse->ptoCourse->thisCourseInfo.Teacher << endl;
        firstCourse = firstCourse->nextCourse;
    }
}

//24. View his/her scoreboard
void DisplayScoreboard1Student(Student* pStudent, int semester, string year){
    EnrolledCourse* firstCourse = pStudent->CourseList;
    while(firstCourse){
        if(firstCourse->ptoCourse->year == year && firstCourse->ptoCourse->semester == semester) break;
        firstCourse = firstCourse->nextCourse;
    }
    if(firstCourse == nullptr) cout << "Student hasn't enrroled course!!!\n";
    int i = 0;
    cout << left << setw(5)  << "No";
    cout << left << setw(15) << "Course ID";
    cout << left << setw(30) << "Course Name";
    cout << left << setw(15) << "Class";
    cout << left << setw(12) << "Midterm";
    cout << left << setw(10) << "Final";
    cout << left << setw(10) << "Other";
    cout << left << setw(10) << "Total" << endl;
    cout << "--------------------------------------------------------------------" << endl;
    while(firstCourse->ptoCourse->year == year && firstCourse->ptoCourse->semester == semester){
        i++;
        cout << left << setw(5)  << i;
        cout << left << setw(15) << firstCourse->ptoCourse->thisCourseInfo.courseID;
        cout << left << setw(30) << firstCourse->ptoCourse->thisCourseInfo.courseName;
        cout << left << setw(18) << firstCourse->ptoCourse->thisCourseInfo.className;
        cout << left << setw(11) << firstCourse->Score->midtermMark;
        cout << left << setw(10) << firstCourse->Score->finalMark;
        cout << left << setw(10) << firstCourse->Score->otherMark;
        cout << left << setw(10) << firstCourse->Score->totalMark << endl;
        firstCourse = firstCourse->nextCourse;
    }

}

void StudentGUI(Student* curStudent, DataBase DB){
    int selection;
    while(true){
        system("cls");
        cout << "1. View profile info" << endl;
        cout << "2. Change password" << endl;
        cout << "3. View enrolled courses" << endl;
        cout << "4. View scoreboard" << endl;
        cout << "0. Back" << endl << endl;
        cout << ">> "; cin >> selection;

        switch(selection){
            case 0: return;
            case 1: 
                ChangePasswordStudent(curStudent);
                break;
            case 2:
                DisplayInfoStudent(curStudent);
                break;
            case 3:
                
                break;
            case 4:

                break;
        }
    }
}