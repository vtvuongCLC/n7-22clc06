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
        cout << left << setw(15) << listStudent->ovrGPA << endl;
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
void DisplayCourseList1Student(Student* pStudent, int semester, string year){
    EnrolledCourse* firstCourse = pStudent->CourseList;
    while(firstCourse){
        if(firstCourse->ptoCourse->year == year && firstCourse->ptoCourse->semester == semester) break;
        firstCourse = firstCourse->nextCourse;
    }
    if(firstCourse == nullptr) cout << "Student hasn't enrroled course!!!\n";

    int i = 0;
    string temp;
    while(firstCourse->ptoCourse->year == year && firstCourse->ptoCourse->semester == semester){
        i++;
        // firstCourse->ptoCourse->courseIndex = i;
        cout << left << setw(10)  << i;//firstCourse->ptoCourse->courseIndex;
        cout << left << setw(15) << firstCourse->ptoCourse->thisCourseInfo.courseID;
        cout << left << setw(20) << firstCourse->ptoCourse->thisCourseInfo.courseName;
        cout << left << setw(10) << firstCourse->ptoCourse->thisCourseInfo.className;
        if (firstCourse->ptoCourse->numCurStudents == 0)
            temp = "0";
        else
            temp = firstCourse->ptoCourse->numCurStudents;
        temp += firstCourse->ptoCourse->numCurStudents;
        temp += '/';
        temp += to_string(firstCourse->ptoCourse->thisCourseInfo.maxStudent);
        cout << left << setw(20) << temp;
        temp = firstCourse->ptoCourse->thisCourseInfo.CourseDate.day;
        temp += ", ";
        temp += firstCourse->ptoCourse->thisCourseInfo.CourseDate.session;
        cout << left << setw(20) << temp;
        cout << left << setw(30) << firstCourse->ptoCourse->thisCourseInfo.Teacher << endl;
        firstCourse = firstCourse->nextCourse;
    }
}

void DisplayScoreboard1Student(Student* pStudent, int semester, string year){
    EnrolledCourse* firstCourse = pStudent->CourseList;
    while(firstCourse){
        if(firstCourse->ptoCourse->year == year && firstCourse->ptoCourse->semester == semester) break;
        firstCourse = firstCourse->nextCourse;
    }
    if(firstCourse == nullptr) cout << "Student hasn't enrroled course!!!\n";
    int i = 0;
    cout << left << setw(5)  << "No";
    cout << left << setw(25) << "Course Name";
    cout << left << setw(15) << "Course ID";
    cout << left << setw(10) << "Other";
    cout << left << setw(12) << "Midterm";
    cout << left << setw(10) << "Final";
    cout << left << setw(10) << "Total" << endl;
    cout << "--------------------------------------------------------------------" << endl;
    while(firstCourse->ptoCourse->year == year && firstCourse->ptoCourse->semester == semester){
        i++;
        cout << left << setw(5)  << i;
        cout << left << setw(25) << firstCourse->ptoCourse->thisCourseInfo.courseName;
        cout << left << setw(17) << firstCourse->ptoCourse->thisCourseInfo.courseID;
        cout << left << setw(11) << firstCourse->Score->otherMark;
        cout << left << setw(11) << firstCourse->Score->midtermMark;
        cout << left << setw(10) << firstCourse->Score->finalMark;
        cout << left << setw(8) << firstCourse->Score->totalMark << endl;
        firstCourse = firstCourse->nextCourse;
    }

}

