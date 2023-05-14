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
void LoadStaffData(StaffAccount* &staffList)
{
    ifstream staffin;
    staffin.open("Data\\Staff.csv");
    string temp;
    StaffAccount* cur = nullptr;
    while (staffin.eof() == false) {
        getline(staffin,temp,',');
        if (temp.empty() == false) {
            if (staffList == nullptr) {
                staffList = new StaffAccount;
                cur = staffList;
            } else {
                cur->nextAccount = new StaffAccount;
                cur = cur->nextAccount;
            }
            cur->username = temp;
            getline(staffin,temp,',');
            cur->password = temp;
            getline(staffin,temp,'\n');
            cur->name = temp;
        }
    }
    staffin.close();
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
        getline(YearIn,tempData,',');
        if (tempData.empty() == false) {
            if (listYear == nullptr) {
                listYear = new Schoolyear;
                curYear = listYear;
            } else {
                curYear->nextYear = new Schoolyear;
                curYear->nextYear->prevYear = curYear;
                curYear = curYear->nextYear;
            }
            numYear++;
            curYear->start = stoi(tempData);
            getline(YearIn,tempData,',');
            curYear->end = stoi(tempData);
            getline(YearIn,curYear->year,'\n');
        }
    }
    YearIn.close();
}
void LoadClassFromfile(string yearName, string classType, StudyClass* &listClass, int &numClass)
{
    if (IsemptyFile(yearName+classType) == true)
        return;
    ifstream ClassIn;
    ClassIn.open("Data\\"+yearName+classType+".txt");
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
            curClass->year = yearName;
            curClass->classType = classType;
            curClass->className = tempClass; 
        }
    }
    ClassIn.close();
}
void LoadStudentListFromFile(string yearName, string className,string classType, Student* &listStudent, int &numStudent)
{
    if (IsemptyFile(className+"StdyCls") == true)
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
            curStudent->programtype = classType;
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
        LoadClassFromfile(curYear->year,"CLC",curYear->listCLC,curYear->numCLC);
        curClass = curYear->listCLC;
        while (curClass != nullptr) {
            LoadStudentListFromFile(curYear->year, curClass->className,"CLC",curClass->listStudent,curClass->numStudent);
            curClass = curClass->nextClass;
        }
        LoadClassFromfile(curYear->year,"APCS",curYear->listAPCS,curYear->numAPCS);
        curClass = curYear->listAPCS;
        while (curClass != nullptr) {
            LoadStudentListFromFile(curYear->year, curClass->className,"APCS",curClass->listStudent,curClass->numStudent);
            curClass = curClass->nextClass;
        }
        LoadClassFromfile(curYear->year,"VP",curYear->listVP,curYear->numVP);
        curClass = curYear->listVP;
        while (curClass != nullptr) {
            LoadStudentListFromFile(curYear->year, curClass->className,"VP",curClass->listStudent,curClass->numStudent);
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
    fileName += "_HK";
    fileName += ('0' + curSemester->semester);
    if (IsemptyFile(fileName+"_CourseInfo") == true)
        return;
    ifstream CourseInfoIn;
    CourseInfoIn.open("Data\\" + fileName + "_CourseInfo.txt");;
    Course* curCourse = nullptr;
    string tempData;
    getline(CourseInfoIn,tempData,'\n');
    if (tempData.empty() == false) {
        curSemester->numCourse = stoi(tempData);
        while (CourseInfoIn.eof() == false) {
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
    }
    
    CourseInfoIn.close();
}
void LoadCourseStudentFromFile(Course* aCourse, Semester* curSemester, Schoolyear** quickPtr)
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
            aCourse->numCurStudents+=1;
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
            curCourseStudent->classtypeIndex = stoi(tempData);
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
            curCourseStudent->ptoStudent = quickPtr[curCourseStudent->yearIndex]->qClassPtr[curCourseStudent->classtypeIndex][curCourseStudent->classIndex]->quickStudentPtr[curCourseStudent->studentIndex];
            Student* curStudent = curCourseStudent->ptoStudent;
            //function LINKENROLLEDCOURSE will reverse the order of a student's enrolled courses list.
            if (curStudent->pSemester == nullptr)
            {
                curStudent->pSemester = new SemEnrollCourse;
                curStudent->pSemester->semester = curSemester->semester;
                curStudent->pSemester->year = curSemester->year;
            }
            SemEnrollCourse* curSemEnroll = curStudent->pSemester;
            while (curSemEnroll)
            {
                if (curSemEnroll->semester == curSemester->semester && curSemEnroll->year == curSemester->year)
                {
                    if(!curSemEnroll->lastEnrolledCourse){
                        curSemEnroll->CourseList = new EnrolledCourse;
                        curSemEnroll->lastEnrolledCourse = curSemEnroll->CourseList;
                    }
                    else {
                        curSemEnroll->lastEnrolledCourse->nextCourse = new EnrolledCourse;
                        curSemEnroll->lastEnrolledCourse->nextCourse->prevCourse = curSemEnroll->lastEnrolledCourse;
                        curSemEnroll->lastEnrolledCourse = curSemEnroll->lastEnrolledCourse->nextCourse;
                    }
                    curSemEnroll->lastEnrolledCourse->ptoCourse = aCourse;
                    curSemEnroll->lastEnrolledCourse->Score = &(curCourseStudent->savedScore);
                    break;
                }
                if (curSemEnroll->nextSem == nullptr)
                {
                    curSemEnroll->nextSem = new SemEnrollCourse;
                    curSemEnroll->nextSem->semester = curSemester->semester;
                    curSemEnroll->nextSem->year = curSemester->year;
                }
                curSemEnroll = curSemEnroll->nextSem;
            }
        }
    }
    CourseStudentIn.close();
}
void LoadSemesterSector(DataBase &DB)
{
    QuickPtrBinder(DB);
    Semester* curSem = nullptr;
    Course* curCourse = nullptr;
    LoadSemesterFromFile(DB.SemesterFile,DB.SemesterList);
        curSem = DB.SemesterList;
        while (curSem != nullptr) {
            LoadCourseInfoFromFile(curSem);
            curCourse = curSem->CourseList;
            while (curCourse != nullptr) {
                LoadCourseStudentFromFile(curCourse,curSem, DB.quickSchoolPtr);
                curCourse = curCourse->nextCourse;
            }
            curSem = curSem->nextSemester;
        }
}

