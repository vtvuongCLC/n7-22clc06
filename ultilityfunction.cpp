#include "header/ultilityfunction.h"
#include "header/datafunction.h"

bool validInfo(BirthDate birth, char gender)
{
    if (gender != 'm' && gender != 'M')
    {
        if (gender != 'f' && gender != 'F')
            return false;
    }
    if (birth.year < 0)
        return false;
    if (birth.month <= 0 || birth.month > 12)
        return false;
    int maxday;

    switch (birth.month)
    {
    case 2:
        if (birth.year % 400 == 0 || (birth.year % 4 == 0 && birth.year % 100 != 0))
            maxday = 29;
        else
            maxday = 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxday = 30;
        break;
    default:
        maxday = 31;
        break;
    }
    if (birth.day <= 0 || birth.day > maxday)
        return false;

    return true;
}
bool validName(string name)
{
    for (int i = 0; i < name.length(); i++) {
        if (name[i] >= 'A' && name[i] <= 'Z' || name[i] >= 'a' && name[i] <= 'z')
            break;
        else {
            name.erase(i);
        }
    }
    for (int i = name.length()-1; i >= 0; i++) {
        if (name[i] >= 'A' && name[i] <= 'Z' || name[i] >= 'a' && name[i] <= 'z')
            break;
        else {
            name.erase(i);
        }
    }
    for (int i = 0; i < name.length(); i++)
    {
        if (!(name[i] >= 'A' && name[i] <= 'Z' || name[i] >= 'a' && name[i] <= 'z' || name[i] == ' '))
            return false;
    }
    return true;
}
void AddStudentManual(Student *&listStudent, string yearName, string className, string classType, int &numStudent)
{
    Student *curStudent = nullptr;
    do
    {
        int check;
        cout << "Add new student ? (1 to proceed | 0 to exit) : " << endl;
        cin >> check;
        if (check <= 0)
            break;
        Info tempInfo;
        cin.ignore();
        cout << "Enter student ID : ";
        getline(cin, tempInfo.StudentID, '\n');
        bool continueloop;
        do {
            continueloop = false;
            cout << "Enter student First Name : ";
            getline(cin, tempInfo.FirstName, '\n');
            if (validName(tempInfo.FirstName) == false) {
                continueloop = true;
                cout << "Enter only Alphabet character only" << endl;
            }
        } while (continueloop == true);
        do {
            continueloop = false;
            cout << "Enter student Last Name : ";
            getline(cin, tempInfo.LastName, '\n');
            if (validName(tempInfo.LastName) == false) {
                continueloop = true;
                cout << "Enter only Alphabet character only" << endl;
            }
        } while (continueloop == true);
       
        char gender;
        cout << "Enter student Gender (male = m | female = f) : ";
        cin >> gender;
        cout << "Enter student Date of birth (Ex: 29 2 2004) : ";
        cin >> tempInfo.Birth.day >> tempInfo.Birth.month >> tempInfo.Birth.year;
        cin.ignore();
        cout << "Enter student Social ID: ";
        getline(cin, tempInfo.SocialID, '\n');
        if (validInfo(tempInfo.Birth, gender) == true)
        {
            char key;
            cout << "Confirm input data ? (y: yes | n: no) >> ";
            cin >> key;
            if (key == 'y' || key == 'Y')
            {
                if (listStudent == nullptr)
                {
                    listStudent = new Student;
                    curStudent = listStudent;
                }
                else
                {
                    curStudent->nextStudent = new Student;
                    curStudent = curStudent->nextStudent;
                }
                numStudent++;
                curStudent->yearName = yearName;
                curStudent->className = className;
                curStudent->programtype = classType;
                curStudent->password = className;
                curStudent->No = numStudent;
                curStudent->dInfo.StudentID = tempInfo.StudentID;
                curStudent->dInfo.FirstName = tempInfo.FirstName;
                curStudent->dInfo.LastName = tempInfo.LastName;
                if (gender == 'm' || gender == 'M')
                {
                    curStudent->dInfo.Gender = "male";
                }
                else
                {
                    curStudent->dInfo.Gender = "female";
                }
                curStudent->dInfo.Birth.day = tempInfo.Birth.day;
                curStudent->dInfo.Birth.month = tempInfo.Birth.month;
                curStudent->dInfo.Birth.year = tempInfo.Birth.year;
                curStudent->dInfo.SocialID = tempInfo.SocialID;
                cout << "Successfully added student to class" << endl;
                system("pause");
            }
            else
            {
                cout << "Discarded input data." << endl;
                system("pause");
            }
        }
        else
        {
            cout << "Some information about date of birth or gender may not be valid...";
            system("pause");
        }
    } while (true);
}
void AddStudentCSV(Student *&listStudent, string yearName, string className, string classType, int &numStudent)
{
    string filepath;
    ifstream csvIn;
    do
    {
        cin.ignore();
        cout << "Enter CSV file name (without file extension): ";
        getline(cin, filepath);
        csvIn.open("InOut\\" + filepath + ".csv");
        if (csvIn.is_open() == false)
        {
            int selection;
            cout << "Unable to open Input file , please re-check the filepath and enter 1 to try again (or enter 0 to exit)" << endl;
            cout << ">> ";
            cin >> selection;
            if (selection == 0)
                return;
        }
    } while (csvIn.is_open() == false);
    csvIn.ignore(1000, '\n');
    Student *curStudent = nullptr;
    while (csvIn.eof() == false)
    {
        if (listStudent == nullptr)
        {
            listStudent = new Student;
            curStudent = listStudent;
        }
        else
        {
            curStudent->nextStudent = new Student;
            curStudent = curStudent->nextStudent;
        }
        curStudent->yearName = yearName;
        curStudent->className = className;
        curStudent->programtype = classType;
        numStudent++;
        string tempdata;
        getline(csvIn, tempdata, ',');
        curStudent->No = stoi(tempdata);

        getline(csvIn, tempdata, ',');
        curStudent->password = className;
        curStudent->dInfo.StudentID = tempdata;

        getline(csvIn, tempdata, ',');
        curStudent->dInfo.FirstName = tempdata;

        getline(csvIn, tempdata, ',');
        curStudent->dInfo.LastName = tempdata;

        getline(csvIn, tempdata, ',');
        curStudent->dInfo.Gender = tempdata;

        getline(csvIn, tempdata, '/');
        curStudent->dInfo.Birth.day = stoi(tempdata);

        getline(csvIn, tempdata, '/');
        curStudent->dInfo.Birth.month = stoi(tempdata);

        getline(csvIn, tempdata, ',');
        curStudent->dInfo.Birth.year = stoi(tempdata);

        getline(csvIn, tempdata, '\n');
        curStudent->dInfo.SocialID = tempdata;
    }
    system("pause");
}
void AddStudent(Student *&listStudent, string yearName, string className, string classType, int &numStudent)
{
    char choose;
    cout << "Please choose the input method (m - manual(default) or f - CSV file input): " << endl;
    cout << ">> ";
    cin >> choose;
    if (choose == 'f' || choose == 'F')
        AddStudentCSV(listStudent, yearName, className, classType, numStudent);
    else
        AddStudentManual(listStudent, yearName, className, classType, numStudent);
}
void AddClass(StudyClass *&listClass, string yearName, string classType, int &numClass)
{
    StudyClass *curClass = nullptr;
    string tempClass;
    int i = 0;
    cout << "Enter Classes in this year (0 to stop): " << endl
         << endl;
    cin.ignore();
    do
    {
        cout << "Enter Class name: ";
        getline(cin, tempClass, '\n');
        if (tempClass == "0")
        {
            break;
        }
        if (listClass == nullptr)
        {
            listClass = new StudyClass;
            curClass = listClass;
        }
        else
        {
            curClass->nextClass = new StudyClass;
            curClass = curClass->nextClass;
        }
        curClass->className = tempClass;
        curClass->year = yearName;
        curClass->classType = classType;
        i++;
    } while (tempClass != "0");
    numClass = i;
}
Schoolyear* getYearData(Schoolyear *listYear)
{
    system("cls");
    bool continueloop;
    Schoolyear* tempYear = new Schoolyear;
    do
    {
        continueloop = false;
        cout << "Enter School year's start year and end year" << endl
             << endl;
        cout << "Enter School year's Start year: ";
        cin >> tempYear->start;
        cout << "Enter School year's End year: ";
        cin >> tempYear->end;
        if (tempYear->start >= tempYear->end) {
            cout << "End year must be at least 1 year greater than start year" << endl;
            system("pause");
            continueloop = true;
            continue;
        }

        tempYear->year = to_string(tempYear->start);
        tempYear->year += '-';
        tempYear->year += to_string(tempYear->end);
        if (listYear == nullptr)
            break;
        Schoolyear *check = listYear;
        while (check != nullptr)
        {
            if (check->start == tempYear->start)
            {
                cout << "This year has already existed, please re-enter another start-end year" << endl;
                system("pause");
                continueloop = true;
                break;
            }
            check = check->nextYear;
        }
        if (continueloop == true)
            continue;
        check = listYear;
        while (check->nextYear != nullptr)
            check = check->nextYear;
        if (check->end > tempYear->start) {
            cout << "This year start time must be after the last added year's end time (last added year's end time: " << check->end << ')' << endl;
            system("pause");
            continueloop = true;
        }
    } while (continueloop == true);
    return tempYear;
}
void AddYear(DataBase &DB)
{
    if (DB.YearList == nullptr)
    {
        DB.YearList = getYearData(DB.YearList);
    }
    else
    { 
        Schoolyear *curYear = DB.YearList;
        while (curYear->nextYear != nullptr)
        {
            curYear = curYear->nextYear;
        }
        curYear->nextYear = getYearData(DB.YearList);
        curYear->nextYear->prevYear = curYear;
    }
    DB.numYear++;
    cout << "Successfully created an academic year" << endl;
    system("pause");
}

