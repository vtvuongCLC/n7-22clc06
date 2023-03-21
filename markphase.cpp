#include "header.h"
#include <fstream>
#include <iostream>

using namespace std;

void ExportCourseList(Course* inputCourse)
{
    if (inputCourse->enroll_List == nullptr)
        return;
    ofstream outData;
    outData.open(inputCourse->courseName+".csv");
    CourseStudent* curStudent = inputCourse->enroll_List;
    outData << "No,StudentID,FirstName,LastName,Midterm,Final,OtherMark,Total" << endl; 
    while (curStudent != nullptr) {
        outData << curStudent->No << ',';
        outData << curStudent->StudentID << ',';
        outData << curStudent->FirstName << ',';
        outData << curStudent->LastName << ',';
        outData << curStudent->Midterm << ',';
        outData << curStudent->Final << ',';
        outData << curStudent->OtherMark << ',';
        outData << curStudent->Total << endl;
        curStudent = curStudent->nextStudent;
    }
    outData.close();
}