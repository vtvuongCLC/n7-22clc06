#include "header/datafunction.h"
#include "header/loginfunction.h"
#include "header/staffui.h"
#include "header/studentui.h"

int main()
{
    string YearFile = "Listyear";
    DataBase DB;
    StaffAccount* staffList = nullptr;
    LoadStaffData(staffList);
    LoadSchoolData(DB);
    LoadSemesterSector(DB);

    char usertype;
    
    do {
        usertype = -9;
        system("cls");
        cout << "Courses Management System" << endl;
        cout << "Login Menu"                << endl;
        cout << "You are :"                 << endl;
        cout << "1. Student"                << endl;
        cout << "2. Staff"                  << endl;
        cout << "0. Exit Program"           << endl;
        cout << ">> ";
        cin >> usertype;
        if (usertype == '0') {
            char exit;
            cout << "Exit program ? (y/n) >> ";
            cin >> exit;
            if (exit == 'y' || exit == 'Y')
                break;
        }
            
        if (usertype == '1') {
            StudyClass* toStudyClass = nullptr;
            Student* toStudent = nullptr;
            if (login_student(DB.YearList,toStudent,toStudyClass) == true) 
                StudentUI(toStudent,toStudyClass,DB);
        }
        if (usertype == '2') {
            StaffAccount* toStaff = nullptr;
            if (login_staff(staffList,toStaff) == true)
                StaffUI(DB,toStaff,staffList);
        }
    } while (true);
    
    cout << "Closing program..." << endl;
    cout << "Cleaning data..." << endl;
    ClearStaffList(staffList);
    ClearData(DB);
    system("pause");
}