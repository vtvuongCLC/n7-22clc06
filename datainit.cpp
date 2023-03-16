#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "header.h"
using namespace std;
bool validInfo(Info infoparam,char gender) {
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
void AddStudentManual(string className)
{
    ofstream StudentDataOut;
    ofstream accountOut;
    StudentDataOut.open(className+".txt");
    accountOut.open("StudentAccount.txt", ios::app);
    int no = 0;
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
        cout << "Enter student Date of birth (dd/mm/yyyy) : ";
        scanf("%d %d %d",&tempInfo.Birth.day,&tempInfo.Birth.month,&tempInfo.Birth.year);
        cin.ignore();
        cout << "Enter student Social ID: ";
        getline(cin,tempInfo.SocialID,'\n');
        if (validInfo(tempInfo,gender) == true) {
            accountOut << tempInfo.StudentID << endl;
            accountOut << className << endl;
            StudentDataOut << no << ',';
            StudentDataOut << tempInfo.StudentID << ',';
            StudentDataOut << tempInfo.FirstName << ',';
            StudentDataOut << tempInfo.LastName << ',';
            if (gender == 'm' || gender == 'M') {
                StudentDataOut << "male" << ',';
            }  
            else // (gender == 'f' || gender == 'F') 
            {
                StudentDataOut << "female" << ',';
            }
            StudentDataOut << tempInfo.Birth.day << '/' << tempInfo.Birth.month << '/' << tempInfo.Birth.year << ',';
            StudentDataOut << tempInfo.SocialID << endl;
        } else {
            cout << "Some information is invalid...";
            system("pause"); 
        }
    } while (true);
    StudentDataOut.close();
    accountOut.close();
}
void AddStudentCSV(string className)
{
    ofstream StudentDataOut;
    StudentDataOut.open(className+".txt");
    string filepath;
    cout << "Enter CSV file path: ";
    getline(cin,filepath,'\n');
    ifstream csvIn;
    ofstream accountOut;
    accountOut.open("StudentAccount.txt", ios::app);
    csvIn.open(filepath);
    if (csvIn.is_open() == false) {
        cout << "Unable to open file (ERROR)";
        return;
    }
    csvIn.ignore(1000,'\n');
    while (csvIn.eof() == false)
    {
        string tempdata;
        getline(csvIn,tempdata,',');
        StudentDataOut << tempdata << ',';
        getline(csvIn,tempdata,',');
        StudentDataOut << tempdata << ',';
        accountOut << tempdata << endl;
        accountOut << className << endl; 
        getline(csvIn,tempdata,'\n');
        StudentDataOut << tempdata << endl;
    }
    StudentDataOut.close();
    accountOut.close();
}
bool IsemptyFile(string fileName)
{
    bool result = false;
    ifstream test;
    test.open(fileName + ".txt");
    if (test.is_open() == false) {
        result = true;
    }
    else
    {
        string temp;
        getline(test,temp,'\n');
        if (temp.length() == 0)
            result = true;                    
    }
    test.close();
    return result;
}
int countLine(string fileName)
{
    ifstream ifs;
    ifs.open(fileName + ".txt");
    int count = 0;
    while (ifs.eof() == false)
    {
        count += 1;
        string temp;
        getline(ifs,temp,'\n');
    }
    ifs.close();
    return count-1;
}
void LoadClass(string YearName, StudyClass* ptrCls, int n)
{
    ifstream ifs;
    ifs.open(YearName+".txt");
    for (int i = 0; i < n; i++)
    {
        string buffer;
        getline(ifs,buffer,'\n');
        ptrCls[i].className = buffer;
    }
    ifs.close();
}
void DisplayClass(StudyClass* ptrCls,int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << i+1 << ". " << ptrCls[i].className << endl;
    }
    
}
void ClassManage(string YearName)
{
    system("cls");
    int n = countLine(YearName);
    StudyClass* ptrClass = new StudyClass[n];
    LoadClass(YearName,ptrClass,n);
    do {
        string selection;
        system("cls");
        DisplayClass(ptrClass,n);
        cout << "Enter 'c' to exit " << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == "c")
            break;
        else
        {
            int intselect = stoi(selection);
            if (intselect <= 0 || intselect > n) {
                cout << "Class not found" << endl;
                system("pause");
            }
            else {
                system("cls");
                char choose; 
                cout << "Please choose the input method (m - manual(default) or f - CSV file input): " << endl;
                cout << ">> ";
                cin >> choose;
                if (choose == 'f' || choose == 'F')
                    AddStudentCSV(ptrClass[intselect-1].className);
                else
                    AddStudentManual(ptrClass[intselect-1].className);
            }
        }
    } while (true);
    delete []ptrClass;
}
void LoadYear(string ListYearFile,Schoolyear* ptrS, int n)
{
    ifstream ifs;
    ifs.open(ListYearFile + ".txt");
    for (int i = 0; i < n; i++)
    {
        string temp;
        getline(ifs,temp,'\n');
        ptrS[i].year = temp;
    }
    ifs.close();
}
void DisplayYear(Schoolyear* ptrS, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << i+1 << ". " << ptrS[i].year << endl;
    }
}
void InitSchoolYear(string ListYearFile)
{
    ifstream check;
    ofstream ClassDataOut;
    ofstream YearOut;
    YearOut.open(ListYearFile+".txt", ios::app);
    string schoolyear;
    check.open(ListYearFile+".txt");
    bool existed;
    do {
        system("cls");
        char ask;
        cout << "Press any key to continue (0 to exit): " << endl;
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
        if (tempClass == "0")
        {
            ClassDataOut.close();
            ClassManage(schoolyear);
            break;
        }
            
        ClassDataOut << tempClass << endl;
    } while (tempClass != "0");
    ClassDataOut.close();
}
void SchoolYearManage(string ListYearFile)
{
    system("cls");
    if (IsemptyFile(ListYearFile) == true)
    {
        cout << "First startup, initializing database..." << endl;
        system("pause");
        InitSchoolYear(ListYearFile);
    }
    else
    {
        int n = countLine(ListYearFile);
        Schoolyear* ptrS = new Schoolyear[n];
        LoadYear(ListYearFile,ptrS,n);
        do {
            system("cls");
            string selection;
            cout << "Choose a year to modify" << endl;
            cout << "List of year: " << endl;
            DisplayYear(ptrS,n);
            cout << "0. Add year" << endl;
            cout << "Enter 'c' to exit " << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == "c" || selection == "C")
                break;
            else if (selection == "0")
                InitSchoolYear(ListYearFile);
            else
            {
                int intselect = stoi(selection);
                if (intselect > 0 && intselect <= n)
                    ClassManage(ptrS[intselect-1].year);
            }
        } while (true);
        delete []ptrS;
    }
}
// int main() <--- FOR TESTING AND DEBUGGING
// {
//     string ListYearFIle = "SchoolyearList";
//     SchoolYearManage(ListYearFIle);
// }

// void pullYearFromFile(Schoolyear* &pHead, string ListYearFile)
// {
//     ifstream ifs;
//     ifs.open(ListYearFile + ".txt");
//     Schoolyear* cur = nullptr;
//     while (ifs.eof() == false)
//     {
//         string buffer;
//         getline(ifs,buffer,'\n');
//         if (pHead == nullptr)
//         {
//             pHead = new Schoolyear;
//             cur = pHead;    
//         }
//         else
//         {
//             cur->nextYear = new Schoolyear;
//             cur = cur->nextYear;
//         }
//         cur->year = buffer;
//     }
//     ifs.close();
// }
// void DisplayYearList(Schoolyear* &pHead)
// {
//     int index = 0;
//     while (pHead != nullptr)
//     {
//         index += 1;
//         cout << index << ". " << pHead->year << endl;
//         pHead = pHead->nextYear;
//     }
//     cout << "0. Add year" << endl;
// }
// void DeleteYearList(Schoolyear* &pHead)
// {
//     while (pHead != nullptr)
//     {
//         Schoolyear* toDel = pHead;
//         pHead = pHead->nextYear;
//         delete(toDel);
//     }
// }
