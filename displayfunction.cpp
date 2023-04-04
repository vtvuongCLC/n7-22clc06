#include "header/datafunction.h"
#include "header/displayfunction.h"
#include "header/InitSemester.h"
using namespace std;

bool validInfo(Info infoparam,char gender)
{
    if (gender != 'm' && gender != 'M')
    {
        if (gender != 'f' && gender != 'F')
        return false;
    }
    if (infoparam.Birth.day <= 0 || infoparam.Birth.day > 31)
        return false;
    if (infoparam.Birth.month <= 0 || infoparam.Birth.month > 12)
        return false;
    if (infoparam.Birth.year < 0)
        return false;
    return true;
}

void AddStudentManual(Student* &listStudent, string yearName, string className, int &numStudent)
{
    Student* curStudent = nullptr;
    do {
        int check;
        system("cls");
        cout << "Add new student ? (1 to proceed | 0 to exit) : " << endl;
        cin >> check;
        if (check <= 0)
            break;
        Info tempInfo;
        cin.ignore();
        cout << "Enter student ID : ";
        getline(cin,tempInfo.StudentID,'\n');
        cout << "Enter student First Name : ";
        getline(cin,tempInfo.FirstName,'\n');
        cout << "Enter student Last Name : ";
        getline(cin,tempInfo.LastName,'\n');
        char gender;
        cout << "Enter student Gender (male = m | female = f) : ";
        cin >> gender;
        cout << "Enter student Date of birth (Ex: 29 2 2004) : ";
        cin >> tempInfo.Birth.day >> tempInfo.Birth.month >> tempInfo.Birth.year;
        cin.ignore();
        cout << "Enter student Social ID: ";
        getline(cin,tempInfo.SocialID,'\n');
        if (validInfo(tempInfo,gender) == true) {
            if (listStudent == nullptr) {
                listStudent = new Student;
                curStudent = listStudent;
            } else {
                curStudent->nextStudent = new Student;
                curStudent = curStudent->nextStudent;
            }
            numStudent++;
            curStudent->yearName = yearName;
            curStudent->className = className;
            curStudent->password = className;
            curStudent->No = numStudent;
            curStudent->dInfo.StudentID = tempInfo.StudentID;
            curStudent->dInfo.FirstName = tempInfo.FirstName;
            curStudent->dInfo.LastName = tempInfo.LastName;
            if (gender == 'm' || gender == 'M') {
                curStudent->dInfo.Gender = "male";
            } else {
                curStudent->dInfo.Gender = "female";
            }
            curStudent->dInfo.Birth.day = tempInfo.Birth.day;
            curStudent->dInfo.Birth.month = tempInfo.Birth.month;
            curStudent->dInfo.Birth.year = tempInfo.Birth.year;
            curStudent->dInfo.SocialID = tempInfo.SocialID;
        } else {
            cout << "Some information is invalid...";
            system("pause"); 
        }
    } while (true);
}
void AddStudentCSV(Student* &listStudent, string yearName, string className, int &numStudent)
{
    string filepath;
    ifstream csvIn;
    system("cls");
    do {
        cout << "Enter CSV file path: ";
        getline(cin,filepath,'\n');
        csvIn.open(filepath);
        if (csvIn.is_open() == false) {
            int selection;
            cout << "Unable to open Input file , please re-check the filepath and enter 1 to try again (or enter 0 to exit)" << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == 0)
                return;
        }
    } while (csvIn.is_open() == false);
    csvIn.ignore(1000,'\n');
    Student* curStudent = nullptr;
    while (csvIn.eof() == false)
    {
        if (listStudent == nullptr) {
            listStudent = new Student;
            curStudent = listStudent;
        } else {
            curStudent->nextStudent = new Student;
            curStudent = curStudent->nextStudent;
        }
        curStudent->yearName = yearName;
        curStudent->className = className;
        numStudent++;
        string tempdata;
        getline(csvIn,tempdata,',');
        curStudent->No = stoi(tempdata);
        
        getline(csvIn,tempdata,',');
        curStudent->password = className;
        curStudent->dInfo.StudentID = tempdata;        
        
        getline(csvIn,tempdata,',');
        curStudent->dInfo.FirstName = tempdata;
        
        getline(csvIn,tempdata,',');
        curStudent->dInfo.LastName = tempdata;
        
        getline(csvIn,tempdata,',');
        curStudent->dInfo.Gender = tempdata;
        
        getline(csvIn,tempdata,'/');
        curStudent->dInfo.Birth.day = stoi(tempdata);
        
        getline(csvIn,tempdata,'/');
        curStudent->dInfo.Birth.month = stoi(tempdata);
        
        getline(csvIn,tempdata,',');
        curStudent->dInfo.Birth.year = stoi(tempdata);
        
        getline(csvIn,tempdata,'\n');
        curStudent->dInfo.SocialID = tempdata;
    }
    system("pause");
}
void AddStudent(Student* &listStudent, string yearName, string className, int &numStudent)
{
    char choose; 
    cout << "Please choose the input method (m - manual(default) or f - CSV file input): " << endl;
    cout << ">> ";
    cin >> choose;
    if (choose == 'f' || choose == 'F')
        AddStudentCSV(listStudent,yearName,className, numStudent);
    else
        AddStudentManual(listStudent,yearName,className, numStudent);
}
void AddClass(StudyClass* &listClass)
{
    StudyClass* curClass = nullptr;
    string tempClass;
    cout << "Enter Classes in this year (0 to stop): " << endl << endl;
    cin.ignore();
    do {
        cout << "Enter Class name: ";
        getline(cin,tempClass,'\n');
        if (tempClass == "0") {
            break;
        }
        if (listClass == nullptr) {
            listClass = new StudyClass;
            curClass = listClass;
        } else {
            curClass->nextClass = new StudyClass;
            curClass = curClass->nextClass;
        }
        curClass->className = tempClass;
    } while (tempClass != "0");
}
string getYearData(Schoolyear* listYear)
{
    system("cls");
    string schoolyear;
    bool exist;
    do {
        exist = false;
    cout << "Enter School year's start year and end year" << endl << endl;
    cin.ignore();
    cout << "Enter School year's Start year: ";
    cin >> schoolyear;
    schoolyear += '-';
    string temp;
    cout << "Enter School year's End year: ";
    cin >> temp;
    schoolyear += temp;
    Schoolyear* check = listYear;
    while (check != nullptr) {
        if (check->year == schoolyear) {
            cout << "This year has already existed" << endl;
            system("pause");
            exist = true;
            break;
        }
        check = check->nextYear;
    }
    } while (exist == true && listYear != nullptr);
    return schoolyear;
}
void AddYear(Schoolyear* &listYear)
{
    Schoolyear* newYear = new Schoolyear;
    Schoolyear* tempPointer = nullptr;
    newYear->year = getYearData(listYear);
    newYear->nextYear = listYear;
    listYear = newYear;
}

