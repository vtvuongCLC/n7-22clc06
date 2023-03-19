#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "header.h"
#include <iomanip>
using namespace std;
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
        getline(StudentIn,tempData,'\n');
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
            curStudent->dInfo.No = stoi(tempData);
            getline(StudentIn,curStudent->dInfo.StudentID,',');
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
void InitBaseData(string YearFile)
{
    ifstream check;
    ofstream ClassDataOut;
    ofstream YearOut;
    YearOut.open(YearFile+".txt", ios::app);
    string schoolyear;
    check.open(YearFile+".txt");
    bool existed;
    do {
        system("cls");
        char ask;
        cout << "Enter any key to continue (0 to exit): " << endl;
        cin >> ask;
        if (ask  == '0')
        {
            YearOut.close();
            check.close();
            return;
        }
        cout << "Enter School year's start year and end year" << endl;
        cin.ignore();
        cout << "Enter School year's Start year: ";
        cin >> schoolyear;
        schoolyear += '-';
        string temp;
        cout << "Enter School year's End year: ";
        cin >> temp;
        schoolyear += temp;
        existed = false;
        while (check.eof() == false)
        {
            string test;
            getline(check,test,'\n');
            if (test == schoolyear)
            {
                cout << "This school year is already existed" << endl;
                system("pause");
                existed = true;
                check.clear();
                check.seekg(0);
                break;
            }
        }
    } while (existed == true);
    check.close();
    YearOut << schoolyear << endl;
    YearOut.close();
    ClassDataOut.open(schoolyear+".txt");
    cin.ignore(1000,'\n');
    cout << "Enter Classes in this year (0 to stop): " << endl << endl;
    string tempClass;
    do {
        cout << "Enter Class name: ";
        getline(cin,tempClass,'\n');
        if (tempClass == "0") {
            break;
        }
        ClassDataOut << tempClass << endl;
    } while (tempClass != "0");
    ClassDataOut.close();
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
                out << curStudent->dInfo.No << ',';
                out << curStudent->dInfo.StudentID << ',';
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
int main()
{
    string YearFile = "Listyear";
    Schoolyear* DataList = nullptr;
    if (IsemptyFile(YearFile) == true) {
        InitBaseData(YearFile);
    }
    LoadData(YearFile,DataList);
    SaveData(YearFile,DataList);
    ClearData(DataList);
}