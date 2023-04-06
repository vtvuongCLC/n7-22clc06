#include "header/datafunction.h"
#include "header/ultilityfunction.h"

bool IsemptyFile(string fileName)
{
    bool result = false;
    ifstream test;
    test.open("Data\\" + fileName + ".txt");
    if (test.is_open() == false) {
        result = true;
    }
    else {
        string temp;
        getline(test,temp,'\n');
        if (temp.empty() == true)
            result = true;                    
    }
    test.close();
    return result;
}

void LoadYearFromFile(string YearFile, Schoolyear* &listYear, int &numYear)
{
    if (IsemptyFile(YearFile) == true)
        return;
    ifstream YearIn;
    YearIn.open("Data\\" + YearFile + ".txt");
    Schoolyear* curYear = nullptr;
    while (YearIn.eof() == false) {
        string tempData;
        getline(YearIn,tempData,'\n');
        if (tempData.empty() == false) {
            if (listYear == nullptr) {
                listYear = new Schoolyear;
                curYear = listYear;
            } else {
                curYear->nextYear = new Schoolyear;
                curYear = curYear->nextYear;
            }
            numYear++;
            curYear->year = tempData;
        }
    }
    YearIn.close();
}
void LoadClassFromfile(string yearName, StudyClass* &listClass, int &numClass)
{
    if (IsemptyFile(yearName+"StdyCls") == true)
        return;
    ifstream ClassIn;
    ClassIn.open("Data\\" + yearName + "StdyCls.txt");
    StudyClass* curClass = nullptr;
    while (ClassIn.eof() == false) {
        string tempClass;
        getline(ClassIn,tempClass,'\n');
        if (tempClass.empty() == false) {
            if (listClass == nullptr) {
                listClass = new StudyClass;
                curClass = listClass;
            } else {
                curClass->nextClass = new StudyClass;
                curClass = curClass->nextClass;
            }
            numClass++;
            curClass->className = tempClass; 
        }
    }
    ClassIn.close();
}
void LoadStudentListFromFile(string yearName, string className, Student* &listStudent, int &numStudent)
{
    if (IsemptyFile(className) == true)
        return;
    ifstream StudentIn;
    StudentIn.open("Data\\" + className + "StdyCls.txt");
    Student* curStudent = nullptr;
    while (StudentIn.eof() == false) {
        string tempData;
        getline(StudentIn,tempData,',');
        if (tempData.empty() == false) {
            if (listStudent == nullptr) {
                listStudent = new Student;
                curStudent = listStudent;
            } else {
                curStudent->nextStudent = new Student;
                curStudent = curStudent->nextStudent;
            }
            numStudent++;
            curStudent->yearName = yearName;
            curStudent->className = className;
            curStudent->dInfo.StudentID = tempData;
            getline(StudentIn,curStudent->password,',');
            getline(StudentIn,curStudent->dInfo.FirstName,',');
            getline(StudentIn,curStudent->dInfo.LastName,',');
            getline(StudentIn,curStudent->dInfo.Gender,',');
            getline(StudentIn,tempData,'/');
            curStudent->dInfo.Birth.day = stoi(tempData);
            getline(StudentIn,tempData,'/');
            curStudent->dInfo.Birth.month = stoi(tempData);
            getline(StudentIn,tempData,',');
            curStudent->dInfo.Birth.year = stoi(tempData);
            getline(StudentIn,curStudent->dInfo.SocialID,'\n');
        }
    }
    StudentIn.close();
}
void LoadSchoolData(DataBase &DB)
{   
    LoadYearFromFile(DB.YearFile,DB.YearList,DB.numYear);
    Schoolyear* curYear = DB.YearList;
    StudyClass* curClass = nullptr;

    while (curYear != nullptr) {
        LoadClassFromfile(curYear->year,curYear->listClass,curYear->numClass);
        curClass = curYear->listClass;
        while (curClass != nullptr) {
            LoadStudentListFromFile(curYear->year, curClass->className,curClass->listStudent,curClass->numStudent);
            curClass = curClass->nextClass;
        }
        curYear = curYear->nextYear;
    }
}

