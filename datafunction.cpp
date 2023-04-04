#include "header/datafunction.h"


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

void LoadYearFromFile(string YearFile, Schoolyear* &listYear)
{
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
            curYear->year = tempData;
        }
    }
    YearIn.close();
}
void LoadClassFromfile(string yearName, StudyClass* &listClass, int &numClass)
{
    if (IsemptyFile(yearName) == true)
        return;
    ifstream ClassIn;
    ClassIn.open("Data\\" + yearName + "StdyCls.txt");
    StudyClass* curClass = nullptr;
    numClass = 0;
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
    numStudent = 0;
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
            curStudent->No = stoi(tempData);
            getline(StudentIn,tempData,',');
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
void LoadSemesterFromFile(string yearName, Semester* &listSemester)
{
    if (IsemptyFile(yearName+"Semester") == true)
        return;
    ifstream SemesterIn;
    SemesterIn.open("Data\\" + yearName + "Semester.txt");
    Semester* curSem = nullptr;
    int i = 0;
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
            i++;
            curSem->semester = tempData;
            getline(SemesterIn,tempData,',');
            curSem->start = tempData;
            getline(SemesterIn,tempData,'\n');
            curSem->end = tempData;
            curSem->index = i;
        }
    }
    SemesterIn.close();
}
void LoadCourseInfoFromFile(Course* &aCourse, string semester, string start, string end)
{
    if (IsemptyFile(semester + '_' + start + '-' + end + "Semester") == true)
        return;
    ifstream CourseInfoIn;
    CourseInfoIn.open("Data\\" + semester + '_' + start + '-' + end + "Semester.txt");
    Course* curCourse = nullptr;
    while (CourseInfoIn.eof() == false) {
        string tempData;
        getline(CourseInfoIn,tempData,',');
        if (tempData.empty() == false) {
            if (curCourse == nullptr) {
                aCourse = new Course;
                curCourse = aCourse;
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
void LoadCourseStudentFromFile(CourseStudent* &listStudent, string CourseID, string className)
{
    if (IsemptyFile(CourseID + '_' + className) == true)
        return;
    ifstream CourseStudentIn;
    CourseStudentIn.open("Data\\" + CourseID + '_' + className + ".txt");
    CourseStudent* curCourseStudent = nullptr;
    while (CourseStudentIn.eof() == false) {
        string tempData;
        getline(CourseStudentIn,tempData,',');
        if (tempData.empty() == false) {
            if (listStudent == nullptr) {
                listStudent = new CourseStudent;
                curCourseStudent = listStudent;
            } else {
                curCourseStudent->nextStudent = new CourseStudent;
                curCourseStudent->nextStudent->prevStudent = curCourseStudent;
                curCourseStudent = curCourseStudent->nextStudent;
            }
            curCourseStudent->classIndex = stoi(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->studentIndex = stoi(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->savedScore->midtermMark = stod(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->savedScore->finalMark = stod(tempData);
            getline(CourseStudentIn,tempData,',');
            curCourseStudent->savedScore->otherMark = stod(tempData);
            getline(CourseStudentIn,tempData,'\n');
            curCourseStudent->savedScore->totalMark = stod(tempData);
        }
    }
}
void LoadData(DataBase &DB, string YearFile)
{   
    if (IsemptyFile(YearFile) == true)
        return;
    LoadYearFromFile(YearFile,DB.YearList);
    Schoolyear* curYear = DB.YearList;
    StudyClass* curClass = nullptr;
    Semester* curSem = nullptr;
    Course* curCourse = nullptr;
    while (curYear != nullptr) {
        LoadClassFromfile(curYear->year,curYear->listClass,curYear->numClass);
        curClass = curYear->listClass;
        while (curClass != nullptr) {
            LoadStudentListFromFile(curYear->year, curClass->className,curClass->listStudent,curClass->numStudent);
            curClass = curClass->nextClass;
        }
        // LoadSemesterFromFile(curYear->year,cu);
        // curSem = curYear->SemesterList;
        // while (curSem != nullptr) {
        //     LoadCourseInfoFromFile(curSem->CourseList,curSem->semester,curSem->start,curSem->end);
        //     curCourse = curSem->CourseList;
        //     while (curCourse != nullptr) {
        //         LoadCourseStudentFromFile(curCourse->listStudent,curCourse->thisCourseInfo.courseID,curCourse->thisCourseInfo.className);
        //         curCourse = curCourse->nextCourse;
        //     }
        //     curSem = curSem->nextSemester;
        // }
        curYear = curYear->nextYear;
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
        out << listStudent->No << ',';
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
void SaveSemesterToFile(string yearName, Semester* listSem)
{
    ofstream out;
    out.open("Data\\" + yearName + "Semester.txt");
    while (listSem != nullptr) {
        out << listSem->semester << ',' << listSem->start << ',' << listSem->end << endl;
        listSem = listSem->nextSemester;
    }
    out.close();
}
bool findStudentScoreBoard(EnrolledCourse* enrolledlist, Course* curCourse, Scoreboard result)
{
    while (enrolledlist != nullptr) {
        if (enrolledlist->ptoCourse == curCourse) {
            result = enrolledlist->Score;
            return true;
        }
        else
            enrolledlist = enrolledlist->nextCourse;
    }
    return false;
}
void SaveCourseStudentToFile(Course* aCourse)
{
    ofstream out;
    out.open("Data\\" + aCourse->thisCourseInfo.courseID + '_' + aCourse->thisCourseInfo.className + ".txt");
    CourseStudent* curStudent = aCourse->listStudent;
    Scoreboard thisCourseBoard;
    while (curStudent != nullptr) {
        out << curStudent->classIndex << ',';
        out << curStudent->studentIndex << ',';
        if (findStudentScoreBoard(curStudent->ptoStudent->CourseList,aCourse,thisCourseBoard) == true) {
            out << thisCourseBoard.midtermMark << ',';
            out << thisCourseBoard.finalMark << ',';
            out << thisCourseBoard.otherMark << ',';
            out << thisCourseBoard.totalMark;
        } else {
            out << "0,0,0,0";
        }
        cout << endl;
        curStudent = curStudent->nextStudent;
    }
    out.close();
}
void SaveCourseInfoToFile(Semester* curSem)
{
    ofstream out;
    out.open("Data\\" + curSem->semester + '_' + curSem->start + '-' + curSem->end + "Semester.txt");
    Course* curCourse = curSem->CourseList;
    
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
void SaveData(string YearFile, Schoolyear* ListYear)
{
    SaveYearToFile(YearFile,ListYear);
    Schoolyear* curYear = ListYear;
    StudyClass* curClass = nullptr;
    Semester* curSem = nullptr;
    Course* curCourse = nullptr;

    while (curYear != nullptr) {
        SaveClassToFile(curYear->year,curYear->listClass);
        // SaveSemesterToFile(curYear->year, curYear->SemesterList);
        curClass = curYear->listClass;
        while (curClass != nullptr) {
            SaveStudentListToFile(curClass->className,curClass->listStudent);
            curClass = curClass->nextClass;
        }
        // curSem = curYear->SemesterList;
        // while (curSem != nullptr)
        // {
        //     SaveCourseInfoToFile(curSem);
        //     curCourse = curSem->CourseList;
        //     while (curCourse != nullptr) {
        //         SaveCourseStudentToFile(curCourse);
        //     }
        // }
        curYear = curYear->nextYear;
    }
}
void ClearData(Schoolyear* &listYear)
{
    Schoolyear* curYear = nullptr;
    StudyClass* curClass = nullptr;
    Student* curStudent = nullptr;
    Semester* curSem = nullptr;
    Course* curCourse = nullptr;
    CourseStudent* curCourseStudent = nullptr;
    while (listYear != nullptr) {
        curYear = listYear;
        delete []curYear->quickClassPtr;
        curYear->quickClassPtr = nullptr;
        while (curYear->listClass != nullptr) {
            curClass = curYear->listClass;
            delete []curClass->quickStudentPtr;
            curClass->quickStudentPtr = nullptr;
            while (curClass->listStudent != nullptr) {
                curStudent = curClass->listStudent;
                curClass->listStudent = curStudent->nextStudent;
                delete curStudent;
                curStudent = nullptr;
            }
            curYear->listClass = curClass->nextClass;
            delete curClass;
            curClass = nullptr;  
        }
        // while (curYear->SemesterList != nullptr) {
        //     curSem = curYear->SemesterList;
        //     while (curSem->CourseList != nullptr) {
        //         curCourse = curSem->CourseList;
        //         while (curCourse->listStudent != nullptr) {
        //             curCourseStudent = curCourse->listStudent;
        //             curCourse->listStudent = curCourseStudent->nextStudent;
        //             delete curCourseStudent;
        //             curCourseStudent = nullptr;
        //         }
        //         curSem->CourseList = curCourse->nextCourse;
        //         delete curCourse;
        //         curCourse = nullptr;
        //     }
        //     curYear->SemesterList = curSem->nextSemester;
        //     delete curSem;
        //     curSem = nullptr;
        // }
        listYear = curYear->nextYear;
        delete curYear;
        curYear = nullptr;
    }
}
void QuickPtrBinder(Schoolyear* &listYear)
{
    if (listYear == nullptr)
        return;
    Schoolyear* curYear = listYear;
    StudyClass* curClass = nullptr;
    Student* curStudent = nullptr;
    while (curYear != nullptr)
    {
        if (curYear->listClass != nullptr)
        {
            curClass = curYear->listClass;
            curYear->quickClassPtr = new StudyClass*[curYear->numClass];
            int i = 0;
            while (curClass != nullptr)
            {
                curYear->quickClassPtr[i] = curClass;
                i++;
                if (curClass->listStudent != nullptr)
                {
                    curStudent = curClass->listStudent;
                    curClass->quickStudentPtr = new Student*[curClass->numStudent];
                    int j = 0;
                    while (curStudent != nullptr)
                    {
                        curClass->quickStudentPtr[j] = curStudent;
                        j++;
                        curStudent = curStudent->nextStudent;
                    }
                }
                curClass = curClass->nextClass;
            }
        }
        curYear = curYear->nextYear;
    }

}

