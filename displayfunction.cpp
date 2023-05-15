#include "header/displayfunction.h"

void DisplayBirth(BirthDate InputBirth)
{
    int offset = 0;
    if (InputBirth.day / 10 == 0) {
        offset += 1;
    }
    if (InputBirth.month / 10 == 0) {
        offset += 1;
    }
    cout << left << InputBirth.day << '/';
    cout << left << InputBirth.month << '/';
    cout << left << setw(13+offset) << InputBirth.year;
}

void DisplayScoreBoardUI(Course* listCourse, bool &nextStep)
{
        cout << left << setw(5) << "No";
        cout << left << setw(15) << "Student ID";
        cout << left << setw(25) << "First Name";
        cout << left << setw(15) << "Last Name";
        cout << left << setw(15) << "Courses ID: ";
        bool noCourse = true;
        while (listCourse != nullptr) {
            noCourse = false;
            cout << left << setw(15) << listCourse->thisCourseInfo.courseID;
            listCourse = listCourse->nextCourse;
        }
        if (noCourse == true) {
            cout << "     No Courses found" << endl;
            nextStep = false;
        } else {
            cout << left << setw(15) << "GPA (10)";
            cout << left << setw(15) << "GPA (4)" << endl;
            nextStep = true;
        }
        
}

void DisplayScoreBoard(StudyClass* curClass, Course* listCourse, int semester, string year)
{
    Student* curStudent = curClass->listStudent;
    Course* curCourse = nullptr;
    SemEnrollCourse* curSemEnroll = nullptr;
    EnrolledCourse* curEnrolled = nullptr;
    int i = 0;
    while (curStudent != nullptr) {
        i++;
        double TOTAL = 0;
        cout << left << setw(5) << i;
        cout << left << setw(15) << curStudent->dInfo.StudentID;
        cout << left << setw(25) << curStudent->dInfo.FirstName;
        cout << left << setw(30) << curStudent->dInfo.LastName;
        curCourse = listCourse;
        curSemEnroll = curStudent->pSemester;
        while(curSemEnroll != nullptr && (curSemEnroll->semester != semester + 1 || curSemEnroll->year != year)){
            curSemEnroll = curSemEnroll->nextSem;
        }
        if(curSemEnroll == nullptr) {
            while(curCourse != nullptr) {
                cout << left << setw(15) << "N/A";
                curCourse = curCourse->nextCourse;
            }
        } else {
            int k = 0;
            while (curCourse != nullptr) {
                curEnrolled = curSemEnroll->CourseList;
                while (curEnrolled != nullptr && curEnrolled->ptoCourse != curCourse) {
                    curEnrolled = curEnrolled->nextCourse;
                }
                if (curEnrolled == nullptr) {
                    cout << left << setw(15) << "N/A";
                } else {
                    cout << left << setw(15) << (curEnrolled->Score->totalMark);
                    TOTAL += curEnrolled->Score->totalMark;
                    k++;
                }
                curCourse = curCourse->nextCourse;
            }
            if (k == 0) {
                cout << left << setw(15) << 0;
            } else {
                cout << left << setw(15) << TOTAL/(k*1.0);
                cout << left << setw(15) << (TOTAL*4.0)/(k*10.0);
            }
        }
        
            
        curStudent = curStudent->nextStudent;
        cout << endl;
    }
}

void DisplayStudentList(Student* listStudent)
{
    int i = 0;
    while (listStudent != nullptr) {
        i++;
        listStudent->No = i;
        cout << left << setw(5) << listStudent->No;
        cout << left << setw(15) << listStudent->dInfo.StudentID;
        cout << left << setw(25) << listStudent->dInfo.FirstName;
        cout << left << setw(15) << listStudent->dInfo.LastName;
        listStudent->dInfo.Gender[0] = toupper(listStudent->dInfo.Gender[0]);
        cout << left << setw(11) << listStudent->dInfo.Gender;
        DisplayBirth(listStudent->dInfo.Birth);
        cout << left << setw(25) << listStudent->dInfo.SocialID;
        listStudent->ovrGPA = 0;
        int index = 0;
        SemEnrollCourse* curEnrolledSemester = listStudent->pSemester;
        while (curEnrolledSemester != nullptr) {
            EnrolledCourse* curEnrolledCourse = curEnrolledSemester->CourseList;
            while (curEnrolledCourse != nullptr) {
                index++;
                listStudent->ovrGPA += curEnrolledCourse->Score->totalMark;
                curEnrolledCourse = curEnrolledCourse->nextCourse;
            }
            curEnrolledSemester = curEnrolledSemester->nextSem;
        }
        if (index != 0) {
            cout << left << setw(20) << listStudent->ovrGPA/(1.0*index);
            cout << left << setw(20) << (listStudent->ovrGPA*4.0)/(10.0*index) << endl;
        } else {
            cout << left << setw(20) << 0;
            cout << left << setw(20) << 0 << endl; 
        }
        
        listStudent = listStudent->nextStudent;
    }
}