void LoadSemesterFromFile(string SemesterFile, Semester* &listSemester)
{
    if (IsemptyFile(SemesterFile) == true)
        return;
    ifstream SemesterIn;
    SemesterIn.open("Data\\" + SemesterFile + ".txt");
    Semester* curSem = nullptr;
    while (SemesterIn.eof() == false) {
        string tempData;
        getline(SemesterIn,tempData,',');
        if (tempData.empty() == false) {
            if (listSemester == nullptr) {
                listSemester = new Semester;
                curSem = listSemester;
            } else {
                curSem->nextSemester = new Semester;
                curSem = curSem->nextSemester;
            }
            curSem->year = tempData;
            getline(SemesterIn,tempData,',');
            curSem->semester = stoi(tempData);
            getline(SemesterIn,tempData,',');
            curSem->start = tempData;
            getline(SemesterIn,tempData,'\n');
            curSem->end = tempData;
        }
    }
    SemesterIn.close();
}
void LoadCourseInfoFromFile(Semester* curSemester)
{
    string fileName = curSemester->year;
    fileName += '_' + ('0' + curSemester->semester);
    if (IsemptyFile(fileName) == true)
        return;
    ifstream CourseInfoIn;
    CourseInfoIn.open("Data\\" + fileName + "_CourseInfo.txt");;
    Course* curCourse = nullptr;
    while (CourseInfoIn.eof() == false) {
        string tempData;
        getline(CourseInfoIn,tempData,',');
        if (tempData.empty() == false) {
            if (curSemester->CourseList == nullptr) {
                curSemester->CourseList = new Course;
                curCourse = curSemester->CourseList;
            } else {
                curCourse->nextCourse = new Course;
                curCourse->nextCourse->prevCourse = curCourse;
                curCourse = curCourse->nextCourse;
            }
            curCourse->thisCourseInfo.courseID = tempData;
            getline(CourseInfoIn,tempData,',');
            curCourse->thisCourseInfo.courseName = tempData;
            getline(CourseInfoIn,tempData,',');
            curCourse->thisCourseInfo.className = tempData;
            getline(CourseInfoIn,tempData,',');
            curCourse->thisCourseInfo.Teacher = tempData;
            getline(CourseInfoIn,tempData,',');
            curCourse->thisCourseInfo.credit = stoi(tempData);
            getline(CourseInfoIn,tempData,',');
            curCourse->thisCourseInfo.maxStudent = stoi(tempData);
            getline(CourseInfoIn,tempData,',');
            curCourse->thisCourseInfo.CourseDate.day = tempData;
            getline(CourseInfoIn,tempData,'\n');
            curCourse->thisCourseInfo.CourseDate.session = tempData;
        }
    }
    CourseInfoIn.close();
}
void LoadCourseStudentFromFile(Course* aCourse, Schoolyear** quickPtr)
{
    string fileName = aCourse->thisCourseInfo.courseID + '_' + aCourse->thisCourseInfo.className;
    if (IsemptyFile(fileName) == true)
        return;
    ifstream CourseStudentIn;
    CourseStudentIn.open("Data\\" + fileName + ".txt");
    CourseStudent* curCourseStudent = nullptr;
    while (CourseStudentIn.eof() == false) {
        string tempData;
        getline(CourseStudentIn,tempData,',');
        if (tempData.empty() == false) {
            if (aCourse->listStudent == nullptr) {
                aCourse->listStudent = new CourseStudent;
                curCourseStudent = aCourse->listStudent;
            } else {
                curCourseStudent->nextStudent = new CourseStudent;
                curCourseStudent->nextStudent->prevStudent = curCourseStudent;
                curCourseStudent = curCourseStudent->nextStudent;
            }
            curCourseStudent->yearIndex = stoi(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->classIndex = stoi(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->studentIndex = stoi(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->savedScore.midtermMark = stod(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->savedScore.finalMark = stod(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->savedScore.otherMark = stod(tempData);
            getline(CourseStudentIn,tempData,'\n');
            curCourseStudent->savedScore.totalMark = stod(tempData);

            curCourseStudent->ptoStudent = quickPtr[curCourseStudent->yearIndex]->quickClassPtr[curCourseStudent->classIndex]->quickStudentPtr[curCourseStudent->studentIndex];
            Student* curStudent = curCourseStudent->ptoStudent;
            if(!curStudent->lastEnrolledCourse){
                curStudent->CourseList = new EnrolledCourse;
                curStudent->lastEnrolledCourse = curStudent->CourseList;
            }
            else {
                curStudent->lastEnrolledCourse->nextCourse = new EnrolledCourse;
                curStudent->lastEnrolledCourse->nextCourse->prevCourse = curStudent->lastEnrolledCourse;
                curStudent->lastEnrolledCourse = curStudent->lastEnrolledCourse->nextCourse;
            }
            curStudent->lastEnrolledCourse->ptoCourse = aCourse;
            curStudent->lastEnrolledCourse->Score = &(curCourseStudent->savedScore);
        }
    }
}
void LoadSemesterSector(DataBase &DB)
{
    if (DB.SemesterList != nullptr)
        return;
    Semester* curSem = nullptr;
    Course* curCourse = nullptr;
    LoadSemesterFromFile(DB.SemesterFile,DB.SemesterList);
        curSem = DB.SemesterList;
        while (curSem != nullptr) {
            LoadCourseInfoFromFile(curSem);
            curCourse = curSem->CourseList;
            while (curCourse != nullptr) {
                LoadCourseStudentFromFile(curCourse,DB.quickSchoolPtr);
                curCourse = curCourse->nextCourse;
            }
            curSem = curSem->nextSemester;
        }
}

void SaveYearToFile(string YearFile, Schoolyear* ListYear)
{
    ofstream out;
    out.open("Data\\" + YearFile + ".txt");
    while (ListYear != nullptr) {
        out << ListYear->year << endl;
        ListYear = ListYear->nextYear;
    }
    out.close();
}
void SaveClassToFile(string yearName, StudyClass* listClass)
{
    ofstream out;
    out.open("Data\\" + yearName + "StdyCls.txt");
        while (listClass != nullptr) {
            out << listClass->className << endl;
            listClass = listClass->nextClass;
        }
        out.close();
}
void SaveStudentListToFile(string className, Student* listStudent)
{
    ofstream out;
    out.open("Data\\" + className + "StdyCls.txt");
    while (listStudent != nullptr) {
        out << listStudent->dInfo.StudentID << ',';
        out << listStudent->password << ',';
        out << listStudent->dInfo.FirstName << ',';
        out << listStudent->dInfo.LastName << ',';
        out << listStudent->dInfo.Gender << ',';
        out << listStudent->dInfo.Birth.day << '/';
        out << listStudent->dInfo.Birth.month << '/';
        out << listStudent->dInfo.Birth.year << ',';
        out << listStudent->dInfo.SocialID << endl;
        listStudent = listStudent->nextStudent;
    }
    out.close();
}

void SaveCourseStudentToFile(Course* aCourse)
{
    ofstream out;
    out.open("Data\\" + aCourse->thisCourseInfo.courseID + '_' + aCourse->thisCourseInfo.className + ".txt");
    CourseStudent* curStudent = aCourse->listStudent;
    Scoreboard thisCourseBoard;
    while (curStudent != nullptr) {
        out << curStudent->yearIndex << ',';
        out << curStudent->classIndex << ',';
        out << curStudent->studentIndex << ',';
        out << thisCourseBoard.midtermMark << ',';
        out << thisCourseBoard.finalMark << ',';
        out << thisCourseBoard.otherMark << ',';
        out << thisCourseBoard.totalMark << endl;
        curStudent = curStudent->nextStudent;
    }
    out.close();
}
void SaveCourseInfoToFile(Semester* curSemester)
{
    ofstream out;
    string fileName = curSemester->year;
    fileName += '_'+ "HK" + ('0' + curSemester->semester);
    out.open("Data\\" + fileName + "_CourseInfo.txt");
    Course* curCourse = curSemester->CourseList;
    while (curCourse != nullptr) {
        out << curCourse->thisCourseInfo.courseID << ',';
        out << curCourse->thisCourseInfo.courseName << ',';
        out << curCourse->thisCourseInfo.className << ',';
        out << curCourse->thisCourseInfo.Teacher << ',';
        out << curCourse->thisCourseInfo.credit << ',';
        out << curCourse->thisCourseInfo.maxStudent << ',';
        out << curCourse->thisCourseInfo.CourseDate.day << ',';
        out << curCourse->thisCourseInfo.CourseDate.session << endl;
        curCourse = curCourse->nextCourse;
    }
    out.close();
    
}
void SaveSemesterToFile(string SemesterFile, Semester* listSemester)
{
    ofstream out;
    out.open("Data\\" + SemesterFile + ".txt");
    while (listSemester != nullptr) {
        out << listSemester->year << ',';
        out << listSemester->semester << ',';
        out << listSemester->start << ',';
        out << listSemester->end << endl;
        listSemester = listSemester->nextSemester;
    }
    out.close();
}

// void SaveData(DataBase DB)
// {
//     if (DB.YearList != nullptr) {
//         SaveYearToFile(DB.YearFile,DB.YearList);
//         Schoolyear* curYear = DB.YearList;
//         StudyClass* curClass = nullptr;
        
//         while (curYear != nullptr) {
//             SaveClassToFile(curYear->year,curYear->listClass);
//             curClass = curYear->listClass;
//             while (curClass != nullptr) {
//                 SaveStudentListToFile(curClass->className,curClass->listStudent);
//                 curClass = curClass->nextClass;
//             }
//             curYear = curYear->nextYear;
//         }
//     }

//     if (DB.SemesterList != nullptr)
//     {
//         SaveSemesterToFile(DB.SemesterFile, DB.SemesterList);
//         Semester* curSemester = DB.SemesterList;
//         Course* curCourse = nullptr;

//         while (curSemester != nullptr) {
//             SaveCourseInfoToFile(curSemester);
//             curCourse = curSemester->CourseList;
//             while (curCourse != nullptr) {
//                 SaveCourseStudentToFile(curCourse);
//                 curCourse = curCourse->nextCourse;
//             }
//             curSemester = curSemester->nextSemester;
//         }
//     }


// }
void ClearData(DataBase &DB)
{
    Semester* curSemester = nullptr;
    Course* curCourse = nullptr;
    CourseStudent* curCourseStudent = nullptr;
    while (DB.SemesterList != nullptr) {
            curSemester = DB.SemesterList;
            while (curSemester->CourseList != nullptr) {
                curCourse = curSemester->CourseList;
                while (curCourse->listStudent != nullptr) {
                    curCourseStudent = curCourse->listStudent;
                    curCourse->listStudent = curCourseStudent->nextStudent; 
                    delete curCourseStudent;
                }
                curSemester->CourseList = curCourse->nextCourse;
                delete curCourse;
            }
            DB.SemesterList = curSemester->nextSemester;
            delete curSemester;
    }

    Schoolyear* curYear = nullptr;
    StudyClass* curClass = nullptr;
    Student* curStudent = nullptr;
    EnrolledCourse* curEnrolCourse = nullptr;
    delete []DB.quickSchoolPtr;
    DB.quickSchoolPtr = nullptr;
    while (DB.YearList != nullptr) {
        curYear = DB.YearList;
        delete []curYear->quickClassPtr;
        curYear->quickClassPtr = nullptr;
        while (curYear->listClass != nullptr) {
            curClass = curYear->listClass;
            delete []curClass->quickStudentPtr;
            curClass->quickStudentPtr = nullptr;
            while (curClass->listStudent != nullptr) {
                curStudent = curClass->listStudent;
                curClass->listStudent = curStudent->nextStudent;
                while (curStudent->CourseList != nullptr) {
                    curEnrolCourse = curStudent->CourseList;
                    curStudent->CourseList = curEnrolCourse->nextCourse;
                    delete curEnrolCourse;
                }
                delete curStudent;
            }
            curYear->listClass = curClass->nextClass;
            delete curClass;
        }
        DB.YearList = curYear->nextYear;
        delete curYear;
    }

}

