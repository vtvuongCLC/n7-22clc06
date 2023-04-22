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
            {   
                char choice ;
                EnrolledCourse* curListCourse = curStudent->lastEnrolledCourse;
                int semester= curListCourse->ptoCourse->semester;
                string year= curListCourse->ptoCourse->year;
                DisplayCourseList1Student(curStudent, semester,year);
                while(curListCourse->ptoCourse!=nullptr){
                    bool display = false;
                    if(semester!=curListCourse->ptoCourse->semester){
                        display=true;
                        semester=curListCourse->ptoCourse->semester;
                    }
                    if(year!=curListCourse->ptoCourse->year){
                        display=true;
                        year=curListCourse->ptoCourse->year;
                    }
                    if(display){
                        cout<<"See More List Courses in another semester or year[Y/N]: ";
                        cin>>choice;
                        if(choice=='y' || choice=='Y')
                            DisplayCourseList1Student(curStudent, semester,year);
                        else break;
                    }
                    curListCourse=curListCourse->prevCourse;    
                }
                break;
            }
            case 4:
            {    
                char choice ;
                EnrolledCourse* curListCourse = curStudent->lastEnrolledCourse;
                int semester= curListCourse->ptoCourse->semester;
                string year= curListCourse->ptoCourse->year;
                DisplayCourseList1Student(curStudent, semester,year);
                while(curListCourse->ptoCourse!=nullptr){
                    bool display= false;
                    if(semester!=curListCourse->ptoCourse->semester){
                        display=true;
                        semester=curListCourse->ptoCourse->semester;
                    }
                    if(year!=curListCourse->ptoCourse->year){
                        display=true;
                        year=curListCourse->ptoCourse->year;
                    }
                    if(display){
                        cout<<"See More Score board in another semester or year[Y/N]: ";
                        cin>>choice;
                        if(choice=='y' || choice=='Y')
                            DisplayScoreboard1Student(curStudent, semester,year);
                        else break;
                    }
                    curListCourse=curListCourse->prevCourse;    
                }
                break;
            }
        }
    }
}