Schoolyear *navigateYear(Schoolyear *listYear, int userindex)
{
    if (listYear == nullptr)
        return nullptr;
    int i = 0;
    while (listYear != nullptr)
    {
        i++;
        if (i == userindex)
            return listYear;
        listYear = listYear->nextYear;
    }
    return nullptr;
}
StudyClass *navigateClass(StudyClass *listClass, int userindex)
{
    if (listClass == nullptr)
        return nullptr;
    int i = 0;
    while (listClass != nullptr)
    {
        i++;
        if (i == userindex)
            return listClass;
        listClass = listClass->nextClass;
    }
    return nullptr;
}
Course *navigateCourse(Course *listCourse, int userindex)
{
    if (listCourse == nullptr)
        return nullptr;
    int i = 0;
    while (listCourse != nullptr)
    {
        i++;
        if (i == userindex)
            return listCourse;
        listCourse = listCourse->nextCourse;
    }
    return nullptr;
}
Student *navigateStudent(Student *listStudent, int userindex)
{
    if (listStudent == nullptr)
    {
        return nullptr;
    }
    int i = 0;
    while (listStudent != nullptr)
    {
        i++;
        if (i == userindex)
            return listStudent;
        listStudent = listStudent->nextStudent;
    }
    return nullptr;
}