void DisplayClassList(StudyClass* listClass, int &max)
{
    int i = 0;
    while (listClass != nullptr) {
        i++;
        cout << i << ". " << listClass->className << endl;
        listClass = listClass->nextClass;
    }
    max = i;
}

void DisplayYearList(Schoolyear* listYear, int &max)
{
    int i = 0;
    while (listYear != nullptr) {
        i++;
        listYear->index = i;
        cout << i << ". " << listYear->year << endl;
        listYear = listYear->nextYear;
    }
    max = i;
}

void DisplayCourseStudentList(CourseStudent* listCourseStudent)
{
    int i = 0;
    string temp;
    while(listCourseStudent != nullptr){
        i++;
        listCourseStudent->no = i;
        temp = listCourseStudent->ptoStudent->dInfo.FirstName;
        temp += ' ';
        temp += listCourseStudent->ptoStudent->dInfo.LastName;
        cout << left << setw(5)  << listCourseStudent->no
             << left << setw(15) << listCourseStudent->ptoStudent->dInfo.StudentID
             << left << setw(40) << temp
             << left << setw(10) << listCourseStudent->savedScore.midtermMark
             << left << setw(10) << listCourseStudent->savedScore.finalMark
             << left << setw(10) << listCourseStudent->savedScore.otherMark
             << left << setw(10) << listCourseStudent->savedScore.totalMark
             << endl;
        listCourseStudent = listCourseStudent->nextStudent;
    }
}

void DisplayCourseList(Course* listCourse, int &max)
{
    int i = 0;
    string temp;
    while (listCourse != nullptr)
    {
        i++;
        listCourse->courseIndex = i;
        cout << left << setw(10) << listCourse->courseIndex;
        cout << left << setw(15) << listCourse->thisCourseInfo.courseID;
        cout << left << setw(20) << listCourse->thisCourseInfo.courseName;
        cout << left << setw(20) << listCourse->thisCourseInfo.className;
        if (listCourse->numCurStudents == 0)
            temp = "0";
        else
            temp = to_string(listCourse->numCurStudents);
        temp+= '/';
        temp+= to_string(listCourse->thisCourseInfo.maxStudent);
        cout << left << setw(25) << temp;
        temp = listCourse->thisCourseInfo.CourseDate.day;
        temp += ',';
        temp += listCourse->thisCourseInfo.CourseDate.session;
        cout << left << setw(20) << temp;
        cout << left << setw(30) << listCourse->thisCourseInfo.Teacher << endl;
        listCourse =listCourse->nextCourse;
    }
    max = i;
}

void DisplayScoreboardCourse(Course* pCourse)
{
    cout << left << setw(5)  << "No";
    cout << left << setw(15) << "Student ID";
    cout << left << setw(25) << "Student Name";
    cout << left << setw(10) << "Other";
    cout << left << setw(12) << "Midterm"; 
    cout << left << setw(10) << "Final";
    cout << left << setw(10) << "Total" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    int i = 0;
    string temp;
    while(pCourse->listStudent){
        i++;
        pCourse->listStudent->no = i;
        temp = pCourse->listStudent->ptoStudent->dInfo.LastName + " " + pCourse->listStudent->ptoStudent->dInfo.FirstName;
        cout << left << setw(5)  << pCourse->listStudent->no;
        cout << left << setw(15) << pCourse->listStudent->ptoStudent->dInfo.StudentID;
        cout << left << setw(27) << temp;
        cout << left << setw(11) << pCourse->listStudent->savedScore.otherMark;
        cout << left << setw(11) << pCourse->listStudent->savedScore.midtermMark;
        cout << left << setw(10) << pCourse->listStudent->savedScore.finalMark;
        cout << left << setw(8)  << pCourse->listStudent->savedScore.totalMark << endl;
        pCourse->listStudent = pCourse->listStudent->nextStudent;
    }
}

bool DisplaySemesterList(Semester* SemesterList,Semester** &handlingArr, string yearName, int &max)
{
    if (SemesterList == nullptr)
    {
        return false;
    }
    int i = 0;
    bool exist = false;
    if (handlingArr == nullptr)
    {
        handlingArr = new Semester*[3];
        for (int j = 0; j < 3; j++)
        handlingArr[j] = nullptr;
    }
    while (SemesterList != nullptr) {
        if (SemesterList->year == yearName) {
            handlingArr[i] = SemesterList;
            i++;
            exist = true;
            SemesterList->index = i;
            SemesterList->semester = i;
            cout << left << setw(10) << SemesterList->index;
            cout << left << setw(10) << SemesterList->semester;
            cout << left << setw(15) << SemesterList->start;
            cout << left << setw(10) << SemesterList->end;
            cout << endl;
        }
        SemesterList = SemesterList->nextSemester; 
    }
    if (exist == false)
    {
        return false;
    }
    max = i;
    return true;   
}

