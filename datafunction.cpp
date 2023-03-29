#include <fstream>
#include <iostream>
#include "datafunction.h"
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
bool IsemptyFile(string fileName)
{
    bool result = false;
    ifstream test;
    test.open(fileName + ".txt");
    if (test.is_open() == false) {
        result = true;
    }
    else {
        string temp;
        getline(test,temp,'\n');
        if (temp.empty() == true)
            result = true;                    
    }
    test.close();
    return result;
}

void LoadYearFromFile(string YearFile, Schoolyear* &listYear)
{
    ifstream YearIn;
    YearIn.open(YearFile+".txt");
    Schoolyear* curYear = nullptr;
    while (YearIn.eof() == false) {
        string tempData;
        getline(YearIn,tempData,'\n');
        if (tempData.empty() == false) {
            if (listYear == nullptr) {
                listYear = new Schoolyear;
                curYear = listYear;
            } else {
                curYear->nextYear = new Schoolyear;
                curYear = curYear->nextYear;
            }
            curYear->year = tempData;
        }
    }
    YearIn.close();
}
void LoadClassFromfile(string yearName, StudyClass* &listClass)
{
    if (IsemptyFile(yearName) == true)
        return;
    ifstream ClassIn;
    ClassIn.open(yearName+".txt");
    StudyClass* curClass = nullptr;
    while (ClassIn.eof() == false) {
        string tempClass;
        getline(ClassIn,tempClass,'\n');
        if (tempClass.empty() == false) {
            if (listClass == nullptr) {
                listClass = new StudyClass;
                curClass = listClass;
            } else {
                curClass->nextClass = new StudyClass;
                curClass = curClass->nextClass;
            }
            curClass->className = tempClass; 
        }
    }
    ClassIn.close();
}
void LoadStudentListFromFile(string yearName, string className, Student* &listStudent)
{
    if (IsemptyFile(className) == true)
        return;
    ifstream StudentIn;
    StudentIn.open(className+".txt");
    Student* curStudent = nullptr;
    while (StudentIn.eof() == false) {
        string tempData;
        getline(StudentIn,tempData,',');
        if (tempData.empty() == false) {
            if (listStudent == nullptr) {
                listStudent = new Student;
                curStudent = listStudent;
            } else {
                curStudent->nextStudent = new Student;
                curStudent = curStudent->nextStudent;
            }
            curStudent->yearName = yearName;
            curStudent->className = className;
            curStudent->No = stoi(tempData);
            getline(StudentIn,tempData,',');
            curStudent->dInfo.StudentID = tempData;
            getline(StudentIn,curStudent->password,',');
            getline(StudentIn,curStudent->dInfo.FirstName,',');
            getline(StudentIn,curStudent->dInfo.LastName,',');
            getline(StudentIn,curStudent->dInfo.Gender,',');
            getline(StudentIn,tempData,'/');
            curStudent->dInfo.Birth.day = stoi(tempData);
            getline(StudentIn,tempData,'/');
            curStudent->dInfo.Birth.month = stoi(tempData);
            getline(StudentIn,tempData,',');
            curStudent->dInfo.Birth.year = stoi(tempData);
            getline(StudentIn,curStudent->dInfo.SocialID,'\n');
        }
    }
    StudentIn.close();
}
void LoadData(string YearFile, Schoolyear* &listYear)
{
    LoadYearFromFile(YearFile,listYear);
    Schoolyear* curYear = listYear;
    while (curYear != nullptr) {
        LoadClassFromfile(curYear->year,curYear->listClass);
        StudyClass* curClass = curYear->listClass;
        while (curClass != nullptr) {
            LoadStudentListFromFile(curYear->year,curClass->className,curClass->listStudent);
            curClass = curClass->nextClass;
        }
        curYear = curYear->nextYear;
    }
        
}