CourseStudent *FindStudentIndex(Schoolyear *listYear, string yearName, string className, int classtype, string StudID, Course *curCourse, Semester *curSemester)
{
    Schoolyear *curYear = listYear;
    int x = 0;
    while (curYear && curYear->year != yearName)
    {
        curYear = curYear->nextYear;
        x++;
    }
    if (curYear == nullptr)
    {
        cout << "This year hasn't existed in the system\n";
        system("pause");
        return nullptr;
    }

    int y;
    StudyClass *curClass = nullptr;
    if (classtype == 1)
    {
        y = 0;
        curClass = curYear->listCLC;
    }
    if (classtype == 2)
    {
        y = 1;
        curClass = curYear->listAPCS;
    }
    if (classtype == 3)
    {
        y = 2;
        curClass = curYear->listVP;
    }

    int z = 0;
    while (curClass && curClass->className != className)
    {
        curClass = curClass->nextClass;
        z++;
    }
    if (curClass == nullptr)
    {
        cout << "This study class hasn't existed in the system\n";
        system("pause");
        return nullptr;
    }
    Student *curStudent = curClass->listStudent;
    int t = 0;
    while (curStudent && curStudent->dInfo.StudentID != StudID)
    {
        curStudent = curStudent->nextStudent;
        t++;
    }
    if (curStudent == nullptr)
    {
        cout << "This student hasn't existed in the system\n";
        system("pause");
        return nullptr;
    }
    SemEnrollCourse* curEnrolledSemester = curStudent->pSemester;
    while (curEnrolledSemester != nullptr) {
        if (curEnrolledSemester->year == curSemester->year && curEnrolledSemester->semester == curSemester->semester) {
            EnrolledCourse* curEnrolledCourse = curEnrolledSemester->CourseList;
            while (curEnrolledCourse != nullptr) {
                if (curEnrolledCourse->ptoCourse->thisCourseInfo.CourseDate.session == curCourse->thisCourseInfo.CourseDate.session) {
                    cout << "This student has participated in another courses in this session, return to course manager" << endl;
                    system("pause");
                    return nullptr;
                }
                curEnrolledCourse = curEnrolledCourse->nextCourse;
            }
        }
        curEnrolledSemester = curEnrolledSemester->nextSem;
    }
    CourseStudent *CourseStud = new CourseStudent;
    CourseStud->ptoStudent = curStudent;
    CourseStud->yearIndex = x;
    CourseStud->classtypeIndex = y;
    CourseStud->classIndex = z;
    CourseStud->studentIndex = t;
    LinkEnrolledCourse(curStudent, curCourse, CourseStud, curSemester);
    return CourseStud;
}
CourseStudent *findStudentInCourse(CourseStudent *listStudent, string studID)
{
    while (listStudent)
    {
        if (listStudent->ptoStudent->dInfo.StudentID == studID)
            break;
        listStudent = listStudent->nextStudent;
    }
    return listStudent;
}

Course *findTheCourse(Course* pCourse, string NameCourse, string IDCourse, string NameClass)
{
    while (pCourse)
    {
        if (NameCourse == pCourse->thisCourseInfo.courseName && IDCourse == pCourse->thisCourseInfo.courseID && NameClass == pCourse->thisCourseInfo.className)
            break;
        pCourse = pCourse->nextCourse;
    }
    return pCourse;
}

void StudentPtrBinder(Student **quickStudentPtr, Student *listStudent)
{
    int i = 0;
    while (listStudent != nullptr)
    {
        quickStudentPtr[i] = listStudent;
        i++;
        listStudent = listStudent->nextStudent;
    }
}
void ClassPtrBinder(StudyClass **quickClassPtr, StudyClass *listClass)
{
    int i = 0;
    while (listClass != nullptr)
    {
        quickClassPtr[i] = listClass;
        i++;
        if (listClass->listStudent != nullptr)
        {
            delete []listClass->quickStudentPtr;
            listClass->quickStudentPtr = new Student *[listClass->numStudent];
            StudentPtrBinder(listClass->quickStudentPtr, listClass->listStudent);
        }
        listClass = listClass->nextClass;
    }
}
void subBinder(StudyClass* listClass, int numClass, StudyClass** &ClassHandler)
{
    delete []ClassHandler;
    ClassHandler = new StudyClass*[numClass];
    ClassPtrBinder(ClassHandler,listClass);
}
void QuickPtrBinder(DataBase &DB)
{
    if (DB.YearList != nullptr)
    {
        delete []DB.quickSchoolPtr;
        DB.quickSchoolPtr = new Schoolyear* [DB.numYear]; 
        Schoolyear* curYear = DB.YearList;
        int i = 0;
        while (curYear != nullptr)
        {
            DB.quickSchoolPtr[i] = curYear;
            delete []curYear->qClassPtr;
            curYear->qClassPtr = new StudyClass**[3];
            for (int j = 0; j < 3; j++)
                curYear->qClassPtr[j] = nullptr;

            if (curYear->listCLC != nullptr) {
                subBinder(curYear->listCLC,curYear->numCLC,curYear->qClassPtr[0]);
            }
            if (curYear->listAPCS != nullptr) {
                subBinder(curYear->listAPCS,curYear->numAPCS,curYear->qClassPtr[1]);
            }
            if (curYear->listVP != nullptr) {
                subBinder(curYear->listVP,curYear->numVP,curYear->qClassPtr[2]);
            }
            i++;
            curYear = curYear->nextYear;
        }
    }
}
void subDebinder(StudyClass* curClass)
{
    while (curClass != nullptr)
    {
        if (curClass->listStudent != nullptr) {
            delete[] curClass->quickStudentPtr;
            curClass->quickStudentPtr = nullptr;
        }
        curClass = curClass->nextClass;
    }
}
void QuickPtrDebinder(DataBase &DB)
{
    if (DB.YearList != nullptr)
    {
        Schoolyear *curYear = DB.YearList;
        StudyClass *curClass = nullptr;
        while (curYear != nullptr)
        {
            curClass = curYear->listCLC;
            subDebinder(curClass);
            curClass = curYear->listAPCS;
            subDebinder(curClass);
            curClass = curYear->listVP;
            subDebinder(curClass);

            if (curYear->qClassPtr != nullptr)
            {
                for (int i = 0; i < 3; i++)
                {
                    delete []curYear->qClassPtr[i];
                    curYear->qClassPtr[i] = nullptr;
                }
                delete []curYear->qClassPtr;
                curYear->qClassPtr = nullptr;
            }

            curYear = curYear->nextYear;
        }
        delete[] DB.quickSchoolPtr;
        DB.quickSchoolPtr = nullptr;
    }
}

