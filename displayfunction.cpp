#include "header/ultilityfunction.h"
#include "header/displayfunction.h"
#include "header/semesterAndCourse.h"
#include "header/datafunction.h"

// Semester* navigateSemester(Semester* listSemester, int userindex)
// {
//     if (listSemester == nullptr)
//         return nullptr;
//     int i = 0;
//     while (listSemester != nullptr)
//     {
//         i++;
//         if (i == userindex)
//             return listSemester;
//         listSemester = listSemester->nextSemester;
//     }
// }

void DisplayBirth(BirthDate InputBirth)
{
    int offset = 0;
    if (InputBirth.day / 10 == 0) {
        offset += 1;
    }
    if (InputBirth.month / 10 == 0) {
        offset += 1;
    }
    cout << left << InputBirth.day << '/';
    cout << left << InputBirth.month << '/';
    cout << left << setw(13+offset) << InputBirth.year;
} 
void DisplayStudentList(Student* listStudent)
{
    while (listStudent != nullptr) {
        cout << left << setw(5) << listStudent->No;
        cout << left << setw(15) << listStudent->dInfo.StudentID;
        cout << left << setw(25) << listStudent->dInfo.FirstName;
        cout << left << setw(15) << listStudent->dInfo.LastName;
        listStudent->dInfo.Gender[0] = toupper(listStudent->dInfo.Gender[0]);
        cout << left << setw(11) << listStudent->dInfo.Gender;
        DisplayBirth(listStudent->dInfo.Birth);
        cout << left << setw(25) << listStudent->dInfo.SocialID << endl;
        listStudent = listStudent->nextStudent;
    }
}
void DisplayClassList(StudyClass* listClass, int &max)
{
    int i = 0;
    while (listClass != nullptr) {
        i++;
        cout << i << ". " << listClass->className << endl;
        listClass = listClass->nextClass;
    }
    max = i;
}
void DisplayYearList(Schoolyear* listYear, int &max)
{
    int i = 0;
    while (listYear != nullptr) {
        i++;
        listYear->index = i;
        cout << i << ". " << listYear->year << endl;
        listYear = listYear->nextYear;
    }
    max = i;
}

// void DisplaySemester(Semester* SemesterList, Schoolyear* curYear, int &max)
// {
//     if (SemesterList == nullptr)
//         max = 0;
//     cout << left << setw(5) << "Index";
//     cout << left << setw(10) << "Semester";
//     cout << left << setw(10) << "Start";
//     cout << left << setw(10) << "End";
//     cout << endl;
//     int i = 0;
//     while (SemesterList != nullptr) {
//         if (SemesterList->year == curYear->year) {
//             i++;
//             SemesterList->index = i;
//             cout << left << setw(5) << SemesterList->index;
//             cout << left << setw(10) << SemesterList->semester;
//             cout << left << setw(10) << SemesterList->start;
//             cout << left << setw(10) << SemesterList->end;
//             cout << endl;
//         }
//         SemesterList = SemesterList->nextSemester; 
//     }
// }

// void SemesterManager(DataBase DB, Schoolyear* curYear)
// {
//     int selection;
//     int maxSelection;
//     do {
//         DisplaySemester(DB.SemesterList, curYear, maxSelection);
//         cout << "0. Back" << endl;
//         cout << endl;
//         cout << ">> ";
//         cin >> selection;
//         if (selection == 0)
//             break; 
//     } while (true);
// }

void StudyClassManager(StudyClass* curClass, string yearName)
{
    string selection;
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
            cout << left << setw(25) << "Social ID" << endl;
            if (curClass->listStudent == nullptr) {
                cout << "No students found" << endl;
                cout << endl;
                cout << "n. Add student" << endl;
            } else {
                DisplayStudentList(curClass->listStudent);
                cout << endl;
            }
            cout << "0. Back" << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == "0")
                break;
            if (selection == "n" || selection == "N")
                AddStudent(curClass->listStudent,yearName,curClass->className,curClass->numStudent);
    } while (true);
}
void ClassesManager(Schoolyear* curYear)
{
    string selection;
    int maxSelection;
    StudyClass* chosenClass = nullptr;
    do {
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
            maxSelection = 0;
        } else {
            DisplayClassList(curYear->listClass,maxSelection);
            cout << endl;
        }
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == "0")
            break;
        else if (selection == "n" || selection == "N") {
            AddClass(curYear->listClass);
        }
        else if (curYear->listClass != nullptr) {
            int intSelection = stoi(selection);
            if (intSelection > 0 && intSelection <= maxSelection) {
                chosenClass = navigateClass(curYear->listClass,stoi(selection));
                StudyClassManager(chosenClass, curYear->year);
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
        if (selection == 1)
            ClassesManager(curYear);
        if (selection == 2)
        {
            QuickPtrBinder(DB);
            LoadSemesterSector(DB);
            //SemesterManager(DB,curYear);
        }
    } while (true);
}

void StaffGUI(DataBase &DB)
{   
    int maxSelection;
    Schoolyear* chosenYear = nullptr;
    string selection;
    do {
        system("cls");
        cout << "List of years:" << endl;
        if (DB.YearList == nullptr) {
            cout << "No school years found" << endl;
            maxSelection = 0;
        } else {
            DisplayYearList(DB.YearList,maxSelection);
        }
        cout << endl;
        cout << "n. Add a new year" << endl;
        cout << "0. Back" << endl;
        cout << endl << ">> ";
        cin >> selection;
        if (selection == "n" || selection == "N") {
            AddYear(DB);
            continue;
        }
        if (selection == "0")
            break;
        if (DB.YearList != nullptr) {
            int intselection = stoi(selection);
            if (intselection > 0 && intselection <= maxSelection) {
                chosenYear = navigateYear(DB.YearList,intselection);
                SchoolYearManager(DB,chosenYear);
            }
        }
    } while (true);
}