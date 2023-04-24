#include "header/displayfunction.h"
#include "header/loginfunction.h"
#include "header/studentui.h"
#include "header/ultilityfunction.h"
#include "header/datafunction.h"

void StudentUI(Student *curStudent, StudyClass* curStudyClass, DataBase DB){
    int selection;
    while (true)
    {
        system("cls");
        cout << "1. View profile info" << endl;
        cout << "2. Change password" << endl;
        cout << "3. View enrolled courses and scoreboard" << endl;
        cout << "0. Back" << endl
             << endl;
        cout << ">> ";
        cin >> selection;
        switch (selection)
        {
        case 0:
            return;
        case 1:
            DisplayInfoStudent(curStudent);
            system("pause");
            break;
        case 2:
            ChangePasswordStudent(curStudent);
            SaveStudentListToFile(curStudyClass->className, curStudyClass->listStudent);
            system("pause");
            break;
        case 3:
            while (true)
            {
                int maxChoice = 0, choice;
                system("cls");
                cout << "Choose the year to view enrolled courses and scoreboard" << endl
                     << endl;
                cout << "List of years:" << endl;
                DisplayYearList(DB.YearList, maxChoice);
                cout << "0. Back" << endl
                     << ">> ";
                cin >> choice;
                if (choice == 0)
                    break;
                if (choice > 0 && choice <= maxChoice)
                {
                        Schoolyear *chosenYear = navigateYear(DB.YearList, choice);
                        Semester **handlingArr = nullptr;
                    while(true){
                        system("cls");
                        cout << "Choose the semester of year " << chosenYear->year << " to view enrolled courses and scoreboard" << endl << endl;
                        cout << left << setw(10) << "Index";
                        cout << left << setw(10) << "Semester";
                        cout << left << setw(10) << "Start";
                        cout << left << setw(10) << "End";
                        cout << endl;
                        if (DisplaySemesterList(DB.SemesterList, handlingArr, chosenYear->year, maxChoice) == false){
                            cout << "No semesters found." << endl;
                            system("pause");
                            break;
                        }
                        cout << endl;
                        cout << "0. Back" << endl
                             << ">> ";
                        cin >> choice;
                        if (choice == 0)
                            break;
                        if (choice > 0 && choice <= maxChoice){
                            Semester* chosenSemester = handlingArr[choice - 1];
                            while (true){
                                system("cls");
                                cout << "Year: " << chosenYear->year << endl;
                                cout << "Semester: " << chosenSemester->semester << endl;
                                cout << "1. View enrolled courses" << endl;
                                cout << "2. View scoreboard" << endl;
                                cout << "0. Back" << endl
                                     << ">> ";
                                cin >> choice;
                                if (choice == 0) break;
                                if(choice == 1) DisplayCourseList1Student(curStudent, chosenSemester->semester, chosenYear->year);
                                if(choice == 2) DisplayScoreboard1Student(curStudent, chosenSemester->semester, chosenYear->year);
                                system("pause");
                            }
                        }
                    }
                }
            }
            break;
        }
    }
}