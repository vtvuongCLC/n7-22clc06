#include "header/ultilityfunction.h"
#include "header/displayfunction.h"
#include "header/datafunction.h"

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
void DisplayStudentList(Student* listStudent)
{
    while (listStudent != nullptr) {
        cout << left << setw(5) << listStudent->No;
        cout << left << setw(15) << listStudent->dInfo.StudentID;
        cout << left << setw(25) << listStudent->dInfo.FirstName;
        cout << left << setw(15) << listStudent->dInfo.LastName;
        listStudent->dInfo.Gender[0] = toupper(listStudent->dInfo.Gender[0]);
        cout << left << setw(11) << listStudent->dInfo.Gender;
        DisplayBirth(listStudent->dInfo.Birth);
        cout << left << setw(25) << listStudent->dInfo.SocialID << endl;
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
    while(listCourseStudent != nullptr){
        i++;
        listCourseStudent->no = i;
        cout << left << setw(5)  << listCourseStudent->no
             << left << setw(15) << listCourseStudent->ptoStudent->dInfo.StudentID
             << left << setw(40) << listCourseStudent->ptoStudent->dInfo.FirstName + ' ' + listCourseStudent->ptoStudent->dInfo.LastName
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
    if (listCourse == nullptr)
        return;
    int i = 0;
    string temp;
    while (listCourse != nullptr)
    {
        i++;
        listCourse->courseIndex = i;
        cout << left << setw(5) << listCourse->courseIndex;
        cout << left << setw(15) << listCourse->thisCourseInfo.courseID;
        cout << left << setw(20) << listCourse->thisCourseInfo.courseName;
        cout << left << setw(10) << listCourse->thisCourseInfo.className;
        temp = listCourse->numCurStudents + '/' + listCourse->thisCourseInfo.maxStudent;
        cout << left << setw(20) << temp;
        temp = listCourse->thisCourseInfo.CourseDate.day + ", " + listCourse->thisCourseInfo.CourseDate.session;
        cout << left << setw(10) << temp;
        cout << left << setw(30) << listCourse->thisCourseInfo.Teacher << endl;
        listCourse =listCourse->nextCourse;
    }
    listCourse->numCurStudents = i;
    max = i;
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
            cout << left << setw(5) << SemesterList->index;
            cout << left << setw(10) << "HK" + SemesterList->semester;
            cout << left << setw(10) << SemesterList->start;
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

void CourseManager(DataBase &DB ,Course* curCourse, Semester* curSemester)
{
    int selection;
    do {
        system("cls");
        cout << "Year: " << curCourse->year << endl;
        cout << "Year: " << curCourse->semester << endl;
        cout << "Course ID: " << curCourse->thisCourseInfo.courseID << endl;
        cout << "Course Name: " << curCourse->thisCourseInfo.courseName << endl;
        cout << "Class Name: " << curCourse->thisCourseInfo.className << endl;
        cout << "Number of Students: " << curCourse->numCurStudents + '/' + curCourse->thisCourseInfo.maxStudent << endl;
        cout << "Course Date: " << curCourse->thisCourseInfo.CourseDate.day + ", " + curCourse->thisCourseInfo.CourseDate.session << endl;
        cout << "Teacher: " << curCourse->thisCourseInfo.Teacher << endl;
        cout << "Number of Credits: " << curCourse->thisCourseInfo.credit << endl;
        cout << endl;

        cout << "List of Students:" << endl;
        cout << left << setw(5) << "No";
        cout << left << setw(15) << "Student ID";
        cout << left << setw(40) << "Student Full Name";
        cout << left << setw(10) << "Midterm";
        cout << left << setw(10) << "Final";
        cout << left << setw(10) << "Other";
        cout << left << setw(10) << "Total";
        if (curCourse->listStudent == nullptr) {
            cout << "No students found" << endl;
        } else {
            DisplayCourseStudentList(curCourse->listStudent);
        }
        cout << endl;
        cout << "1. Add a Student" << endl;
        cout << "2. Remove a Student" << endl;
        cout << "3. Upload a CSV file of enrolled student" << endl;
        cout << "4. Update Course Information" << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == 0)
            break;
        switch (selection)
        {
        case 1:
            if (curCourse->numCurStudents == curCourse->thisCourseInfo.maxStudent) {
                cout << "Maximum number of students in course exceeded" << endl;
                system("pause");
            } else {
                addStudentToCourse(curCourse,DB.YearList);
                SaveCourseStudentToFile(curCourse);
            } 
            
            break;
        case 2:
            removeStudentFromCourse(curCourse,DB.YearList);
            SaveCourseStudentToFile(curCourse);
            break;
        case 3:
            if (curCourse->numCurStudents == curCourse->thisCourseInfo.maxStudent) {
                cout << "Maximum number of students in course exceeded" << endl;
                system("pause");
            } else {
                UploadListofStud(curCourse,DB.YearList);
                SaveCourseStudentToFile(curCourse);
            } 
            break;
        case 4:
                UpdateCourseInfo(curCourse->thisCourseInfo);
                SaveCourseInfoToFile(curSemester);
            break;
        default: break;
        }
    } while (true);
}
void SpecificSemesterManager(DataBase &DB, Semester* curSemester)
{
    int maxSelection;
    string selection;
    do {
        maxSelection = 0;
        system("cls");
        cout << "Current Year: " << curSemester->year << endl;
        cout << "Semester: " << "HK" + curSemester->semester << endl;
        cout << "Start date: " << curSemester->start << endl;
        cout << "End date: " << curSemester->end << endl;
        cout << endl;
        cout << left << setw(5) << "Index";
        cout << left << setw(15) << "Course ID";
        cout << left << setw(20) << "Course Name";
        cout << left << setw(10) << "Class Name";
        cout << left << setw(20) << "Number of Students";
        cout << left << setw(10) << "Course Date";
        cout << left << setw(30) << "Teacher";
        cout << endl;
        if (curSemester->CourseList == nullptr)
        {
            cout << "No Courses found" << endl;

        } else {
            DisplayCourseList(curSemester->CourseList,maxSelection);
        }
        cout << endl;
        cout << "n. Add Course" << endl;
        cout << "x. Remove Course" << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == "0")
            break;
        if (selection == "n" || selection == "N") {
            NewCourse(curSemester->CourseList);
            SaveCourseInfoToFile(curSemester);
        }
            
        if (selection == "x" || selection == "X") {
            removeCourse(curSemester);
            SaveCourseInfoToFile(curSemester);
        }
            
        if (curSemester->CourseList != nullptr) {
            int intSelection = stoi(selection);
            if (intSelection > 0 && intSelection <= maxSelection) {
                Course* curCourse = navigateCourse(curSemester->CourseList,intSelection);
                CourseManager(DB,curCourse,curSemester);
            }
        }
    } while (true);
}
void SemestersListManager(DataBase &DB, string yearName)
{
    int maxSelection;
    string selection;
    Semester** handlingArr = nullptr;

    do {
        maxSelection = 0;
        system("cls");
        cout << "Current Year: " << yearName << endl;
        cout << left << setw(5) << "Index";
        cout << left << setw(10) << "Semester";
        cout << left << setw(10) << "Start";
        cout << left << setw(10) << "End";
        cout << endl;
        if (DisplaySemesterList(DB.SemesterList,handlingArr,yearName,maxSelection) == false)
        {
            cout << "No semesters found." << endl;
        }
        cout << endl;
        if (maxSelection < 3)
        {
            cout << "n. Add semester" << endl;
        } else {
            cout << "All 3 semesters of this year have been added" << endl;
        }
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == "0")
            break;
        if ( (maxSelection < 3) && (selection == "n" || selection == "N")) {
            InitSemester(DB.SemesterList,maxSelection+1,yearName);
            SaveSemesterToFile(DB.SemesterFile,DB.SemesterList);
        }
            
        else {
            int intSelection = stoi(selection);
            if (intSelection > 0 && intSelection <= 3)
            {
                SpecificSemesterManager(DB, handlingArr[intSelection]);
            }
        }
    } while (true);
    delete []handlingArr;
}

