#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "header.h"
using namespace std;
bool validInfo(int no,Info infoparam,char gender) {
    if (gender != 'm' && gender != 'f')
        return false;
    if (infoparam.Birth.day <= 0 || infoparam.Birth.day > 31)
        return false;
    if (infoparam.Birth.month <= 0 || infoparam.Birth.day > 12)
        return false;
    if (infoparam.Birth.year < 0)
        return false;
    return true;
}
void AddStudentManual(bool toAppend,string className)
{
    ofstream StudentDataOut;
    if (toAppend == true) {
        StudentDataOut.open(className+".txt",ios::app);
    }
    else
        StudentDataOut.open(className+".txt");
    int no = 0;
    do {
        int check;
        system("cls");
        cout << "Add new student (-1 to exit) : " << endl;
        cin >> check;
        if (check < 0)
            break;
        no += 1;
        Info tempInfo;
        cout << "Enter student ID : ";
        getline(cin,tempInfo.StudentID,'\n');
        cout << "Enter student First Name : ";
        getline(cin,tempInfo.FirstName,'\n');
        cout << "Enter student Last Name : ";
        getline(cin,tempInfo.LastName,'\n');
        char gender;
        cout << "Enter student Gender(male = m | female = f) : ";
        cin >> gender;
        gender = tolower(gender);
        cout << "Enter student Date of birth(dd/mm/yyyy) : ";
        scanf("%d/%d/%d",&tempInfo.Birth.day,&tempInfo.Birth.month,&tempInfo.Birth.year);
        if (validInfo(tempInfo,gender) == true) {
            StudentDataOut << no << ',';
            StudentDataOut << tempInfo.StudentID << ',';
            StudentDataOut << tempInfo.FirstName << ',';
            StudentDataOut << tempInfo.LastName << ',';
            if (gender == 'm')
                StudentDataOut << "male" << ',';
            else
                StudentDataOut << "female" << ',';
                StudentDataOut << tempInfo.Birth.day << '/' << tempInfo.Birth.month << '/' << tempInfo.Birth.year << ',';
                StudentDataOut << tempInfo.SocialID << endl;
        } else {
            cout << "Some information is invalid...";
            system("pause"); 
        }
    } while (true);
        StudentDataOut.close();
}
void AddStudentCSV(bool toAppend, string className)
{
    ofstream StudentDataOut;
    if (toAppend == true) {
        StudentDataOut.open(className+".txt",ios::app);
    }
    else
        StudentDataOut.open(className+".txt");
    string filepath;
    cout << "Enter CSV file path: ";
    getline(cin,filepath,'\n');
    ifstream csvIn;
    csvIn.open(filepath);
    if (csvIn.is_open() == false) {
        cout << "Unable to open file (ERROR)";
        return;
    }
    csvIn.ignore(1000,'\n');
    while (csvIn.eof() == false)
    {
        string tempdata;
        getline(csvIn,tempdata,'\n');
        StudentDataOut << tempdata << endl;
    }
    StudentDataOut.close();
}
void InitSchoolYear(bool toAppend, string Yearname)
{
    ofstream ClassDataOut;
    string schoolyear;
    if (toAppend == true) {
        schoolyear = Yearname;
        ClassDataOut.open(schoolyear+".txt", ios::app);
    }
    else {
        cout << "Enter School year's Start year: ";
        cin >> schoolyear;
        schoolyear += '-';
        string temp;
        cout << "Enter School year's End year: ";
        cin >> temp;
        schoolyear += temp;
        ClassDataOut.open(schoolyear+".txt");
        ClassDataOut << schoolyear << endl;
    }   
    cin.ignore(1000,'\n');
    cout << "Enter Class name (0 to stop)" << endl << endl;
    string tempClass;
    do {
        cout << "Enter a Class name: ";
        getline(cin,tempClass,'\n');
        if (tempClass == "0")
            break;
        ClassDataOut << tempClass << endl;
    } while (tempClass != "0");
    ClassDataOut.close();
}
