#include<iostream>
#include<string>
#include"header.h"
#include"datainit3.h"

using namespace std;

bool pass_student(Student* user,string &pass){
    if(user->password!=pass){ 
        cout<<"Wrong password!. Please try again."<<endl;
        cout<<"password: ";
        cin>>pass;
        return pass_student(user,pass);
    }
    return true;   
}

bool login_student(string &id,string &pass, Student* user){
    Student *tmp= user;
    while(tmp!=nullptr){
        if(tmp->dInfo.StudentID==id){
            if(pass_student(tmp,pass)) return true;
        } 
        tmp=tmp->nextStudent;
    };
    cout<<"Wrong student id, please try again"<<endl;
    cout<<"ID: ";
    cin>>id;
    return login_student(id,pass,user);
}

int login(Student* user){
    int tmp;
    cout<<"You are :"<<endl;
    cout<<"1. Student:"<<endl;
    cout<<"2. Staff:"<<endl;
    cout<<"Press another number to exit"<<endl;
    cout<<"Your choose: ";
    cin>>tmp;
    switch(tmp)
    {
    case 1:
    {
        string id;
        string pass;
        do{
            cout<<"ID: ";
            cin>>id;
            cout<<"password: ";
            cin>>pass; 
        }
        while(login_student(id,pass,user));
        cout<<"Successful to login"<<endl;
        return 1;
    }
    case 2:

        return 2;
    default:
        return 0;
    }
}