#include "header/structlist.h"
#include "header/loginfunction.h"
#include <fstream>
#include <iostream>
using namespace std;
int login_student(string id,string pass, Schoolyear* DataBase) {
	if (DataBase == nullptr)
		return -2;
	Schoolyear* curYear = DataBase;
	StudyClass* curClass = nullptr;
	Student* curStudent = nullptr;
	while (curYear != nullptr)
	{
		curClass = curYear->listClass;
		while (curClass != nullptr)
		{
			curStudent = curClass->listStudent;
			while (curStudent != nullptr)
			{
				if (curStudent->dInfo.StudentID == id) {
					if (curStudent->password == pass)
						return 1;
					else
						return 0;
				}
				curStudent = curStudent->nextStudent;
			}
			curClass = curClass->nextClass;
		}
		curYear = curYear->nextYear;
	}
	// while (!(iYear == nullptr && iClass == nullptr && searcher == nullptr)) {
	// 	if (searcher == nullptr && iClass != nullptr) {
	// 		searcher = iClass->listStudent;
	// 		iClass = iClass->nextClass;
	// 	}
	// 	if (iClass == nullptr && iYear != nullptr) {
	// 		iClass = iYear->listClass;
	// 		iYear = iYear->nextYear;
	// 	}
	// 	else
	// 		searcher = searcher->nextStudent;
	// }
	return -1;
}
bool login_staff(string AccountStaff, string passStaff) {
    ifstream filein;
	bool key = false;
    filein.open("Data\\Staff.csv");
	if (filein.is_open() == false)
		return false;
    while(!filein.eof()){
        string tmpAcc;
        string tmpPass;
        
        getline(filein,tmpAcc,',');
        getline(filein,tmpPass);
		if (tmpAcc == AccountStaff && tmpPass == passStaff)
			key = true;
    }
    filein.close();
    return key;
}
int login(Schoolyear *DataBase) {
    int tmp;
    cout<<"You are :"<<endl;
    cout<<"1. Student"<<endl;
    cout<<"2. Staff"<<endl;
    cout<<"Enter another number to exit"<<endl;
    cout<<">> ";
    cin>>tmp;
	if (tmp == 1) {
		if (DataBase == nullptr)
		{
			cout << "No data found. Contact Staff for more information" << endl;
			return -1;
		}
		string id;
		string pass;
		int key;
		do {
			cout << "Student ID: ";
			cin >> id;
			cout << "Password: ";
			cin >> pass;
			key = login_student(id, pass, DataBase);
			if (key == 1)
				break;
			if (key == -1) {
				cout << "Student ID is not correct, please try again" << endl;
			}
			if (key == 0) {
				cout << "Password is not correct, please try again" << endl;
			}
			system("pause");
		} while (key != 1);
		cout << "Successful to login" << endl;
		system("pause");
		return 1;
	}
	if (tmp == 2) {   
        string AccountStaff;
        string passStaff;
		bool key;
        do{
        cout<<"Staff Account: ";
        cin>>AccountStaff;
        cout<<"Password: ";
        cin>>passStaff;
		key = login_staff(AccountStaff, passStaff);
		} while (key == false);
        cout<<"Successful to login"<<endl;
		system("pause");
        return 2;
    }   
	return -1; 
}