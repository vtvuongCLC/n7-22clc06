#include "header.h"

void getInfo(Info &student, ifstream& ifs){
    getline(ifs, student.StudentID, ',');
    getline(ifs, student.FirstName, ',');
    getline(ifs, student.LastName, ',');
    string gender;
    getline(ifs, gender, ',');
    if(gender == "male") student.isMale = true;
    else student.isMale = false;
    ifs >> student.Birth.day;
    ifs.ignore(1);
    ifs >> student.Birth.month;
    ifs.ignore(1);
    ifs >> student.Birth.year;
    getline(ifs, student.SocialID);
}

void getStudent(StudyClass &ClassToAdd){
    ifstream ifs;
    ifs.open("getStudent.csv");
    if(!ifs.is_open()) {
        cout << "Not found this find!!!\n";
        return;        
    }
    while(!ifs.eof()){
    Student* cur = ClassToAdd.pStudent;
    ClassToAdd.pStudent = new Student;
    ClassToAdd.pStudent->nextStudent = cur;
    ClassToAdd.pStudent->mainClass = ClassToAdd.nameStudyClass;
    ifs >> ClassToAdd.pStudent->No;
    getInfo(ClassToAdd.pStudent->This_Student, ifs);
    }
}