void StudyClassManager(StudyClass* curClass, string yearName)
{
    string selection;
    do {
        system("cls");
            cout << "Student Management" << endl;
            cout << endl; 
            cout << "Year: " << yearName << endl;
            cout << "Class: " << curClass->className << endl;
            cout << endl;
            cout << left << setw(5) << "No";
            cout << left << setw(15) << "Student ID";
            cout << left << setw(25) << "First Name";
            cout << left << setw(15) << "Last Name";
            cout << left << setw(11) << "Gender";
            cout << left << setw(19) << "Date of Birth";
            cout << left << setw(25) << "Social ID" << endl;
            if (curClass->listStudent == nullptr) {
                cout << "No students found" << endl;
                cout << endl;
                cout << "n. Add student" << endl;
            } else {
                DisplayStudentList(curClass->listStudent);
                cout << endl;
            }
            cout << "0. Back" << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == "0")
                break;
            if (selection == "n" || selection == "N") {
                AddStudent(curClass->listStudent,yearName,curClass->className,curClass->numStudent);
                SaveStudentListToFile(curClass->className,curClass->listStudent);
            }
    } while (true);
}
void ClassesManager(Schoolyear* curYear)
{
    string selection;
    int maxSelection;
    StudyClass* chosenClass = nullptr;
    do {
        maxSelection = 0;
        system("cls");
        cout << "Classes Management" << endl;
        cout << endl;
        cout << "Year: " << curYear->year << endl;
        cout << endl;
        cout << "List of classes: " << endl;
        if (curYear->listClass == nullptr) {
            cout << "No classes found" << endl;
            cout << endl;
            cout << "n. New class" << endl;
        } else {
            DisplayClassList(curYear->listClass,maxSelection);
            cout << endl;
        }
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == "0")
            break;
        else if (selection == "n" || selection == "N") {
            AddClass(curYear->listClass);
            SaveClassToFile(curYear->year,curYear->listClass);
        }
        else if (curYear->listClass != nullptr) {
            int intSelection = stoi(selection);
            if (intSelection > 0 && intSelection <= maxSelection) {
                chosenClass = navigateClass(curYear->listClass,stoi(selection));
                StudyClassManager(chosenClass, curYear->year);
            }
        }
    } while (true);
}
void SchoolYearManager(DataBase &DB, Schoolyear* curYear)
{
    int selection;
    do {
        system("cls");
        cout << "Current Year: " << curYear->year << endl;
        cout << "1. Classes management" << endl;
        cout << "2. Semesters management" << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == 0)
            break;
        if (selection == 1) {
            ClassesManager(curYear);
        }
            
        if (selection == 2)
        {
            QuickPtrBinder(DB);
            LoadSemesterSector(DB);
            SemestersListManager(DB,curYear->year);
        }
    } while (true);
    
}

void StaffGUI(DataBase &DB)
{   
    int maxSelection;
    Schoolyear* chosenYear = nullptr;
    string selection;
    do {
        maxSelection = 0;
        system("cls");
        cout << "List of years:" << endl;
        if (DB.YearList == nullptr) {
            cout << "No school years found" << endl;
        } else {
            DisplayYearList(DB.YearList,maxSelection);
        }
        cout << endl;
        cout << "n. Add a new year" << endl;
        cout << "0. Back" << endl;
        cout << endl << ">> ";
        cin >> selection;
        if (selection == "n" || selection == "N") {
            AddYear(DB);
            SaveYearToFile(DB.YearFile,DB.YearList);
            continue;
        }
        if (selection == "0")
            break;
        if (DB.YearList != nullptr) {
            int intselection = stoi(selection);
            if (intselection > 0 && intselection <= maxSelection) {
                chosenYear = navigateYear(DB.YearList,intselection);
                SchoolYearManager(DB,chosenYear);
            }
        }
    } while (true);
}

// void StudentGUI()
// {
    
// }