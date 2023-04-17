#include "header/displayfunction.h"
#include "header/loginfunction.h"
#include "header/studentui.h"

void StudentUI(Student* curStudent, DataBase DB){
    int selection;
    while(true){
        system("cls");
        cout << "1. View profile info" << endl;
        cout << "2. Change password" << endl;
        cout << "3. View enrolled courses" << endl;
        cout << "4. View scoreboard" << endl;
        cout << "0. Back" << endl << endl;
        cout << ">> "; cin >> selection;

        switch(selection){
            case 0: return;
            case 1:
                DisplayInfoStudent(curStudent);
                break;
            case 2:
                ChangePasswordStudent(curStudent);
                break;
            case 3:
                
                break;
            case 4:

                break;
        }
    }
}