Schoolyear* navigateYear(Schoolyear* listYear, int userindex)
{
    if (listYear == nullptr)
        return nullptr;
    int i = 0;
    while (listYear != nullptr) {
        i++;
        if (i == userindex)
            return listYear;
        listYear = listYear->nextYear;
    }
    return nullptr;
}
StudyClass* navigateClass(StudyClass* listClass, int userindex)
{
    if (listClass == nullptr)
        return nullptr;
    int i = 0;
    while (listClass != nullptr) {
        i++;
        if (i == userindex)
            return listClass;
        listClass = listClass->nextClass;
    }
    return nullptr;
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
void DisplaySemester(Semester* SemesterList)
{
    cout << left << setw(5) << "Index";
    cout << left << setw(10) << "Semester";
    cout << left << setw(10) << "Start";
    cout << left << setw(10) << "End";
    cout << endl;
    while (SemesterList != nullptr) {
        
        cout << left << setw(5) << SemesterList->index;
        cout << left << setw(10) << SemesterList->semester;
        cout << left << setw(10) << SemesterList->start;
        cout << left << setw(10) << SemesterList->end;
        cout << endl;
        SemesterList = SemesterList->nextSemester; 
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
            } else {
                DisplayStudentList(curClass->listStudent);
            }
            cout << endl;
            cout << "n. Add student" << endl;
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
            maxSelection = 0;
        } else {
            DisplayClassList(curYear->listClass,maxSelection);
        }
        cout << endl;
        cout << "n. New class" << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == "0")
            break;
        if (selection == "n" || selection == "N") {
            AddClass(curYear->listClass);
        }
        if (curYear->listClass != nullptr) {
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
        //if (selection == 2)
            //SemesterManager();
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
            AddYear(DB.YearList);
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