void SaveStaffData(StaffAccount* staffList)
{
    ofstream staffout;
    staffout.open("Data\\Staff.csv");
    string temp;
    while (staffList != nullptr) {
        staffout << staffList->username << ',';
        staffout << staffList->password << ',';
        staffout << staffList->name << '\n';
        staffList = staffList->nextAccount;
    }
    staffout.close();
}
void SaveYearToFile(string YearFile, Schoolyear* ListYear)
{
    if (ListYear == nullptr)
        return;
    ofstream out;
    out.open("Data\\" + YearFile + ".txt");
    while (ListYear != nullptr) {
        out << ListYear->start << ',';
        out << ListYear->end << ',';
        out << ListYear->year << endl;
        ListYear = ListYear->nextYear;
    }
    out.close();
}
void SaveClassToFile(string yearName, string classType, StudyClass* listClass)
{
    if (listClass == nullptr)
        return;
    ofstream out;
    out.open("Data\\"+yearName+classType+".txt");
        while (listClass != nullptr) {
            out << listClass->className << endl;
            listClass = listClass->nextClass;
        }
        out.close();
}
void SaveStudentListToFile(string className, Student* listStudent)
{
    if (listStudent == nullptr)
        return;
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
    if (aCourse->listStudent == nullptr)
        out << "";
    else {
        while (curStudent != nullptr) {
            thisCourseBoard = curStudent->savedScore;
            out << curStudent->yearIndex << ',';
            out << curStudent->classtypeIndex << ',';
            out << curStudent->classIndex << ',';
            out << curStudent->studentIndex << ',';
            out << thisCourseBoard.midtermMark << ',';
            out << thisCourseBoard.finalMark << ',';
            out << thisCourseBoard.otherMark << ',';
            out << thisCourseBoard.totalMark << endl;
            curStudent = curStudent->nextStudent;
        }
    }
    out.close();
}
void SaveCourseInfoToFile(Semester* curSemester)
{
    if (curSemester->CourseList == nullptr)
        return;
    ofstream out;
    string fileName = curSemester->year;
    fileName += "_HK";
    fileName += ('0' + curSemester->semester);
    out.open("Data\\" + fileName + "_CourseInfo.txt");
    out << curSemester->numCourse << endl;
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
    if (listSemester == nullptr)
        return;
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

void ClearStaffList(StaffAccount* &staffList)
{
    StaffAccount* todle = nullptr;
    while (staffList != nullptr) {
        todle = staffList;
        staffList = staffList->nextAccount;
        delete todle;
    }
}
void ClearClass(StudyClass* &listClass)
{
    Student* curStudent = nullptr;
    StudyClass* curClass = nullptr;
    SemEnrollCourse* curSemEnroll = nullptr;
    EnrolledCourse* curEnroll = nullptr;
    while (listClass != nullptr) {
        curClass = listClass;
        while (curClass->listStudent != nullptr) {
            curStudent = curClass->listStudent;
                while(curStudent->pSemester != nullptr){
                    curSemEnroll = curStudent->pSemester;
                    curStudent->pSemester = curSemEnroll->nextSem;
                    while (curSemEnroll->CourseList != nullptr) {
                        curEnroll = curSemEnroll->CourseList;
                        curSemEnroll->CourseList = curEnroll->nextCourse;
                        delete curEnroll;
                    }
                    delete curSemEnroll;
                }
            curClass->listStudent = curStudent->nextStudent;
            delete curStudent;
        }
        listClass = curClass->nextClass;
        delete curClass;
    }
}
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
        ClearClass(curYear->listCLC);
        ClearClass(curYear->listAPCS);
        ClearClass(curYear->listVP);
        delete []curYear->qClassPtr;
        DB.YearList = curYear->nextYear;
        delete curYear;
    }

}

