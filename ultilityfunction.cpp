#include "header/ultilityfunction.h"

bool validInfo(Info infoparam,char gender)
{
    if (gender != 'm' && gender != 'M')
    {
        if (gender != 'f' && gender != 'F')
        return false;
    }
    if (infoparam.Birth.day <= 0 || infoparam.Birth.day > 31)
        return false;
    if (infoparam.Birth.month <= 0 || infoparam.Birth.month > 12)
        return false;
    if (infoparam.Birth.year < 0)
        return false;
    return true;
}

void AddStudentManual(Student* &listStudent, string yearName, string className, int &numStudent)
{
    Student* curStudent = nullptr;
    do {
        int check;
        system("cls");
        cout << "Add new student ? (1 to proceed | 0 to exit) : " << endl;
        cin >> check;
        if (check <= 0)
            break;
        Info tempInfo;
        cin.ignore();
        cout << "Enter student ID : ";
        getline(cin,tempInfo.StudentID,'\n');
        cout << "Enter student First Name : ";
        getline(cin,tempInfo.FirstName,'\n');
        cout << "Enter student Last Name : ";
        getline(cin,tempInfo.LastName,'\n');
        char gender;
        cout << "Enter student Gender (male = m | female = f) : ";
        cin >> gender;
        cout << "Enter student Date of birth (Ex: 29 2 2004) : ";
        cin >> tempInfo.Birth.day >> tempInfo.Birth.month >> tempInfo.Birth.year;
        cin.ignore();
        cout << "Enter student Social ID: ";
        getline(cin,tempInfo.SocialID,'\n');
        if (validInfo(tempInfo,gender) == true) {
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
            curStudent->password = className;
            curStudent->No = numStudent;
            curStudent->dInfo.StudentID = tempInfo.StudentID;
            curStudent->dInfo.FirstName = tempInfo.FirstName;
            curStudent->dInfo.LastName = tempInfo.LastName;
            if (gender == 'm' || gender == 'M') {
                curStudent->dInfo.Gender = "male";
            } else {
                curStudent->dInfo.Gender = "female";
            }
            curStudent->dInfo.Birth.day = tempInfo.Birth.day;
            curStudent->dInfo.Birth.month = tempInfo.Birth.month;
            curStudent->dInfo.Birth.year = tempInfo.Birth.year;
            curStudent->dInfo.SocialID = tempInfo.SocialID;
        } else {
            cout << "Some information is invalid...";
            system("pause"); 
        }
    } while (true);
}
void AddStudentCSV(Student* &listStudent, string yearName, string className, int &numStudent)
{
    string filepath;
    ifstream csvIn;
    system("cls");
    do {
        cout << "Enter CSV file path: ";
        getline(cin,filepath,'\n');
        csvIn.open(filepath);
        if (csvIn.is_open() == false) {
            int selection;
            cout << "Unable to open Input file , please re-check the filepath and enter 1 to try again (or enter 0 to exit)" << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == 0)
                return;
        }
    } while (csvIn.is_open() == false);
    csvIn.ignore(1000,'\n');
    Student* curStudent = nullptr;
    while (csvIn.eof() == false)
    {
        if (listStudent == nullptr) {
            listStudent = new Student;
            curStudent = listStudent;
        } else {
            curStudent->nextStudent = new Student;
            curStudent = curStudent->nextStudent;
        }
        curStudent->yearName = yearName;
        curStudent->className = className;
        numStudent++;
        string tempdata;
        getline(csvIn,tempdata,',');
        curStudent->No = stoi(tempdata);
        
        getline(csvIn,tempdata,',');
        curStudent->password = className;
        curStudent->dInfo.StudentID = tempdata;        
        
        getline(csvIn,tempdata,',');
        curStudent->dInfo.FirstName = tempdata;
        
        getline(csvIn,tempdata,',');
        curStudent->dInfo.LastName = tempdata;
        
        getline(csvIn,tempdata,',');
        curStudent->dInfo.Gender = tempdata;
        
        getline(csvIn,tempdata,'/');
        curStudent->dInfo.Birth.day = stoi(tempdata);
        
        getline(csvIn,tempdata,'/');
        curStudent->dInfo.Birth.month = stoi(tempdata);
        
        getline(csvIn,tempdata,',');
        curStudent->dInfo.Birth.year = stoi(tempdata);
        
        getline(csvIn,tempdata,'\n');
        curStudent->dInfo.SocialID = tempdata;
    }
    system("pause");
}
void AddStudent(Student* &listStudent, string yearName, string className, int &numStudent)
{
    char choose; 
    cout << "Please choose the input method (m - manual(default) or f - CSV file input): " << endl;
    cout << ">> ";
    cin >> choose;
    if (choose == 'f' || choose == 'F')
        AddStudentCSV(listStudent,yearName,className, numStudent);
    else
        AddStudentManual(listStudent,yearName,className, numStudent);
}
void AddClass(StudyClass* &listClass)
{
    StudyClass* curClass = nullptr;
    string tempClass;
    cout << "Enter Classes in this year (0 to stop): " << endl << endl;
    cin.ignore();
    do {
        cout << "Enter Class name: ";
        getline(cin,tempClass,'\n');
        if (tempClass == "0") {
            break;
        }
        if (listClass == nullptr) {
            listClass = new StudyClass;
            curClass = listClass;
        } else {
            curClass->nextClass = new StudyClass;
            curClass = curClass->nextClass;
        }
        curClass->className = tempClass;
    } while (tempClass != "0");
}
string getYearData(Schoolyear* listYear)
{
    system("cls");
    string schoolyear;
    bool exist;
    do {
        exist = false;
    cout << "Enter School year's start year and end year" << endl << endl;
    cin.ignore();
    cout << "Enter School year's Start year: ";
    cin >> schoolyear;
    schoolyear += '-';
    string temp;
    cout << "Enter School year's End year: ";
    cin >> temp;
    schoolyear += temp;
    Schoolyear* check = listYear;
    while (check != nullptr) {
        if (check->year == schoolyear) {
            cout << "This year has already existed" << endl;
            system("pause");
            exist = true;
            break;
        }
        check = check->nextYear;
    }
    } while (exist == true && listYear != nullptr);
    return schoolyear;
}
void AddYear(Schoolyear* &listYear)
{
    Schoolyear* newYear = new Schoolyear;
    newYear->year = getYearData(listYear);
    newYear->nextYear = listYear;
    listYear = newYear;
}

