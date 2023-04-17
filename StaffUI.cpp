#include "header/ultilityfunction.h"
#include "header/staffui.h"
#include "header/datafunction.h"
#include "header/displayfunction.h"
void CourseManager(DataBase &DB ,Course* curCourse, Semester* curSemester)
{
    int selection;
    do {
        system("cls");
        cout << "Year: " << curCourse->year << endl;
        cout << "Semester: " << curCourse->semester << endl;
        cout << "Course ID: " << curCourse->thisCourseInfo.courseID << endl;
        cout << "Course Name: " << curCourse->thisCourseInfo.courseName << endl;
        cout << "Class Name: " << curCourse->thisCourseInfo.className << endl;
        cout << "Number of Students: " << curCourse->numCurStudents  << '/' << curCourse->thisCourseInfo.maxStudent << endl;
        cout << "Course Date: " << curCourse->thisCourseInfo.CourseDate.day + ", " + curCourse->thisCourseInfo.CourseDate.session << endl;
        cout << "Teacher: " << curCourse->thisCourseInfo.Teacher << endl;
        cout << "Number of Credits: " << curCourse->thisCourseInfo.credit << endl;
        cout << endl;

        cout << "List of Students:" << endl;
        cout << left << setw(5) << "No";
        cout << left << setw(15) << "Student ID";
        cout << left << setw(40) << "Student Full Name";
        cout << left << setw(10) << "Midterm";
        cout << left << setw(10) << "Final";
        cout << left << setw(10) << "Other";
        cout << left << setw(10) << "Total";
        cout << endl;
        if (curCourse->listStudent == nullptr) {
            cout << "No students found" << endl;
        } else {
            DisplayCourseStudentList(curCourse->listStudent);
        }
        cout << endl;
        cout << "1. Add a Student" << endl;
        cout << "2. Remove a Student" << endl;
        cout << "3. Upload a CSV file of enrolled student" << endl;
        cout << "4. Update Course Information" << endl;
        cout << "5. Export students list to CSV file" << endl;
        cout << "6. Import students scores from CSV file" << endl;
        cout << "7. Update scores of a student" << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == 0)
            break;
        switch (selection)
        {
        case 1:
            if (curCourse->numCurStudents == curCourse->thisCourseInfo.maxStudent) {
                cout << "Maximum number of students in course exceeded" << endl;
                system("pause");
            } else {
                addStudentToCourse(curCourse,DB.YearList);
                SaveCourseStudentToFile(curCourse);
            } 
            
            break;
        case 2:
            removeStudentFromCourse(curCourse,DB.YearList);
            SaveCourseStudentToFile(curCourse);
            break;
        case 3:
            if (curCourse->numCurStudents == curCourse->thisCourseInfo.maxStudent) {
                cout << "Maximum number of students in course exceeded" << endl;
                system("pause");
            } else {
                UploadListofStud(curCourse,DB.YearList);
                SaveCourseStudentToFile(curCourse);
            } 
            break;
        case 4:
                UpdateCourseInfo(curCourse->thisCourseInfo);
                SaveCourseInfoToFile(curSemester);
            break;
        case 5:
                ExportCourseStudent(curCourse);
            break;
        case 6:
                importCourseScore(curCourse);
                SaveCourseStudentToFile(curCourse);
            break;
        case 7:
                ChangeStudentScore(curCourse->listStudent);
                SaveCourseStudentToFile(curCourse);
            break;
        default: break;
        }
    } while (true);
}
void SpecificSemesterManager(DataBase &DB, Semester* curSemester)
{
    if (curSemester == nullptr)
        return;
    int maxSelection;
    char selection;
    do {
        maxSelection = 0;
        system("cls");
        cout << "Current Year: " << curSemester->year << endl;
        cout << "Semester: " << curSemester->semester << endl;
        cout << "Start date: " << curSemester->start << endl;
        cout << "End date: " << curSemester->end << endl;
        cout << endl;
        cout << left << setw(10) << "Index";
        cout << left << setw(15) << "Course ID";
        cout << left << setw(20) << "Course Name";
        cout << left << setw(20) << "Class Name";
        cout << left << setw(25) << "Number of Students";
        cout << left << setw(20) << "Course Date";
        cout << left << setw(30) << "Teacher";
        cout << endl;
        if (curSemester->CourseList == nullptr)
        {
            cout << "No Courses found" << endl;

        } else {
            DisplayCourseList(curSemester->CourseList,maxSelection);
        }
        curSemester->numCourse = maxSelection;
        cout << endl;
        cout << "n. Add Course" << endl;
        cout << "x. Remove Course" << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == '0')
            break;
        if (selection == 'n' || selection == 'N') {
            NewCourse(curSemester->CourseList, curSemester->semester, curSemester->year);
            SaveCourseInfoToFile(curSemester);
            continue;
        }
            
        if (selection == 'x' || selection == 'X') {
            if (curSemester->CourseList == nullptr)
            {
                cout << "No Courses to remove now" << endl;
                system("pause");
            }
            removeCourse(curSemester);
            SaveCourseInfoToFile(curSemester);
            continue;
        }
            
        if (curSemester->CourseList != nullptr) {
            int intSelection = int(selection) - '0';
            if (intSelection > 0 && intSelection <= maxSelection) {
                Course* curCourse = navigateCourse(curSemester->CourseList,intSelection);
                CourseManager(DB,curCourse,curSemester);
            }
        }
    } while (true);
}
void SemestersListManager(DataBase &DB, string yearName)
{
    int maxSelection;
    char selection;
    Semester** handlingArr = nullptr;

    do {
        maxSelection = 0;
        system("cls");
        cout << "Current Year: " << yearName << endl;
        cout << left << setw(10) << "Index";
        cout << left << setw(10) << "Semester";
        cout << left << setw(10) << "Start";
        cout << left << setw(10) << "End";
        cout << endl;
        if (DisplaySemesterList(DB.SemesterList,handlingArr,yearName,maxSelection) == false)
        {
            cout << "No semesters found." << endl;
        }
        cout << endl;
        if (maxSelection < 3)
        {
            cout << "n. Add semester" << endl;
        } else {
            cout << "All 3 semesters of this year have been added" << endl;
        }
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == '0')
            break;
        if ( (maxSelection < 3) && (selection == 'n' || selection == 'N')) {
            InitSemester(DB.SemesterList,maxSelection+1,yearName);
            SaveSemesterToFile(DB.SemesterFile,DB.SemesterList);
        }
            
        else {
            int intSelection = int(selection) - '0';
            if (intSelection > 0 && intSelection <= 3)
            {

                SpecificSemesterManager(DB, handlingArr[intSelection-1]);
            }
        }
    } while (true);
    delete []handlingArr;
}

