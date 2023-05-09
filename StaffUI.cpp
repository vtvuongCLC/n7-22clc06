#include "header/ultilityfunction.h"
#include "header/staffui.h"
#include "header/datafunction.h"
#include "header/displayfunction.h"
void CourseManager(DataBase &DB ,Course* curCourse, Semester* curSemester)
{
    int selection;
    do {
        system("cls");
        cout << "Year: " << curSemester->year << endl;
        cout << "Semester: " << curSemester->semester << endl;
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
                addStudentToCourse(curCourse, curSemester, DB.YearList);
                SaveCourseStudentToFile(curCourse);
            } 
            
            break;
        case 2:
            removeStudentFromCourse(curCourse, curSemester, DB.YearList);
            SaveCourseStudentToFile(curCourse);
            break;
        case 3:
            if (curCourse->numCurStudents == curCourse->thisCourseInfo.maxStudent) {
                cout << "Maximum number of students in course exceeded" << endl;
                system("pause");
            } else {
                UploadListofStud(curCourse, curSemester, DB.YearList);
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
    char selection;
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
        if (selection == '0')
            break;
        if (selection == 'n' || selection == 'N') {
            NewCourse(curSemester->CourseList);
            SaveCourseInfoToFile(curSemester);
            continue;
        }
            
        if (selection == 'x' || selection == 'X') {
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
            int intSelection = int(selection) - '0';
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
    char selection;
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
        if (selection == '0')
            break;
        if ( (maxSelection < 3) && (selection == 'n' || selection == 'N')) {
            InitSemester(DB.SemesterList,maxSelection+1,yearName);
            SaveSemesterToFile(DB.SemesterFile,DB.SemesterList);
        }
            
        else {
            int intSelection = int(selection) - '0';
            if (intSelection > 0 && intSelection <= 3)
            {

                SpecificSemesterManager(DB, handlingArr[intSelection-1]);
            }
        }
    } while (true);
    delete []handlingArr;
}

void StudyClassScoreBoardManager(StudyClass* curClass, string yearName, Semester** HandlingArr)
{
    if (HandlingArr[0] == nullptr) {
        cout << "No Semesters found for this year" << endl;
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
            DisplayScoreBoard(curClass,HandlingArr[i]->CourseList,i, yearName);
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
void StudyClassManager(StudyClass* curClass, Semester* listSemester)
{
    Semester** HandlingArr = nullptr;
    calculateGPA(curClass,curClass->year,listSemester,HandlingArr);
    string selection;
    do {
        system("cls");
            cout << "Student Management" << endl;
            cout << endl; 
            cout << "Year: " << curClass->curyear << endl;
            cout << "Academic Program: " << curClass->classType << endl;
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
                cout << "Enter an index or select below options:" << endl;
                cout << "s. View Scoreboard" << endl;
            }
            cout << "0. Back" << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == "0")
                break;
            if ((curClass->listStudent == nullptr) && (selection == "n" || selection == "N")) {
                AddStudent(curClass->listStudent,curClass->year,curClass->className,curClass->classType,curClass->numStudent);
                SaveStudentListToFile(curClass->className,curClass->listStudent);
            }
            if (selection == "s" || selection == "S") {
                StudyClassScoreBoardManager(curClass,curClass->year,HandlingArr);
            }
            if (curClass->listStudent != nullptr) {
                int intselection = stoi(selection);
                if (intselection > 0 && intselection <= curClass->numStudent) {
                    char choose;
                    cout << "Options: " << endl;
                    cout << "1. Change student's information" << endl;
                    cout << "0. Back" << endl;
                    cout << ">> ";
                    cin >> choose;
                    if (choose == '1') {
                        Student* curStudent = navigateStudent(curClass->listStudent,intselection);
                        if (curStudent != nullptr) {
                            UpdateStudentInfo(curStudent);
                            SaveStudentListToFile(curClass->className,curClass->listStudent);
                        }
                    }
                }
            }
    } while (true);
    Student* curStudent = curClass->listStudent;
    while (curStudent != nullptr) {
        delete []curStudent->GPA;
        curStudent->GPA = nullptr;
        curStudent = curStudent->nextStudent;
    }
    delete []HandlingArr;
}
void ClassesManager(StudyClass* &listClass, Semester* listSemester, string yearName, string classType)
{
    system("cls");
    char selection;  
    int maxSelection;
    StudyClass* chosenClass = nullptr;
    do {
        maxSelection = 0;
        system("cls");
        cout << "Classes Management" << endl;
        cout << endl;
        cout << "Year: " << yearName << endl;
        cout << "Academic Program: " << classType << endl;
        cout << endl;
        cout << "List of classes: " << endl;
        if (listClass == nullptr) {
            cout << "No classes found" << endl;
            cout << endl;
            cout << "n. New class" << endl;
        } else {
            DisplayClassList(listClass,maxSelection);
            cout << endl;
            cout << "Enter an index or select below options:" << endl;
        }
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == '0')
            break;
        else if (selection == 'n' || selection == 'N') {
            AddClass(listClass,yearName,classType);
            SaveClassToFile(listClass->year,listClass->classType,listClass);
        }
        else if (listClass != nullptr) {
            int intSelection = int(selection) - '0';
            if (intSelection > 0 && intSelection <= maxSelection) {
                chosenClass = navigateClass(listClass, intSelection);
                StudyClassManager(chosenClass, listSemester);
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
            char c;
            cout << "Class's Program: " << endl;
            cout << "1. CLC" << endl;
            cout << "2. APCS" << endl;
            cout << "3. VP" << endl;
            cout << ">> ";
            cin >> c;
            if (c == '1') {
                ClassesManager(curYear->listCLC,DB.SemesterList,curYear->year,"CLC");
            }
            if (c == '2') {
                ClassesManager(curYear->listAPCS,DB.SemesterList,curYear->year,"APCS");
            }
            if (c == '3') {
                ClassesManager(curYear->listVP,DB.SemesterList,curYear->year,"VP");
            }
        }
            
        if (selection == 2)
        {
            QuickPtrBinder(DB);
            SemestersListManager(DB,curYear->year);
            QuickPtrDebinder(DB);
        }
    } while (true);
    
}
void MainManagementUI(DataBase &DB)
{
    int maxSelection;
    Schoolyear* chosenYear = nullptr;
    char selection;
    do {
        maxSelection = 0;
        system("cls");
        cout << "List of years:" << endl;
        if (DB.YearList == nullptr) {
            cout << "No school years found" << endl;
            cout << endl;
        } else {
            DisplayYearList(DB.YearList,maxSelection);
            cout << endl;
            cout << "Enter an index or select below options:" << endl;
        }
        
        cout << "n. Add a new year" << endl;
        cout << "0. Back" << endl;
        
        cout << endl << ">> ";
        cin >> selection;
        if (selection == 'n' || selection == 'N') {
            AddYear(DB);
            SaveYearToFile(DB.YearFile,DB.YearList);
            continue;
        }
        if (selection == '0')
            break;
        if (DB.YearList != nullptr) {
            int intSelection = int(selection) - '0';
            if (intSelection > 0 && intSelection <= maxSelection) {
                chosenYear = navigateYear(DB.YearList,intSelection);
                SchoolYearManager(DB,chosenYear);
            }
        }
    } while (true);
}
void StaffUI(DataBase &DB,StaffAccount* toStaff, StaffAccount* staffList)
{   
    char c;
    do {
        system("cls");
        cout << "Staff's Name: " << toStaff->name << endl;
        cout << "Staff Menu:" << endl;
        cout << "1. Change password" << endl;
        cout << "2. Management Functions" << endl;
        cout << "0. Log out" << endl;
        cout << ">> ";
        cin >> c;
        if (c == '0')
            break;
        if (c == '1') {
            ChangePasswordStaff(toStaff);
            SaveStaffData(staffList);
        }
        if (c == '2') {
            MainManagementUI(DB);
        }

    } while (true);
}