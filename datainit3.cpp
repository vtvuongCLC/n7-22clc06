#include<iostream>
#include<string>
#include"header.h"
#include"datainit.h"

using namespace std;

int login(Schoolyear user){
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
        do{
            cout<<"ID: ";
            cin>>id;
            while(user.listClass!=nullptr){
                while(user.listClass->listStudent!=nullptr){
                    if(user.listClass->listStudent->dInfo.StudentID==id){
                        return 1;
                    }
                    user.listClass->listStudent=user.listClass->listStudent->nextStudent;           
                }
                user.listClass=user.listClass->nextClass;
            }
        }
        while(true);
        break;
    }
    case 2:
        break;
    default:
        return 0;
    }
}
