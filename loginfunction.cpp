#include "header/loginfunction.h"

void ChangePasswordStudent(Student* curStudent){
    int check;
    string password, confirm;
    while(true){
        system("cls");
        cout << "Do you want to continue changing password ? (1 to proceed | 0 to exit): "; cin >> check;
        if(check == 0) return;
        if(check != 1) continue;
        system("cls");
        cout << "Change Password\n\n";
        cout << "Current Password: "; cin >> password;
        if(password != curStudent->password){
            cout << "You must enter a valid password\n";
        }
        else {
            cout << "New Password: "; cin >> password;
            cout << "Confirm Password: "; cin >> confirm;
            if(password == confirm){
                curStudent->password = confirm;
                cout << "The password has been changed successfully!!!\n";
            }
            else{
                cout << "The new password and confirmation password do not match. THe password hasn't been changed!!!\n";
            }
        }
        system("pause");
    }
}

int login_student(string id,string pass, Schoolyear* DataBase, Student* &toStudent) {
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
					if (curStudent->password == pass) {
						toStudent = curStudent;
						return 1;
					}
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
int login(Schoolyear *DataBase, Student* &toStudent) {
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
		toStudent = nullptr;
		do {
			cout << "Student ID: ";
			cin >> id;
			cout << "Password: ";
			cin >> pass;
			key = login_student(id, pass, DataBase,toStudent);
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