//STUDENT
void DisplayInfoStudent(Student* curStudent)
{
    cout << "Student Name: " << curStudent->dInfo.FirstName << ' ' << curStudent->dInfo.LastName << endl;
    curStudent->dInfo.Gender[0] = toupper(curStudent->dInfo.Gender[0]);
    cout << "Gender: " << curStudent->dInfo.Gender << endl;
    cout << "Date of Birth: "; DisplayBirth(curStudent->dInfo.Birth);
    cout << "Social ID: " << curStudent->dInfo.SocialID << endl << endl;

    cout << "Student ID: " << curStudent->dInfo.StudentID << endl;
    cout << "Class Name: " << curStudent->className << endl;
    cout << "Academic Program: " << curStudent->programtype << endl;
}

void DisplayCourseList1Student(Student* pStudent, int semester, string year)
{
    SemEnrollCourse* curSemester = pStudent->pSemester;
    while(curSemester){
        if(curSemester->semester == semester && curSemester->year == year) break;
        curSemester = curSemester->nextSem;
    }
    if(curSemester == nullptr) {
        cout << "Student hasn't enrroled course in semester " << semester << " year " << year << endl;
        return;
    }
    EnrolledCourse* firstCourse = curSemester->CourseList;
    int i = 0;
    string temp;
    cout << left << setw(10) << "Index";
    cout << left << setw(15) << "Course ID";
    cout << left << setw(20) << "Course Name";
    cout << left << setw(20) << "Class Name";
    cout << left << setw(25) << "Number of Students";
    cout << left << setw(20) << "Course Date";
    cout << left << setw(30) << "Teacher";
    cout << endl;
    while(firstCourse){
        i++;
        // firstCourse->ptoCourse->courseIndex = i;
        cout << left << setw(10)  << i;//firstCourse->ptoCourse->courseIndex;
        cout << left << setw(15) << firstCourse->ptoCourse->thisCourseInfo.courseID;
        cout << left << setw(20) << firstCourse->ptoCourse->thisCourseInfo.courseName;
        cout << left << setw(20) << firstCourse->ptoCourse->thisCourseInfo.className;
        if (firstCourse->ptoCourse->numCurStudents == 0)
            temp = "0";
        else
            temp = to_string(firstCourse->ptoCourse->numCurStudents);
        temp += '/';
        temp += to_string(firstCourse->ptoCourse->thisCourseInfo.maxStudent);
        cout << left << setw(25) << temp;
        temp = firstCourse->ptoCourse->thisCourseInfo.CourseDate.day;
        temp += ", ";
        temp += firstCourse->ptoCourse->thisCourseInfo.CourseDate.session;
        cout << left << setw(20) << temp;
        cout << left << setw(30) << firstCourse->ptoCourse->thisCourseInfo.Teacher << endl;
        firstCourse = firstCourse->nextCourse;
    }
}

void DisplayScoreboard1Student(Student* pStudent, int semester, string year)
{
    SemEnrollCourse* curSemester = pStudent->pSemester;
    while(curSemester){
        if(curSemester->semester == semester && curSemester->year == year) break;
        curSemester = curSemester->nextSem;
    }
    if(curSemester == nullptr) {
        cout << "Student hasn't enrroled course in semester " << semester << " year " << year << endl;
        return;
    }
    EnrolledCourse* firstCourse = curSemester->CourseList;
    int i = 0;
    cout << left << setw(5)  << "No";
    cout << left << setw(15) << "Course ID";
    cout << left << setw(30) << "Course Name";
    cout << left << setw(15) << "Class";
    cout << left << setw(12) << "Midterm";
    cout << left << setw(10) << "Final";
    cout << left << setw(10) << "Other";
    cout << left << setw(10) << "Total" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    while(firstCourse){
        i++;
        cout << left << setw(5)  << i;
        cout << left << setw(15) << firstCourse->ptoCourse->thisCourseInfo.courseID;
        cout << left << setw(30) << firstCourse->ptoCourse->thisCourseInfo.courseName;
        cout << left << setw(18) << firstCourse->ptoCourse->thisCourseInfo.className;
        cout << left << setw(11) << firstCourse->Score->midtermMark;
        cout << left << setw(10) << firstCourse->Score->finalMark;
        cout << left << setw(10) << firstCourse->Score->otherMark;
        cout << left << setw(10) << firstCourse->Score->totalMark << endl;
        firstCourse = firstCourse->nextCourse;
    }

}