void DisplayScoreboardCourse(Course* pCourse){
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
        cout << "Semester: " << curCourse->semester << endl;
        cout << "Course ID: " << curCourse->thisCourseInfo.courseID << endl;
        cout << "Course Name: " << curCourse->thisCourseInfo.courseName << endl;
        cout << "Class Name: " << curCourse->thisCourseInfo.className << endl;
        cout << "Number of Students: " << curCourse->numCurStudents  << '/' << curCourse->thisCourseInfo.maxStudent << endl;
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
        cout << endl;
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
        cout << "5. Export students list to CSV file" << endl;
        cout << "6. Import students scores from CSV file" << endl;
        cout << "7. Update scores of a student" << endl;
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
        case 5:
                ExportCourseStudent(curCourse);
            break;
        case 6:
                importCourseScore(curCourse);
                SaveCourseStudentToFile(curCourse);
            break;
        case 7:
                ChangeStudentScore(curCourse->listStudent);
                SaveCourseStudentToFile(curCourse);
            break;
        default: break;
        }
    } while (true);
}
void SpecificSemesterManager(DataBase &DB, Semester* curSemester)
{
    if (curSemester == nullptr)
        return;
    int maxSelection;
    string selection;
    do {
        maxSelection = 0;
        system("cls");
        cout << "Current Year: " << curSemester->year << endl;
        cout << "Semester: " << curSemester->semester << endl;
        cout << "Start date: " << curSemester->start << endl;
        cout << "End date: " << curSemester->end << endl;
        cout << endl;
        cout << left << setw(10) << "Index";
        cout << left << setw(15) << "Course ID";
        cout << left << setw(20) << "Course Name";
        cout << left << setw(20) << "Class Name";
        cout << left << setw(25) << "Number of Students";
        cout << left << setw(20) << "Course Date";
        cout << left << setw(30) << "Teacher";
        cout << endl;
        if (curSemester->CourseList == nullptr)
        {
            cout << "No Courses found" << endl;

        } else {
            DisplayCourseList(curSemester->CourseList,maxSelection);
        }
        curSemester->numCourse = maxSelection;
        cout << endl;
        cout << "n. Add Course" << endl;
        cout << "x. Remove Course" << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == "0")
            break;
        if (selection == "n" || selection == "N") {
            NewCourse(curSemester->CourseList, curSemester->semester, curSemester->year);
            SaveCourseInfoToFile(curSemester);
            continue;
        }
            
        if (selection == "x" || selection == "X") {
            if (curSemester->CourseList == nullptr)
            {
                cout << "No Courses to remove now" << endl;
                system("pause");
            }
            removeCourse(curSemester);
            SaveCourseInfoToFile(curSemester);
            continue;
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
        cout << left << setw(10) << "Index";
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

                SpecificSemesterManager(DB, handlingArr[intSelection-1]);
            }
        }
    } while (true);
    delete []handlingArr;
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
            cout << endl << "No Courses found" << endl;
            nextStep = false;
        } else {
            cout << left << setw(15) << "GPA (4)" << endl;
            nextStep = true;
        }
        
}
void DisplayScoreBoard(StudyClass* curClass, Course* listCourse, int semester)
{
    Student* curStudent = curClass->listStudent;
    Course* curCourse = nullptr;
    EnrolledCourse* curEnrolled = nullptr;
    int i = 0;
    while (curStudent != nullptr) {
        i++;
        int k = 0;
        double TOTAL = 0;
        cout << left << setw(5) << i;
        cout << left << setw(15) << curStudent->dInfo.StudentID;
        cout << left << setw(25) << curStudent->dInfo.FirstName;
        cout << left << setw(30) << curStudent->dInfo.LastName;
        curCourse = listCourse;
        while (curCourse != nullptr) {
            curEnrolled = curStudent->CourseList;
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
        cout << left << setw(15) << curStudent->GPA[semester];
        curStudent = curStudent->nextStudent;
        cout << endl;
    }
}
void StudyClassScoreBoardManager(StudyClass* curClass, string yearName, Semester** HandlingArr)
{
    if (HandlingArr[0] == nullptr) {
        cout << "No Semesters found for this year" << endl;
        delete []HandlingArr;
        system("pause");
        return;
    }

    int i = 0;
    char selection = '\0';
    bool nextStep;
    do {
        system("cls");
        cout << "Year: " << yearName << endl;
        cout << "Semester: " << i+1 << endl;
        
        DisplayScoreBoardUI(HandlingArr[i]->CourseList,nextStep);
        if (nextStep == true) {
            DisplayScoreBoard(curClass,HandlingArr[i]->CourseList,i);
            cout << endl;
        } else {    
            cout << endl;
        }
        if (i != 0) {
                cout << "z. Previous Semester" << endl;
            }
        if (!(i == 2 || HandlingArr[i+1] == nullptr)) {
                cout << "x. Next Semester" << endl;
        }
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == '0')
            break;
        if (selection == 'z' || selection == 'Z') {
            i--;
        }
        if (selection == 'x' || selection == 'X') {
            i++;
        }
    } while(true);
}
void StudyClassManager(StudyClass* curClass, string yearName, Semester* listSemester)
{
    Semester** HandlingArr = new Semester*[3];
    int i;
    for (i = 0; i < 3; i++) {
        HandlingArr[i] = nullptr;
    }
    i = 0;
    
    while (listSemester != nullptr && i < 3) {
        if (listSemester->year == yearName) {
            HandlingArr[i] = listSemester;
            i++;
        }
        listSemester = listSemester->nextSemester;
    }
    Student* curStudent = curClass->listStudent;
    while (curStudent != nullptr) {
        curStudent->ovrGPA = 0;
        curStudent->GPA = new double[3];
            for (int j = 0; j < 3; j++) {
                curStudent->GPA[j] = -1;
            }
        curStudent = curStudent->nextStudent;
    }
    Course* curCourse = nullptr;
    EnrolledCourse* curEnrolled = nullptr;
    for (i = 0; i < 3; i++) {
        if (HandlingArr[i] != nullptr) {
            curStudent = curClass->listStudent;
            while (curStudent != nullptr) {
                int count = 0;
                double totalscore = 0;
                curCourse = HandlingArr[i]->CourseList;
                while (curCourse != nullptr) {
                    curEnrolled = curStudent->CourseList;
                    while (curEnrolled != nullptr && curEnrolled->ptoCourse != curCourse)
                        curEnrolled = curEnrolled->nextCourse;
                    if (curEnrolled != nullptr) {
                        count++;
                        totalscore+= curEnrolled->Score->totalMark;
                    }
                    curCourse = curCourse->nextCourse;
                }
                if (count != 0) {
                    curStudent->GPA[i] = (totalscore*4)/(count*10.0);
                }
                curStudent = curStudent->nextStudent;
            }
        }
    }
    curStudent = curClass->listStudent;
    while (curStudent != nullptr) {
        double totalgpa = 0;
        int count = 0;
        for (int k = 0; k < 3; k++) {
            if (curStudent->GPA[k] != -1) {
                totalgpa+= curStudent->GPA[k];
                count++;
            }
        }
        curStudent->ovrGPA = totalgpa/(count*1.0);
        curStudent = curStudent->nextStudent;
    }

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
            cout << left << setw(25) << "Social ID";
            cout << left << setw(15) << "Overall GPA" << endl;
            if (curClass->listStudent == nullptr) {
                cout << "No students found" << endl;
                cout << endl;
                cout << "n. Add student" << endl;
            } else {
                DisplayStudentList(curClass->listStudent);
                cout << endl;
                cout << "s. View Scoreboard" << endl;
            }
            cout << "0. Back" << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == "0")
                break;
            if ((curClass->listStudent == nullptr) && (selection == "n" || selection == "N")) {
                AddStudent(curClass->listStudent,yearName,curClass->className,curClass->numStudent);
                SaveStudentListToFile(curClass->className,curClass->listStudent);
            }
            if (selection == "s" || selection == "S") {
                StudyClassScoreBoardManager(curClass,yearName,HandlingArr);
            }
    } while (true);
    delete []HandlingArr;
}
void ClassesManager(Schoolyear* curYear, Semester* listSemester)
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
                StudyClassManager(chosenClass, curYear->year, listSemester);
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
            ClassesManager(curYear,DB.SemesterList);
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