void LinkEnrolledCourse(Student *&curStudent, Course *curCourse, CourseStudent *curCourseStudent, Semester *curSemester)
{
    if (curStudent->pSemester == nullptr)
    {
        curStudent->pSemester = new SemEnrollCourse;
        curStudent->pSemester->semester = curSemester->semester;
        curStudent->pSemester->year = curSemester->year;
    }

    SemEnrollCourse *curSemEnroll = curStudent->pSemester;
    while (curSemEnroll)
    {
        if (curSemEnroll->semester == curSemester->semester && curSemEnroll->year == curSemester->year)
        {
            EnrolledCourse *tmp = curSemEnroll->CourseList;
            curSemEnroll->CourseList = new EnrolledCourse;
            curSemEnroll->CourseList->nextCourse = tmp;
            if (tmp)
                tmp->prevCourse = curSemEnroll->CourseList;
            else
                curSemEnroll->lastEnrolledCourse = curSemEnroll->CourseList;
            curSemEnroll->CourseList->ptoCourse = curCourse;
            curSemEnroll->CourseList->Score = &(curCourseStudent->savedScore);
            return;
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
void getCourseListForHandlingArr(string curYearName, Semester* listSemester, Semester** HandlingArr, int &k)
{
    for (int i = 0; i < 3; i++) {
            HandlingArr[i] = nullptr;
        }
    Semester* iSemester = listSemester;
    k = 0;       
    while (iSemester != nullptr) {
        if (iSemester->year == curYearName)  {
            HandlingArr[k] = iSemester;
            k++;
        }
        iSemester = iSemester->nextSemester;
    }
    k--;
}

void uppercaser(string &a)
{
    for (int i = 0; i < a.length(); i++)
    {
        toupper(a[i]);
    }
}
void UpdateStudentInfo(Student *curStudent)
{
    do
    {
        system("cls");
        char selection;
        cout << "Current Information: " << endl;
        cout << "1.First Name: " << curStudent->dInfo.FirstName << endl;
        cout << "2.Last Name: " << curStudent->dInfo.LastName << endl;
        curStudent->dInfo.Gender[0] = toupper(curStudent->dInfo.Gender[0]);
        cout << "3.Gender: " << curStudent->dInfo.Gender << endl;
        cout << "4.Date of Birth: " << curStudent->dInfo.Birth.day << '/' << curStudent->dInfo.Birth.month << '/' << curStudent->dInfo.Birth.year << endl;
        cout << "5.Social ID: " << curStudent->dInfo.SocialID << endl;
        cout << "0. Back" << endl;
        cout << "Enter selection: " << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == '0')
            break;
        cin.ignore(1000, '\n');
        string temp;
        char c;
        switch (selection)
        {
        case '1':
            
            cout << "Enter new First Name" << endl;
            getline(cin, temp);
            cout << "Confirm change ? (y/n): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                curStudent->dInfo.FirstName = temp;
                cout << "First Name changed successfully" << endl;
            }
            else
            {
                cout << "Discarded change" << endl;
            }
            system("pause");
            break;
        case '2':
            cout << "Enter new Last Name" << endl;
            getline(cin, temp);
            cout << "Confirm change ? (y/n): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                curStudent->dInfo.LastName = temp;
                cout << "Last Name changed successfully" << endl;
            }
            else
            {
                cout << "Discarded change" << endl;
            }
            system("pause");
            break;
        case '3':
            char gender;
            cout << "Enter new Gender (1-Male | 0-Female)" << endl;
            cin >> gender;
            if (gender == '0' || gender == '1')
            {
                cout << "Confirm change ? (y/n): ";
                cin >> c;
                if (c == 'y' || c == 'Y')
                {
                    if (gender == '1')
                        curStudent->dInfo.Gender = "male";
                    else
                        curStudent->dInfo.Gender = "female";
                    cout << "Gender changed successfully" << endl;
                }
                else
                {
                    cout << "Discarded change" << endl;
                }
            }
            else
            {
                cout << "No changes were made" << endl;
            }
            system("pause");
            break;
        case '4':
            char select, subselect;
            BirthDate tempbirth;
            do
            {
                system("cls");
                cout << "Current Date of Birth: " << curStudent->dInfo.Birth.day << '/' << curStudent->dInfo.Birth.month << '/' << curStudent->dInfo.Birth.year << endl;
                cout << endl;
                cout << "Enter new Date of Birth (Enter 0 to exit): " << endl;
                cin >> c;
                if (c == '0') {
                    cout << "No changes were made" << endl;
                }
                cout << "Enter new Birth Day: ";
                cin >> tempbirth.day;
                cout << "Enter new Birth Month: ";
                cin >> tempbirth.month;
                cout << "Enter new Birth Year: ";
                cin >> tempbirth.year;
                if (validInfo(tempbirth, 'm') == true)
                {
                    char confirm;
                    cout << "Confirm change ? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y')
                    {
                        curStudent->dInfo.Birth = tempbirth;
                        cout << "Date of Birth changed successfully" << endl;
                    }
                    else
                    {
                        cout << "Discarded changes" << endl;
                    }
                    break;
                }
                else
                {
                    cout << "New Date of Birth is not valid, please try again" << endl;
                    system("pause");
                }
            } while (true);
            system("pause");
            break;
        case '5':
            cout << "Enter new Social ID: ";
            getline(cin, temp);
            cout << "Confirm change ? (y/n): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                curStudent->dInfo.SocialID = temp;
                cout << "Social ID changed successfully" << endl;
            }
            else
            {
                cout << "Discared change" << endl;
            }
            system("pause");
            break;
        }
    } while (true);
}
void UpdateCourseInfo(CourseInfo &curCourseInfo, Semester* curSemester)
{
    int selection;
    do
    {
        system("cls");
        cout << "1. Course ID: " << curCourseInfo.courseID << endl;
        cout << "2. Course Name: " << curCourseInfo.courseName << endl;
        cout << "3. Class Name: " << curCourseInfo.className << endl;
        cout << "4. Maximum number of Students: " << curCourseInfo.maxStudent << endl;
        cout << "5. Course Day: " << curCourseInfo.CourseDate.day << endl;
        cout << "6. Course Session: " << curCourseInfo.CourseDate.session << endl;
        cout << "7. Teacher: " << curCourseInfo.Teacher << endl;
        cout << "8. Number of Credits: " << curCourseInfo.credit << endl;
        cout << "0. Back" << endl;
        cout << ">> ";
        cin >> selection;
        if (selection == 0)
            break;
        cin.ignore(1000, '\n');
        system("cls");
        string courseID = curCourseInfo.courseID, courseName = curCourseInfo.courseName, className = curCourseInfo.className;
        switch (selection)
        {

        case 1:
            cout << "Enter the new course ID: ";
            getline(cin, courseID);
            break;

        case 2:
            cout << "Enter the new course name: ";
            getline(cin, courseName);
            break;

        case 3:
            cout << "Enter the new class name: ";
            getline(cin, className);
            break;

        case 4:
            int numMaxStudents;
            cout << "Enter the number of max students (must bigger than current): ";
            do
            {
                cin >> numMaxStudents;
            } while (numMaxStudents < curCourseInfo.maxStudent);

            curCourseInfo.maxStudent = numMaxStudents;
            break;

        case 5:
            int day;
            cout << "2. Monday" << endl
                 << "3. Tueday" << endl
                 << "4. Wednesday" << endl
                 << "5. Thursday" << endl
                 << "6. Friday" << endl
                 << "7. Saturday" << endl
                 << "0. Cancel" << endl
                 << "Enter the selection of day of the week: ";
            cin >> day;

            switch (day)
            {
            case 2:
                curCourseInfo.CourseDate.day = "MON";
                break;
            case 3:
                curCourseInfo.CourseDate.day = "TUE";
                break;
            case 4:
                curCourseInfo.CourseDate.day = "WED";
                break;
            case 5:
                curCourseInfo.CourseDate.day = "THU";
                break;
            case 6:
                curCourseInfo.CourseDate.day = "FRI";
                break;
            case 7:
                curCourseInfo.CourseDate.day = "SAT";
                break;
            default:
                cout << "Cancel change" << endl;
                system("pause");
                break;
            }
            break;

        case 6:
            int session;
            cout << "1. S1(07:30)" << endl
                 << "2. S2(09:30)" << endl
                 << "3. S3(13:30)" << endl
                 << "4. S4(15:30)" << endl
                 << "0. Cancel" << endl
                 << "Enter the selection of the session: ";
            cin >> session;

            switch (session)
            {
            case 1:
                curCourseInfo.CourseDate.session = "S1(07:30)";
                break;
            case 2:
                curCourseInfo.CourseDate.session = "S2(09:30)";
                break;
            case 3:
                curCourseInfo.CourseDate.session = "S3(13:30)";
                break;
            case 4:
                curCourseInfo.CourseDate.session = "S4(15:30)";
                break;
            default:
                cout << "Cancel change" << endl;
                system("pause");
                break;
            }
            break;

        case 7:
            cout << "Enter the new Teacher of the course: ";
            getline(cin, curCourseInfo.Teacher);
            break;

        case 8:
            cout << "Enter the new credit: ";
            do
            {
                cin >> curCourseInfo.credit;
                if (curCourseInfo.credit <= 0)
                    cout << "The number of credits must > 0" << endl;
            } while (curCourseInfo.credit <= 0);
            break;
        default:
            return;
        }
        if(!(courseID == curCourseInfo.courseID && courseName == curCourseInfo.courseName && className == curCourseInfo.className)){
            if(findTheCourse(curSemester->CourseList, courseName, courseID, className) == nullptr){
                curCourseInfo.courseID = courseID;
                curCourseInfo.courseName = courseName;
                curCourseInfo.className = className;
            }
            else {
                cout << "The new information of this course has been duplicated with other courses!!!" << endl;
                system("pause");
                continue; 
            }
        }
        cout << "This course is updated with the new info" << endl;
        system("pause");
    } while (true);
}
bool UploadListofStud(Course *&curCourse, Semester *curSemester, Schoolyear *listYear)
{
    if (curCourse->listStudent)
        return false;
    CourseStudent *temp = nullptr;
    string yearName, className, StudID, tmp;
    ifstream in;
    int i = 0;
    in.open("InOut\\" + curCourse->thisCourseInfo.courseID + ".csv");
    if (!in.is_open())
    {
        return false;
    }
    int classtype;
    in.ignore(1000,'\n');
    while (i < curCourse->thisCourseInfo.maxStudent && !in.eof())
    {
        getline(in, yearName, ',');
        getline(in, className, ',');
        getline(in, tmp, ',');
        getline(in, StudID);
        uppercaser(tmp);
        if (tmp == "CLC")
            classtype = 1;
        if (tmp == "APCS")
            classtype = 2;
        if (tmp == "VP")
            classtype = 3;
        CourseStudent *newStudent = FindStudentIndex(listYear, yearName, className, classtype, StudID, curCourse, curSemester);
        if (newStudent != nullptr)
        {
            if (curCourse->listStudent == nullptr)
            {
                curCourse->listStudent = newStudent;
                temp = curCourse->listStudent;
            }
            else
            {
                temp->nextStudent = newStudent;
                temp->nextStudent->prevStudent = temp;
                temp = temp->nextStudent;
            }
            i++;
        }
    }
    if (i <= curCourse->thisCourseInfo.maxStudent)
        cout << "No student left to add.";
    else
        cout << "Maximum number of students added.";
    in.close();
    curCourse->numCurStudents = i;
    return true;
}
void NewCourse(Course *&firstCour)
{
    system("cls");
    Course *tmp = firstCour;
    firstCour = new Course;
    firstCour->nextCourse = tmp;
    if (tmp)
        tmp->prevCourse = firstCour;

    cin.ignore(1000, '\n');
    cout << "Enter course ID: ";
    getline(cin, firstCour->thisCourseInfo.courseID);
    cout << "Enter course name: ";
    getline(cin, firstCour->thisCourseInfo.courseName);
    cout << "Enter class name: ";
    getline(cin, firstCour->thisCourseInfo.className);
    cout << "Enter teacher name: ";
    getline(cin, firstCour->thisCourseInfo.Teacher);
    do
    {
        cout << "Enter number of credits: ";
        cin >> firstCour->thisCourseInfo.credit;
        if (firstCour->thisCourseInfo.credit <= 0)
        {
            cout << "The number of credits must be greater than 0" << endl;
        }
    } while (firstCour->thisCourseInfo.credit <= 0);
    do
    {
        cout << "Enter max number of students: ";
        cin >> firstCour->thisCourseInfo.maxStudent;
        if (firstCour->thisCourseInfo.maxStudent <= 0)
        {
            cout << "The number of students must be greater than 0" << endl;
        }
    } while (firstCour->thisCourseInfo.maxStudent <= 0);
    cout << "Enter session for course" << endl;
    cout << "Enter the selection of day of the week: \n\n";
    cout << "2. Monday" << endl
         << "3. Tueday" << endl
         << "4. Wednesday" << endl
         << "5. Thursday" << endl
         << "6. Friday" << endl
         << "7. Saturday" << endl
         << endl;
    int day;
    bool checkInvalid = true;
    while (checkInvalid)
    {
        cout << "=> Enter day of the week: ";
        cin >> day;
        switch (day)
        {
        case 2:
            firstCour->thisCourseInfo.CourseDate.day = "MON";
            break;
        case 3:
            firstCour->thisCourseInfo.CourseDate.day = "TUE";
            break;
        case 4:
            firstCour->thisCourseInfo.CourseDate.day = "WED";
            break;
        case 5:
            firstCour->thisCourseInfo.CourseDate.day = "THU";
            break;
        case 6:
            firstCour->thisCourseInfo.CourseDate.day = "FRI";
            break;
        case 7:
            firstCour->thisCourseInfo.CourseDate.day = "SAT";
            break;
        default:
            cout << "Day must be from 2 to 7\n";
        }
        if (day >= 2 && day <= 7)
            checkInvalid = false;
    }
    int session;
    checkInvalid = true;
    cout << "Enter the selection of the session: \n";
    cout << "1. S1(07:30)" << endl
         << "2. S2(09:30)" << endl
         << "3. S3(13:30)" << endl
         << "4. S4(15:30)" << endl
         << endl;
    while (checkInvalid)
    {
        cout << "=> Session for that day: ";
        cin >> session;
        switch (session)
        {
        case 1:
            firstCour->thisCourseInfo.CourseDate.session = "S1(07:30)";
            break;
        case 2:
            firstCour->thisCourseInfo.CourseDate.session = "S2(09:30)";
            break;
        case 3:
            firstCour->thisCourseInfo.CourseDate.session = "S3(13:30)";
            break;
        case 4:
            firstCour->thisCourseInfo.CourseDate.session = "S4(15:30)";
            break;
        default:
            cout << "Session must be from 1 to 4\n";
        }
        if (session >= 1 && session <= 4)
            checkInvalid = false;
    }
}
void InitSemester(Semester *&Sem, int semester, string year)
{
    Semester *curSem = nullptr;
    if (Sem == nullptr)
    {
        Sem = new Semester;
        curSem = Sem;
    }
    else
    {
        curSem = Sem;
        while (curSem->nextSemester != nullptr)
        {
            curSem = curSem->nextSemester;
        }
        curSem->nextSemester = new Semester;
        curSem = curSem->nextSemester;
    }
    curSem->semester = semester;
    curSem->year = year;

    cout << "\nThe system created semester " << curSem->semester << " in year " << curSem->year << endl;
    cin.ignore(1000, '\n');
    cout << "Enter starting date for semester " << curSem->semester << ": ";
    getline(cin, curSem->start);
    cout << "Enter ending date for semester " << curSem->semester << ": ";
    getline(cin, curSem->end);
    cout << "Successfully created a semester" << endl;
    system("pause");
}
void addStudentToCourse(Course *curCourse, Semester *curSemester, Schoolyear *curYear)
{
    if (curCourse->numCurStudents >= curCourse->thisCourseInfo.maxStudent)
    {
        cout << "The course is having maximum student!!! You cannot add student to this course.\n";
        return;
    }
    int numYears, classtype;
    string studentID, nameStudyClass;
    // DisplayYearList(curYear, numYears);
    cin.ignore(1000, '\n');
    cout << "Enter the student ID: ";
    getline(cin, studentID);
    cout << "Enter the academic program of student (1-CLC | 2-APCS | 3-VP): ";
    cin >> classtype;
    cin.ignore(1000, '\n');
    cout << "Enter the name of study class of student you want to add: ";
    getline(cin, nameStudyClass);

    if (findStudentInCourse(curCourse->listStudent, studentID) != nullptr)
    {
        cout << "This student has enrolled to this course!\n";
        system("pause");
        return;
    }
    CourseStudent *newStudent = FindStudentIndex(curYear, curYear->year, nameStudyClass, classtype, studentID, curCourse, curSemester);
    if (newStudent != nullptr)
    {
        newStudent->nextStudent = curCourse->listStudent;
        if (curCourse->listStudent)
        {
            curCourse->listStudent->prevStudent = newStudent;
        }
        curCourse->listStudent = newStudent;
        curCourse->numCurStudents++;
        cout << "Successfully added a student to course" << endl;
        system("pause");
    }
}

