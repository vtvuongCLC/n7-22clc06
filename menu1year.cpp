#include "header/findObject.h"

void menu1Year(DataBase* DB){
    DB = new DataBase;
    int numSemester = 1;
    cout << "There are 3 semesters in a school year: Semester 1 (Fall), Semester 2 (Summer), and Semester 3 (Autumn)." << endl;
    while(numSemester != 4){
        InitSemester(DB->SemesterList, numSemester, DB->YearList->year);
        bool checkEndSemester = false;
        while(!checkEndSemester){
            system("cls");
            cout << "Menu At The Beginning Of The Semester" 
                                     << numSemester << endl
                 << "1.Add New Course"              << endl 
                 << "2.Upload File List Of Student" << endl
                 << "3.Add A student"               << endl 
                 << "4.View The List Of Courses"    << endl 
                 << "5.Update Course Information"   << endl
                 << "6.Remove A Student"            << endl
                 << "7.Delete A Course"             << endl
                 << "8.Display List"                << endl
                 << "9.To End Semester"             << endl;
            int selection;
            cout << "Enter a selection: "; cin >> selection;
            cin.ignore();
            switch(selection){
                case 1:
                    EnterCourseData(DB->SemesterList->CourseList);
                    break;
                case 2:
                    //UploadListofStud();
                    break;
                case 3:
                    addStudentToCourse(DB->SemesterList, DB->YearList);
                    break;
                case 4:
                    viewListOfCoursesIn1Semester(DB->SemesterList);
                    break;
                case 5:
                    updateCourseInformation(DB->SemesterList);
                    break;
                case 6:
                    removeStudentFromCourse(DB->SemesterList, DB->YearList);
                    break;
                case 7:
                    removeCourse(DB->SemesterList);
                    break;
                case 8:
                    // menuDisplay(DataBase* DB);
                    break;
                case 9:
                    //menuScoreBoard
                    checkEndSemester = true;
                    break;
                default: 
                    cout << "The selection must be from 1 to 9" << endl;
                    break;
            }
            system("pause");
        }
        // TO THE END OF SEMESTER
        
        numSemester++;
    }
}

