#include "header/loginfunction.h"
#include "header/ultilityfunction.h"

bool login_student(Schoolyear* SchoolyearList, Student* &toStudent, StudyClass* &toStudyClass)
{
	if (SchoolyearList == nullptr) {
		cout << "The system is currently under maintenance, please contact the Staff for more information" << endl;
		system("pause");
		return false;
	}
	Schoolyear* curYear;
	StudyClass* curClass = nullptr;
	string username;
	string password;
	char choice;
	do {
		system("cls");
		cout << "Student Login Panel" << endl;
		cout << "Proceed ? y/n" << endl;
		cin >> choice;
		if (choice != 'y' && choice != 'Y')
			break;
		cin.ignore(1,'\n');
		cout << "Username: ";
		getline(cin,username);
		cout << "Password: ";
		getline(cin,password);
		
		curYear = SchoolyearList;
		int key;
		while (curYear != nullptr)
		{
			curClass = curYear->listCLC;
			key = searchStudentAccount(username,password,curClass,toStudent,toStudyClass);
			if (key == 1) {
				return true;
			}
			if (key == 0) {
				return false;
			}
			curClass = curYear->listAPCS;
			key = searchStudentAccount(username,password,curClass,toStudent,toStudyClass);
			if (key == 1) {
				return true;
			}
			if (key == 0) {
				return false;
			}
			curClass = curYear->listVP;
			key = searchStudentAccount(username,password,curClass,toStudent,toStudyClass);
			if (key == 1) {
				return true;
			}
			if (key == 0) {
				return false;
			}
			curYear = curYear->nextYear;
		}
		if (curYear == nullptr) {
			cout << "Invalid username or password" << endl;
			system("pause");
		}
	} while (true);
	return false;
}
bool login_staff(StaffAccount* staffList, StaffAccount* &toStaff)
{
    if (staffList == nullptr)
		return false;
	char choice;
	string username;
	string password;
	do {
		system("cls");
		cout << "Staff Login Panel" << endl;
		cout << "Proceed ? y/n" << endl;
		cin >> choice;
		if (choice != 'y' && choice != 'Y')
			break;
		cin.ignore(1000,'\n');
		cout << "Username: ";
		getline(cin,username);
		cout << "Password: ";
		getline(cin,password);

		StaffAccount* cur = staffList;
		while (cur != nullptr) {
			if (cur->username == username) {
				if (cur->password != password) {
					
					do {
						cout << "Invalid password, please re-enter again (0 to exit)" << endl;
						cout << ">> ";
						cin >> password;
					} while (password != cur->password && password != "0");
					if (password == "0") {
						cout << "Cancelled Login" << endl;
						system("pause");
						return false;
					}
				}
				toStaff = cur;
				cout << "Login successful" << endl;
				system("pause");
				return true;
			}
			cur = cur->nextAccount;
		}
		if (cur == nullptr) {
			cout << "Username not found, please try again" << endl;
			system("pause");
		}
	} while (true);
	return false;
}