void removeEnrollCourse(Student *removedStudent, Course *pCourse, Semester *curSemester)
{
    SemEnrollCourse *removedSem = removedStudent->pSemester;
    while (removedSem)
    {
        if (removedSem->semester == curSemester->semester && removedSem->year == curSemester->year)
            break;
        removedSem = removedSem->nextSem;
    }
    if (!removedSem)
        return;
    EnrolledCourse *tmp = removedSem->CourseList;
    while (tmp)
    {
        if (tmp->ptoCourse == pCourse)
            break;
        tmp = tmp->nextCourse;
    }
    if (!tmp->nextCourse)
        removedSem->lastEnrolledCourse = tmp->prevCourse;
    if (tmp->prevCourse && tmp->nextCourse)
    {
        tmp->prevCourse->nextCourse = tmp->nextCourse;
        tmp->nextCourse->prevCourse = tmp->prevCourse;
    }
    else
    {
        removedSem->CourseList = tmp->nextCourse;
        if (removedSem->CourseList)
            removedSem->CourseList->prevCourse = nullptr;
    }
    delete tmp;

    if (!(removedSem->CourseList))
    {
        if (removedStudent->pSemester == removedSem)
        {
            removedStudent->pSemester = removedStudent->pSemester->nextSem;
        }
        else
        {
            SemEnrollCourse *tmpSem = removedStudent->pSemester;
            while (tmpSem && tmpSem->nextSem != removedSem)
                tmpSem = tmpSem->nextSem;
            tmpSem->nextSem = tmpSem->nextSem->nextSem;
        }

        delete removedSem;
    }
}
void removeStudentFromCourse(Course *curCourse, Semester *curSemester, Schoolyear *curYear)
{
    string studentName, studentID, nameStudyClass;
    cin.ignore(1000, '\n');
    cout << "Enter the student ID you want to remove: ";
    getline(cin, studentID);

    CourseStudent *removedStudent = findStudentInCourse(curCourse->listStudent, studentID);

    if (removedStudent == nullptr)
    {
        cout << "The student hasn't enrolled to this course\n";
        system("pause");
        return;
    }

    removeEnrollCourse(removedStudent->ptoStudent, curCourse, curSemester);

    if (removedStudent->nextStudent)
    {
        removedStudent->nextStudent->prevStudent = removedStudent->prevStudent;
    }
    if (removedStudent->prevStudent)
    {
        removedStudent->prevStudent->nextStudent = removedStudent->nextStudent;
    }
    else
    {
        curCourse->listStudent = curCourse->listStudent->nextStudent;
    }
    delete removedStudent;
    curCourse->numCurStudents--;
    cout << "Successfully removed a student from the course" << endl;
    system("pause");
}
void removeCourse(Semester *curSemester)
{
    string courseName, courseID, className;
    cin.ignore(1000, '\n');

    cout << "Enter the course ID you want to remove: ";
    getline(cin, courseID);
    cout << "Enter the course name you want to remove: ";
    getline(cin, courseName);
    cout << "Enter the class name of course you want to remove: ";
    getline(cin, className);

    Course *pCourse = findTheCourse(curSemester->CourseList, courseName, courseID, className);
    if (!pCourse)
    {
        cout << "This course doesn't exist!\n";
        system("pause");
        return;
    }

    if (pCourse == curSemester->CourseList)
    {
        curSemester->CourseList = curSemester->CourseList->nextCourse;
        if (curSemester->CourseList)
            curSemester->CourseList->prevCourse = nullptr;
    }
    else
    {
        pCourse->prevCourse->nextCourse = pCourse->nextCourse;
        if (pCourse->nextCourse)
            pCourse->nextCourse->prevCourse = pCourse->prevCourse;
    }

    while (pCourse->listStudent)
    {
        CourseStudent *tmp = pCourse->listStudent;
        pCourse->listStudent = pCourse->listStudent->nextStudent;
        removeEnrollCourse(tmp->ptoStudent, pCourse, curSemester);
        delete tmp;
    }
    string filename = "Data\\" + pCourse->thisCourseInfo.courseID + "_" + pCourse->thisCourseInfo.className + ".txt";
    remove(filename.c_str());

    delete pCourse;
    cout << "The program removed this course.\n";
    curSemester->numCourse--;
    system("pause");
}