void StudyClassScoreBoardManager(StudyClass* curClass, string yearName, Semester** HandlingArr)
{
    if (HandlingArr[0] == nullptr) {
        cout << "No Semesters found for this year" << endl;
        delete []HandlingArr;
        system("pause");
        return;
    }

    int i = 0;
    char selection = '\0';
    bool nextStep;
    do {
        system("cls");
        cout << "Year: " << yearName << endl;
        cout << "Semester: " << i+1 << endl;
        
        DisplayScoreBoardUI(HandlingArr[i]->CourseList,nextStep);
        if (nextStep == true) {
            DisplayScoreBoard(curClass,HandlingArr[i]->CourseList,i);
            cout << endl;
        } else {    
            cout << endl;
        }
        if (i != 0) {
                cout << "z. Previous Semester" << endl;
            }
        if (!(i == 2 || HandlingArr[i+1] == nullptr)) {
                cout << "x. Next Semester" << endl;
        }
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == '0')
            break;
        if (selection == 'z' || selection == 'Z') {
            i--;
        }
        if (selection == 'x' || selection == 'X') {
            i++;
        }
    } while(true);
}
void StudyClassManager(StudyClass* curClass, string yearName, Semester* listSemester)
{
    Semester** HandlingArr = nullptr;
    calculateGPA(curClass,yearName,listSemester,HandlingArr);
    char selection;
    do {
        system("cls");
            cout << "Student Management" << endl;
            cout << endl; 
            cout << "Year: " << yearName << endl;
            cout << "Class: " << curClass->className << endl;
            cout << endl;
            cout << left << setw(5) << "No";
            cout << left << setw(15) << "Student ID";
            cout << left << setw(25) << "First Name";
            cout << left << setw(15) << "Last Name";
            cout << left << setw(11) << "Gender";
            cout << left << setw(19) << "Date of Birth";
            cout << left << setw(25) << "Social ID";
            cout << left << setw(15) << "Overall GPA" << endl;
            if (curClass->listStudent == nullptr) {
                cout << "No students found" << endl;
                cout << endl;
                cout << "n. Add student" << endl;
            } else {
                DisplayStudentList(curClass->listStudent);
                cout << endl;
                cout << "s. View Scoreboard" << endl;
            }
            cout << "0. Back" << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == '0')
                break;
            if ((curClass->listStudent == nullptr) && (selection == 'n' || selection == 'N')) {
                AddStudent(curClass->listStudent,yearName,curClass->className,curClass->numStudent);
                SaveStudentListToFile(curClass->className,curClass->listStudent);
            }
            if (selection == 's' || selection == 'S') {
                StudyClassScoreBoardManager(curClass,yearName,HandlingArr);
            }
    } while (true);
    Student* curStudent = curClass->listStudent;
    while (curStudent != nullptr) {
        delete []curStudent->GPA;
        curStudent->GPA = nullptr;
        curStudent = curStudent->nextStudent;
    }
    delete []HandlingArr;
}
void ClassesManager(Schoolyear* curYear, Semester* listSemester)
{
    char selection;
    int maxSelection;
    StudyClass* chosenClass = nullptr;
    do {
        maxSelection = 0;
        system("cls");
        cout << "Classes Management" << endl;
        cout << endl;
        cout << "Year: " << curYear->year << endl;
        cout << endl;
        cout << "List of classes: " << endl;
        if (curYear->listClass == nullptr) {
            cout << "No classes found" << endl;
            cout << endl;
            cout << "n. New class" << endl;
        } else {
            DisplayClassList(curYear->listClass,maxSelection);
            cout << endl;
        }
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == '0')
            break;
        else if (selection == 'n' || selection == 'N') {
            AddClass(curYear->listClass);
            SaveClassToFile(curYear->year,curYear->listClass);
        }
        else if (curYear->listClass != nullptr) {
            int intSelection = int(selection) - '0';
            if (intSelection > 0 && intSelection <= maxSelection) {
                chosenClass = navigateClass(curYear->listClass, intSelection);
                StudyClassManager(chosenClass, curYear->year, listSemester);
            }
        }
    } while (true);
}
void SchoolYearManager(DataBase &DB, Schoolyear* curYear)
{
    int selection;
    do {
        system("cls");
        cout << "Current Year: " << curYear->year << endl;
        cout << "1. Classes management" << endl;
        cout << "2. Semesters management" << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == 0)
            break;
        if (selection == 1) {
            ClassesManager(curYear,DB.SemesterList);
        }
            
        if (selection == 2)
        {
            QuickPtrBinder(DB);
            LoadSemesterSector(DB);
            SemestersListManager(DB,curYear->year);
        }
    } while (true);
    
}

void StaffUI(DataBase &DB)
{   
    int maxSelection;
    Schoolyear* chosenYear = nullptr;
    char selection;
    do {
        maxSelection = 0;
        system("cls");
        cout << "List of years:" << endl;
        if (DB.YearList == nullptr) {
            cout << "No school years found" << endl;
        } else {
            DisplayYearList(DB.YearList,maxSelection);
        }
        cout << endl;
        cout << "n. Add a new year" << endl;
        cout << "0. Back" << endl;
        cout << endl << ">> ";
        cin >> selection;
        if (selection == 'n' || selection == 'N') {
            AddYear(DB);
            SaveYearToFile(DB.YearFile,DB.YearList);
            continue;
        }
        if (selection == '0')
            break;
        if (DB.YearList != nullptr) {
            int intSelection = int(selection) - '0';
            if (intSelection > 0 && intSelection <= maxSelection) {
                chosenYear = navigateYear(DB.YearList,intSelection);
                SchoolYearManager(DB,chosenYear);
            }
        }
    } while (true);
}