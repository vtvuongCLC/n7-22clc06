#include"header/viewScore.h"


void ChangeScoreStudent(Scoreboard* &pScore){
    int choise;
    do{
        cout<<"Which of Score Updating: "<<endl;
        cout<<"1. Total Score"<<endl;
        cout<<"2. Other Score"<<endl;
        cout<<"3. Midterm Score"<<endl;
        cout<<"4. Final Score"<<endl;
        cout<<"5. Exit"<<endl;
        switch(choise){
            case 1:
                cout<<"Total Score: ";
                cin>>pScore->totalMark;
                break;
            case 2:    
                cout<<"Other Score: ";
                cin>>pScore->otherMark;
                break;
            case 3:
                cout<<"Score midterm: ";
                cin>>pScore->midtermMark;
                break;
            case 4:
                cout<<"Score final: ";
                cin>>pScore->finalMark;
                break;
        }
    }while(choise==5);
}


Student* FindUpdateStudent(Course *pCourse,string idStudent){
    while(pCourse->listStudent->ptoStudent){
        if(pCourse->listStudent->ptoStudent->dInfo.StudentID==idStudent) break;
        pCourse->listStudent->ptoStudent=pCourse->listStudent->ptoStudent->nextStudent;
    }
    return pCourse->listStudent->ptoStudent;
}

bool FindUpdateCourse(EnrolledCourse *pcourse,string id){
    while(pcourse){
        if(pcourse->ptoCourse->thisCourseInfo.courseID==id) return true;
        pcourse=pcourse->nextCourse;
    }
    return false;
}

void UpdateScoreStudent(Course* pCourse,int semester, string year){
    cout<<"Update Score Student!"<<endl;
    cout<<"=================================="<<endl;
    string idStudent;
    Student* tmpStudent;
    do{
        cout<<"Enter ID Student Update Score: ";
        cin>>idStudent;
        while(pCourse){
            if(pCourse->semester==semester && pCourse->year==year){
                tmpStudent= FindUpdateStudent(pCourse,idStudent);
                if(tmpStudent!=nullptr) break;
            }
            pCourse=pCourse->nextCourse;
        }
    }while(tmpStudent!=nullptr);
    cout<<"=================================="<<endl;
    cout<<"Score Board of this Student "<<endl;
    DisplayScoreboard1Student(tmpStudent,semester,year);
    cout<<"=================================="<<endl;
    cout<<"UPDATING STUDENT SCORE"<<endl;
    int tmp;
    do{
            string CourseID;
            cout<<"ID of Course updating: ";
            cin>>CourseID;
        do{
            if(FindUpdateCourse(tmpStudent->CourseList,CourseID)) 
                ChangeScoreStudent(tmpStudent->CourseList->Score);
        }while(!FindUpdateCourse(tmpStudent->CourseList,CourseID));
        cout<<"UPDATE SUCCESSFUL"<<endl;
        cout<<"PRESS 1 TO UPDATE OTHER COURSE"<<endl;
        cout<<"PRESS ANY NUMBER TO EXIT"<<endl;
        cout<<"Your choise: ";
        cin>>tmp;
    }while(tmp!=1);
}