void ExportCourseStudent(Course *curCourse)
{
    if (curCourse->listStudent == nullptr)
    {
        cout << "No students found in this Course" << endl;
        system("pause");
        return;
    }
    ofstream out;
    out.open("InOut\\StudentOf_" + curCourse->thisCourseInfo.courseID + '_' + curCourse->thisCourseInfo.className + ".csv");
    CourseStudent *curStudent = curCourse->listStudent;
    Scoreboard thisCourseBoard;
    Student *temp = nullptr;
    bool successflag = false;
    out << "No,Student ID,Full Name,Mid Term Mark,Final Mark,Other Mark,Total Mark" << endl;
    while (curStudent != nullptr)
    {
        successflag = true;
        temp = curStudent->ptoStudent;
        thisCourseBoard = curStudent->savedScore;
        out << curStudent->no << ',';
        out << temp->dInfo.StudentID << ',';
        out << temp->dInfo.FirstName + " " + temp->dInfo.LastName << ',';
        out << thisCourseBoard.midtermMark << ',';
        out << thisCourseBoard.finalMark << ',';
        out << thisCourseBoard.otherMark << ',';
        out << thisCourseBoard.totalMark << endl;
        curStudent = curStudent->nextStudent;
    }
    out.close();
    if (successflag == true)
    {
        cout << "Students list exported successfully" << endl;
    }
    else
    {
        cout << "Error occurred while exporting" << endl;
    }
    system("pause");
}
bool importCourseScore(Course *&curCourse)
{
    if (!curCourse->listStudent)
    {
        cout << "No students found in this Course" << endl;
        system("pause");
        return false;
    }
    bool success;
    ifstream in;
    string No, ID, Name, TotalMark, FinalMark, MidtermMark, OtherMark;
    string filepath;
    cin.ignore(1000, '\n');
    cout << "Enter filename (without file extension): ";
    getline(cin, filepath);
    in.open("InOut\\" + filepath + ".csv");
    if (!in.is_open()) {
        success = false;
    } else {
        in.ignore(1000,'\n');
        while (in.eof() == false)
        {
            getline(in, No, ',');
            if (No.empty() == true) {
                in.close();
                break;
            }
            getline(in, ID, ',');
            getline(in, Name, ',');
            getline(in, MidtermMark, ',');
            getline(in, FinalMark, ',');
            getline(in, OtherMark, ',');
            getline(in, TotalMark, '\n');
            CourseStudent *temp = curCourse->listStudent;
            while (temp != nullptr) {
                if (temp->ptoStudent->dInfo.StudentID == ID)
                    break;
                temp = temp->nextStudent;
            }
            temp->savedScore.midtermMark = stod(MidtermMark);
            temp->savedScore.finalMark = stod(FinalMark);
            temp->savedScore.otherMark = stod(OtherMark);
            temp->savedScore.totalMark = stod(TotalMark);
            success = true;
        }
        in.close();
    }
    if (success == true) {
        cout << "Successfully imported file" << endl;
        system("pause");
        return true;
    } else {
        cout << "Error occurred while importing" << endl;
        system("pause");
        return false;
    }
}