void AddYear(Schoolyear* &listYear)
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
    } while (exist == true);
    if (listYear == nullptr) {
        listYear = new Schoolyear;
        listYear->year = schoolyear;
        return;
    }
    Schoolyear* curYear = listYear;
    while (curYear->nextYear != nullptr)
    {
        curYear = curYear->nextYear;
    }
    curYear->nextYear = new Schoolyear;
    curYear = curYear->nextYear;
    curYear->year = schoolyear;
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
void AddStudentManual(Student* &listStudent, string yearName, string className)
{
    int no = 0;
    Student* curStudent = nullptr;
    do {
        int check;
        system("cls");
        cout << "Add new student ? (1 to proceed | 0 to exit) : " << endl;
        cin >> check;
        if (check <= 0)
            break;
        no += 1;
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
            curStudent->yearName = yearName;
            curStudent->className = className;
            curStudent->password = className;
            curStudent->No = no;
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
void AddStudentCSV(Student* &listStudent, string yearName, string className)
{
    string filepath;
    ifstream csvIn;
    system("cls");
    do {
        cout << "Enter CSV file path: ";
        getline(cin,filepath,'\n');
        csvIn.open(filepath);
        if (csvIn.is_open() == false) {
            cout << "Unable to open file (ERROR)";
            system("pause");
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
void AddStudent(Student* &listStudent, string yearName, string className)
{
    char choose; 
    cout << "Please choose the input method (m - manual(default) or f - CSV file input): " << endl;
    cout << ">> ";
    cin >> choose;
    if (choose == 'f' || choose == 'F')
        AddStudentCSV(listStudent,yearName,className);
    else
        AddStudentManual(listStudent,yearName,className);
}

void InitBaseData(Schoolyear* &listYear)
{  
    system("cls");
    AddYear(listYear);
    AddClass(listYear->listClass);
}
void SaveData(string YearFile, Schoolyear* ListYear)
{
    if (ListYear == nullptr)
        return;
    ofstream out;
    Schoolyear* curYear = ListYear;
    StudyClass* curClass = nullptr;
    Student* curStudent = nullptr;
    out.open(YearFile+".txt");
    while (curYear != nullptr) {
        out << curYear->year << endl;
        curYear = curYear->nextYear;
    }
    out.close();
    if (ListYear->listClass == nullptr)
        return;
    curYear = ListYear;
    while (curYear != nullptr) {
        out.open(curYear->year+".txt");
        curClass = curYear->listClass;
        while (curClass != nullptr) {
            out << curClass->className << endl;
            curClass = curClass->nextClass;
        }
        out.close();
        curYear = curYear->nextYear;
    }
    curYear = ListYear;
    while (curYear != nullptr) {
        curClass = curYear->listClass;
        while (curClass != nullptr) {
            curStudent = curClass->listStudent;
            out.open(curClass->className+".txt");
            while (curStudent != nullptr) {
                out << curStudent->No << ',';
                out << curStudent->dInfo.StudentID << ',';
                out << curStudent->password << ',';
                out << curStudent->dInfo.FirstName << ',';
                out << curStudent->dInfo.LastName << ',';
                out << curStudent->dInfo.Gender << ',';
                out << curStudent->dInfo.Birth.day << '/';
                out << curStudent->dInfo.Birth.month << '/';
                out << curStudent->dInfo.Birth.year << ',';
                out << curStudent->dInfo.SocialID << endl;
                curStudent = curStudent->nextStudent;
            }
            out.close();
            curClass = curClass->nextClass;
        }
        curYear = curYear->nextYear;
    }

}
void ClearData(Schoolyear* &listYear)
{
    Schoolyear* curYear = nullptr;
    StudyClass* curClass = nullptr;
    Student* curStudent = nullptr;
    while (listYear != nullptr) {
        curYear = listYear;
        listYear = listYear->nextYear;
        while (curYear->listClass != nullptr) {
            curClass = curYear->listClass;
            while (curClass->listStudent != nullptr) {
                curStudent = curClass->listStudent;
                curClass->listStudent = curClass->listStudent->nextStudent;
                delete curStudent;
            }
            curYear->listClass = curYear->listClass->nextClass;
            delete curClass;
        }
        delete curYear;
    }
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