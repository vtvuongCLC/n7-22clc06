#ifndef _UPDATE_SCORE_
#define _UPDATE_SCORE_


#include"structlist.h"
#include"displayfunction.h"
#include<iostream>
#include<fstream>
using namespace std;
void ChangeScoreStudent(Scoreboard* &pScore);
Student* FindUpdateStudent(Course *pCourse,string idStudent);
bool FindUpdateCourse(EnrolledCourse *pcourse,string id);
void UpdateScoreStudent(Course* pCourse,int semester, string year);

#endif