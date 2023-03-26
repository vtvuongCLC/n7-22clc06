#ifndef _DATAINIT_H
#define _DATAINIT_H
#include<iostream>
#include"header.h"
using namespace std;

bool pass_student(Student* user,string &pass);
bool login_student(string &id,string &pass, Student* user);
int login(Student* user);
bool login_staff(string AccountStaff,string passStaff);
#endif