#include <iostream>
#include <iomanip>
#include "datafunction.h"
#include "displayfunction.h"
using namespace std;

void DisplayYearList(Schoolyear* listYear, int &max)
{
    int i = 0;
    while (listYear != nullptr) {
        i += 1;
        cout << i << ". " << listYear->year << endl;
        listYear = listYear->nextYear;
    }
    max = i;
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

void StudyClassManage(StudyClass* InputClass, string yearName)
{
    int selection;
    if (InputClass->listStudent == nullptr) {
        system("cls");
        cout << "No student data available" <<endl;
        cout << "Add student ? (1 to proceed | 0 to cancel)" << endl;
        cin >> selection;
        if (selection == 1) {
            AddStudent(InputClass->listStudent,yearName, InputClass->className,InputClass->numStudent);
            StudyClassManage(InputClass, yearName);
        }
    } else {
        do {
            system("cls");
            cout << "Student Management" << endl;
            cout << endl; 
            cout << "Year: " << yearName << endl;
            cout << "Class: " << InputClass->className << endl;
            cout << endl;
            cout << left << setw(5) << "No";
            cout << left << setw(15) << "Student ID";
            cout << left << setw(25) << "First Name";
            cout << left << setw(15) << "Last Name";
            cout << left << setw(11) << "Gender";
            cout << left << setw(19) << "Date of Birth";
            cout << left << setw(25) << "Social ID" << endl;
            DisplayStudentList(InputClass->listStudent);
            cout << endl;
            cout << "0. Back" << endl;
            cout << endl << ">> ";
            cin >> selection;
            if (selection == 0)
                break;
        } while (true);
    }
}
void ListClassManage(Schoolyear* InputYear)
{
    int selection;
    if (InputYear->listClass == nullptr) {
        system("cls");
        cout << "No class data available" <<endl;
        cout << "Add class ? (1 to proceed | 0 to cancel)" << endl;
        cin >> selection;
        if (selection == 1) {
            AddClass(InputYear->listClass);
            ListClassManage(InputYear);
        }
    }
    else {
        int maxSelection;
        StudyClass* toClass = nullptr;
        do {
            system("cls");
            cout << "Classes Management" << endl;
            cout << endl;
            cout << "Year: " << InputYear->year << endl;
            cout << endl;
            cout << "List of classes: " << endl;
            DisplayClassList(InputYear->listClass, maxSelection);
            cout << endl;
            cout << "0. Back" << endl;
            cout << endl << ">> ";
            cin >> selection;
            if (selection == 0)
                break;
            if (selection > 0 && selection <= maxSelection) {
                toClass = navigateClass(InputYear->listClass, selection);
                StudyClassManage(toClass, InputYear->year);
            }
        } while (true);
    }
}
void SchoolYearManage(Schoolyear *DataList)
{
    
    int maxSelection;
    Schoolyear* toYear;
    string selection;
    do {
        system("cls");
        cout << "School Year Management" << endl << endl;
        cout << "List of years:" << endl;
        DisplayYearList(DataList,maxSelection);
        cout << endl;
        cout << "n. Add a new year" << endl;
        cout << "0. End program" << endl;
        cout << endl << ">> ";
        cin >> selection;
        if (selection == "n") {
            AddYear(DataList);
            continue;
        }
        int intselection = stoi(selection);
        if (intselection == 0)
            break;
        if (intselection > 0 && intselection <= maxSelection) {
            toYear = navigateYear(DataList,intselection);
            ListClassManage(toYear);
        }
    } while (true);
}

void StaffGUI(Schoolyear* DataBase)
{   
    int selection;
    do {
        cout << "1. School year initialization." << endl;
        cout << "2. Semester management" << endl;
        cout << "0. Exit program" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == 0)
            break;
        if (selection == 1)
            SchoolYearManage(DataBase);
        if (selection == 2)
        {
            
        }
    } while (true);
    
}

void StudentGUI(Schoolyear* DataBase)
{
    
}