void ChangeStudentScore(CourseStudent *listCourseStudent)
{
    if (listCourseStudent == nullptr)
    {
        cout << "No students found in this Course" << endl;
        system("pause");
        return;
    }
    string StudentID;
    cin.ignore();
    cout << "Enter the ID of the student: ";
    cin >> StudentID;
    CourseStudent *curStudent = findStudentInCourse(listCourseStudent, StudentID);
    if (curStudent == nullptr) {
        cout << "There is no student with this ID in the course" << endl;
        system("pause");
        return;
    }
    int choice;
    do
    {
        system("cls");
        cout << "Student ID: " << curStudent->ptoStudent->dInfo.StudentID << endl;
        cout << "Which of Score Updating: " << endl;
        cout << "1. Current Midterm Score: " << curStudent->savedScore.midtermMark << endl;
        cout << "2. Current Final Score: " << curStudent->savedScore.finalMark << endl;
        cout << "3. Current Other Score: " << curStudent->savedScore.otherMark << endl;
        cout << "4. Current Total Score: " << curStudent->savedScore.totalMark << endl;
        cout << "5. Exit" << endl;
        cout << "Enter the selection: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            do
            {
                cout << "Midterm Score: ";
                cin >> curStudent->savedScore.midtermMark;
            } while (curStudent->savedScore.midtermMark < 0 || curStudent->savedScore.midtermMark > 10);
            break;
        case 2:
            do
            {
                cout << "Final Score: ";
                cin >> curStudent->savedScore.finalMark;
            } while (curStudent->savedScore.finalMark < 0 || curStudent->savedScore.finalMark > 10);

            break;
        case 3:
            do
            {
                cout << "Other Score: ";
                cin >> curStudent->savedScore.otherMark;
            } while (curStudent->savedScore.otherMark < 0 || curStudent->savedScore.otherMark > 10);
            break;
        case 4:
            do
            {
                cout << "Total Score: ";
                cin >> curStudent->savedScore.totalMark;
            } while (curStudent->savedScore.totalMark < 0 || curStudent->savedScore.totalMark > 10);
            break;
        }
    } while (choice != 5);
}
void ChangePasswordStaff(StaffAccount *curStaff)
{
    char check;
    string password, confirm;
    while (true)
    {
        system("cls");
        cout << "Do you want to continue changing password ? (1 to proceed | 0 to exit): ";
        cin >> check;
        if (check == '0')
            return;
        if (check != '1')
            continue;
        system("cls");
        cout << "Change Password\n\n";
        cout << "Current Password: ";
        cin >> password;
        if (password != curStaff->password)
        {
            cout << "You must enter a valid password\n";
        }
        else
        {
            cout << "New Password: ";
            cin >> password;
            cout << "Confirm Password: ";
            cin >> confirm;
            if (password == confirm)
            {
                curStaff->password = confirm;
                cout << "The password has been changed successfully!!!\n";
                system("pause");
                break;
            }
            else
            {
                cout << "The new password and confirmation password do not match. The password hasn't been changed!!!\n";
            }
        }
        system("pause");
    }
}
void ChangePasswordStudent(Student *curStudent)
{
    char check;
    string password, confirm;
    while (true)
    {
        system("cls");
        cout << "Do you want to continue changing password ? (1 to proceed | 0 to exit): ";
        cin >> check;
        if (check == '0')
            return;
        if (check != '1')
            continue;
        system("cls");
        cout << "Change Password\n\n";
        cout << "Current Password: ";
        cin >> password;
        if (password != curStudent->password)
        {
            cout << "You must enter a valid password\n";
        }
        else
        {
            cout << "New Password: ";
            cin >> password;
            cout << "Confirm Password: ";
            cin >> confirm;
            if (password == confirm)
            {
                curStudent->password = confirm;
                cout << "The password has been changed successfully!!!\n";
                system("pause");
                break;
            }
            else
            {
                cout << "The new password and confirmation password do not match. The password hasn't been changed!!!\n";
            }
        }
    }
}
int searchStudentAccount(string username, string password, StudyClass *listClass, Student *&toStudent, StudyClass *&toStudyClass)
{
    Student *curStudent = nullptr;
    while (listClass != nullptr)
    {
        curStudent = listClass->listStudent;
        while (curStudent != nullptr)
        {
            if (curStudent->dInfo.StudentID == username)
            {
                if (curStudent->password != password)
                {
                    do
                    {
                        cout << "Invalid password, please re-enter again (0 to exit)" << endl;
                        cout << ">> ";
                        cin >> password;
                    } while (password != curStudent->password && password != "0");
                    if (password == "0")
                    {
                        cout << "Cancelled Login" << endl;
                        system("pause");
                        return 0;
                    }
                }
                toStudent = curStudent;
                toStudyClass = listClass;
                cout << "Login successful" << endl;
                system("pause");
                return 1;
            }
            curStudent = curStudent->nextStudent;
        }
        listClass = listClass->nextClass;
    }
    return -1;
}