Schoolyear* navigateYear(Schoolyear* listYear, int userindex)
{
    if (listYear == nullptr)
        return nullptr;
    int i = 0;
    while (listYear != nullptr) {
        i++;
        if (i == userindex)
            return listYear;
        listYear = listYear->nextYear;
    }
    return nullptr;
}
StudyClass* navigateClass(StudyClass* listClass, int userindex)
{
    if (listClass == nullptr)
        return nullptr;
    int i = 0;
    while (listClass != nullptr) {
        i++;
        if (i == userindex)
            return listClass;
        listClass = listClass->nextClass;
    }
    return nullptr;
}
void QuickPtrBinder(DataBase &DB)
{
    if (DB.YearList != nullptr) {
        DB.quickSchoolPtr = new Schoolyear*[DB.numYear];
        Schoolyear* curYear = DB.YearList;
        StudyClass* curClass = nullptr;
        Student* curStudent = nullptr;
        int i = 0;
        while (curYear != nullptr)
        {
            DB.quickSchoolPtr[i] = curYear;
            if (curYear->listClass != nullptr)
            {
                curClass = curYear->listClass;
                curYear->quickClassPtr = new StudyClass*[curYear->numClass];
                int j = 0;
                while (curClass != nullptr)
                {
                    curYear->quickClassPtr[j] = curClass;
                    j++;
                    if (curClass->listStudent != nullptr)
                    {
                        curStudent = curClass->listStudent;
                        curClass->quickStudentPtr = new Student*[curClass->numStudent];
                        int k = 0;
                        while (curStudent != nullptr)
                        {
                            curClass->quickStudentPtr[k] = curStudent;
                            k++;
                            curStudent = curStudent->nextStudent;
                        }
                    }
                    curClass = curClass->nextClass;
                }
            }
            curYear = curYear->nextYear;
        }
    }
}
void BridgingList(DataBase &DB)
{
    if (DB.SemesterList == nullptr)
        return;
    QuickPtrBinder(DB);
    Semester* curSem = DB.SemesterList;
    Course* curCourse = nullptr;
    CourseStudent* curCourseStudent = nullptr;
    while (curSem != nullptr)
    {
        curCourse = curSem->CourseList;
        while (curCourse != nullptr) {
            if (curCourse->listStudent != nullptr) {
                if (curCourse->listStudent->ptoStudent == nullptr)
                {
                    curCourseStudent = curCourse->listStudent;
                    while (curCourseStudent != nullptr) {
                        curCourseStudent->ptoStudent = DB.quickSchoolPtr[curCourseStudent->yearIndex]->quickClassPtr[curCourseStudent->classIndex]->quickStudentPtr[curCourseStudent->studentIndex];
                        curCourseStudent = curCourseStudent->nextStudent;
                    }
                }
            }
            curCourse = curCourse->nextCourse;
        }
        curSem = curSem->nextSemester;
    }
}
