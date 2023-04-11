#include "header/ultilityfunction.h"
#include "header/datafunction.h"
#include "header/displayfunction.h"
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
            char key;
            cout << "Confirm input data ? (y: yes | n: no) >> ";
            cin >> key;
            if (key == 'y' || key == 'Y') {
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
                cout << "Discarded input data." << endl;
                system("pause");
            }

        } else {
            cout << "Some information may not be correct...";
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
void AddYear(DataBase &DB)
{
    if (DB.YearList == nullptr)
    {
        DB.YearList = new Schoolyear;
        DB.YearList->year = getYearData(DB.YearList);
    } else {
        Schoolyear* curYear = DB.YearList;
        while (curYear->nextYear != nullptr) {
            curYear = curYear->nextYear;
        }
        curYear->nextYear = new Schoolyear;
        curYear->nextYear->year = getYearData(DB.YearList);
    }
    DB.numYear++;
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
Course* navigateCourse(Course* listCourse, int userindex)
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
bool FindStudentIndex(Schoolyear* listYear,CourseStudent* &CourseStud, string yearName,string className, string StudID,Course* curCourse)
{
    Schoolyear* curYear = listYear;
    int x = 0;
    while (listYear && listYear->year.find(yearName) == string::npos) {
        curYear = curYear->nextYear;
        x++;
    }
    if (curYear == nullptr){
        cout << "This year hasn't existed in the system\n";
        system("pause");
        return false;
    }
    StudyClass* curClass = curYear->listClass;
    int y = 0;
    while(curClass && curClass->className != className) {
        curClass = curClass->nextClass;
        y++;
    }
    if(curClass == nullptr){
        cout << "This study class hasn't existed in the system\n";
        system("pause");
        return false;
    }
    Student* curStudent = curClass->listStudent;
    int z = 0;
    while(curStudent->dInfo.StudentID != StudID) {
        curStudent = curStudent->nextStudent;
        z++;
    }
    if(curStudent == nullptr){
        cout << "This student hasn't existed in the system\n";
        system("pause");
        return false;
    }
    CourseStud->ptoStudent = curStudent;
    CourseStud->yearIndex = x;
    CourseStud->classIndex = y;
    CourseStud->studentIndex = z;
    LinkEnrolledCourse(curStudent,curCourse, CourseStud);
    return true;
}
CourseStudent* findStudentInCourse(CourseStudent* listStudent, string studID)
{
    while(listStudent){
        if(listStudent->ptoStudent->dInfo.StudentID == studID) break;
        listStudent = listStudent->nextStudent;
    }
    return listStudent;
}
Course* findTheCourse(Semester* pSemester, string year, int semester, string NameCourse, string IDCourse, string NameClass)
{
    while(pSemester){
        if(pSemester->year == year && pSemester->semester == semester) break;
        pSemester = pSemester->nextSemester;
    }
    if(pSemester == nullptr) return nullptr;

    Course* pCourse = pSemester->CourseList;
    while(pCourse){
        if(NameCourse  == pCourse->thisCourseInfo.courseName 
          && IDCourse  == pCourse->thisCourseInfo.courseID 
          && NameClass == pCourse->thisCourseInfo.className) 
        break;
        pCourse = pCourse->nextCourse;
    }
    return pCourse;
} 

void QuickPtrBinder(DataBase &DB)
{
    if (DB.YearList != nullptr) {
        if (DB.quickSchoolPtr != nullptr) {
            delete []DB.quickSchoolPtr;
            DB.quickSchoolPtr = nullptr;
        } 
        DB.quickSchoolPtr = new Schoolyear*[DB.numYear];
        Schoolyear* curYear = DB.YearList;
        StudyClass* curClass = nullptr;
        Student* curStudent = nullptr;
        int i = 0;
        while (curYear != nullptr)
        {
            DB.quickSchoolPtr[i] = curYear;
            i++;
            if (curYear->listClass != nullptr)
            {
                if (curYear->quickClassPtr == nullptr) {
                    if (curYear->quickClassPtr != nullptr)
                    {
                        delete []curYear->quickClassPtr;
                        curYear->quickClassPtr = nullptr;
                    }
                    curYear->quickClassPtr = new StudyClass*[curYear->numClass];
                    curClass = curYear->listClass;
                    int j = 0;
                    while (curClass != nullptr)
                    {
                        curYear->quickClassPtr[j] = curClass;
                        j++;
                        if (curClass->listStudent != nullptr)
                        {
                            curStudent = curClass->listStudent;
                            if (curClass->quickStudentPtr != nullptr)
                            {
                                delete []curClass->quickStudentPtr;
                                curClass->quickStudentPtr = nullptr;
                            }
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
                
            }
            curYear = curYear->nextYear;
        }
    }
}
void LinkEnrolledCourse(Student *&curStudent, Course *curCourse, CourseStudent* curCourseStudent)
{
    EnrolledCourse* temp = curStudent->CourseList;
    curStudent->CourseList = new EnrolledCourse;
    curStudent->CourseList->nextCourse = temp;
    if(temp)
        temp->prevCourse = curStudent->CourseList;
    else
        curStudent->lastEnrolledCourse = curStudent->CourseList;
    curStudent->CourseList->ptoCourse = curCourse;
    curStudent->CourseList->Score = &(curCourseStudent->savedScore);
}

void UpdateCourseInfo(CourseInfo &curCourseInfo)
{   
    int selection;
    do {
        system("cls");
        cout << "1. Course ID: " << curCourseInfo.courseID << endl;
        cout << "2. Course Name: " << curCourseInfo.courseName << endl;
        cout << "3. Class Name: " << curCourseInfo.className << endl;
        cout << "4. Maximum number of Students: " << curCourseInfo.maxStudent << endl;
        cout << "5. Course Day: " << curCourseInfo.CourseDate.day << endl;
        cout << "6. Course Session: " <<  curCourseInfo.CourseDate.session << endl;
        cout << "7. Teacher: " << curCourseInfo.Teacher << endl;
        cout << "8. Number of Credits: " << curCourseInfo.credit << endl;
        cout << "0. Back";
        cout << ">> ";
        cin >> selection;
        if (selection == 0)
            break;
        cin.ignore(1000,'\n');
        switch(selection) {
                
                case 1:
                    cout << "Enter the new course ID: ";
                    getline(cin, curCourseInfo.courseID);
                break;

                case 2:
                    cout << "Enter the new course name: ";
                    getline(cin, curCourseInfo.courseName);
                break;

                case 3:
                    cout << "Enter the new class name: ";
                    getline(cin, curCourseInfo.className);
                break;
                
                case 4:
                    int numMaxStudents;
                    cout << "Enter the number of max students (must bigger than current): ";
                    do{
                        cin >> numMaxStudents;
                    } while(numMaxStudents < curCourseInfo.maxStudent);

                    curCourseInfo.maxStudent = numMaxStudents;
                break;
                
                case 5:
                    int day;
                    cout << "2. Monday"    << endl
                         << "3. Tueday"    << endl
                         << "4. Wednesday" << endl
                         << "5. Thursday"  << endl
                         << "6. Friday"    << endl
                         << "7. Saturday"  << endl
                         << "0. Cancel"    << endl
                         << "Enter the selection of day of the week: ";
                        cin >> day;

                        switch(day){
                            case 2: curCourseInfo.CourseDate.day = "MON"; break;
                            case 3: curCourseInfo.CourseDate.day = "TUE"; break;
                            case 4: curCourseInfo.CourseDate.day = "WED"; break;
                            case 5: curCourseInfo.CourseDate.day = "THU"; break;
                            case 6: curCourseInfo.CourseDate.day = "FRI"; break;
                            case 7: curCourseInfo.CourseDate.day = "SAT"; break;
                            default: 
                                cout << "Cancel change" << endl;
                                system("pause");
                            break;
                        }
                break;
                
                case 6:
                    int session;
                    cout << "1. S1 (07:30)" << endl
                         << "2. S2 (09:30)" << endl
                         << "3. S3 (13:30)" << endl
                         << "4. S4 (15:30)" << endl
                         << "0. Cancel"     << endl
                         << "Enter the selection of the session: "; 
                        cin >> session;

                         switch(session){
                            case 1: curCourseInfo.CourseDate.session = "S1 (07:30)"; break;
                            case 2: curCourseInfo.CourseDate.session = "S2 (09:30)"; break;
                            case 3: curCourseInfo.CourseDate.session = "S3 (13:30)"; break;
                            case 4: curCourseInfo.CourseDate.session = "S4 (15:30)"; break;
                            default:
                                cout << "Cancel change" << endl;
                                system("pause");
                            break;
                         }
                break;
                
                case 7:
                    cout << "Enter the new Teacher of the course: ";
                    getline(cin,curCourseInfo.Teacher);
                break;
                
                case 8:
                    cout << "Enter the new credit: ";
                    do{
                        cin >> curCourseInfo.credit;
                        if(curCourseInfo.credit <= 0)
                            cout << "The number of credits must > 0" << endl;
                    }while(curCourseInfo.credit <= 0);
                break;
                default: return;
            }
    } while (true);
}
bool UploadListofStud(Course* &curCourse, Schoolyear* listYear)
{
    if(curCourse->listStudent)
        return false;
    CourseStudent* temp = nullptr;
    string yearName, className, StudID;
    ifstream in;
    int i = 0;
    in.open(curCourse->thisCourseInfo.courseID+".csv");
    if(!in.is_open()){
        return false;
    }
    while (i < curCourse->thisCourseInfo.maxStudent && !in.eof())
    {
        in.ignore(100,',');
        getline(in,yearName,',');
        getline(in,className,',');
        getline(in,StudID);
        if(!curCourse->listStudent){
            curCourse->listStudent = new CourseStudent;
            temp = curCourse->listStudent;
        }
        else{
            temp->nextStudent = new CourseStudent;
            temp->nextStudent->prevStudent = temp;
            temp = temp->nextStudent;
        }
    
        while(!FindStudentIndex(listYear,temp,yearName,className,StudID,curCourse)){
             getline(in,className,',');
             getline(in,StudID);
        }
        i++;
    }
    if(i <= curCourse->thisCourseInfo.maxStudent) 
        cout<<"No student left to add.";
    else 
        cout<<"Maximum number of students added.";
    in.close();
    curCourse->numCurStudents = i;
    return true;
}
void NewCourse(Course* &firstCour, int semester, string year)
{
    system("cls");
    Course* tmp = firstCour;
    firstCour = new Course;
    firstCour->nextCourse = tmp;
    firstCour->year = year;
    firstCour->semester = semester;
    if(tmp) tmp->prevCourse = firstCour;

    cin.ignore(1000,'\n');
    cout<<"Enter course ID: ";
    getline(cin,firstCour->thisCourseInfo.courseID);
    cout<<"Enter course name: ";
    getline(cin,firstCour->thisCourseInfo.courseName);
    cout<<"Enter class name: ";
    getline(cin,firstCour->thisCourseInfo.className);
    cout<<"Enter teacher name: ";
    getline(cin,firstCour->thisCourseInfo.Teacher);
    do{
        cout<<"Enter number of credits: ";
        cin >> firstCour->thisCourseInfo.credit;
        if(firstCour->thisCourseInfo.credit <= 0){
             cout << "The number of credits must be greater than 0" << endl;
        }
    }while(firstCour->thisCourseInfo.credit <= 0);
    do{
        cout<<"Enter max number of students: ";
        cin >> firstCour->thisCourseInfo.maxStudent;
        if (firstCour->thisCourseInfo.maxStudent <= 0) {
           cout << "The number of students must be greater than 0" << endl;
        }
    } while(firstCour->thisCourseInfo.maxStudent <= 0);
    cout <<"Enter session for course"<<endl;
    cout << "Enter the selection of day of the week: \n\n";
    cout << "2. Monday"    << endl
         << "3. Tueday"    << endl
         << "4. Wednesday" << endl
         << "5. Thursday"  << endl
         << "6. Friday"    << endl
         << "7. Saturday"  << endl << endl;
    int day;
    bool checkInvalid = true;
    while(checkInvalid){
        cout<<"=> Enter day of the week: "; cin >> day;
        switch(day){
            case 2: firstCour->thisCourseInfo.CourseDate.day = "MON"; break;
            case 3: firstCour->thisCourseInfo.CourseDate.day = "TUE"; break;
            case 4: firstCour->thisCourseInfo.CourseDate.day = "WED"; break;
            case 5: firstCour->thisCourseInfo.CourseDate.day = "THU"; break;
            case 6: firstCour->thisCourseInfo.CourseDate.day = "FRI"; break;
            case 7: firstCour->thisCourseInfo.CourseDate.day = "SAT"; break;
            default: cout << "Day must be from 2 to 7\n";
        }
        if(day >= 2 && day <= 7) checkInvalid = false;
    }
    int session;
    checkInvalid = true;
    cout << "Enter the selection of the session: \n";
    cout << "1. S1(07:30)" << endl
         << "2. S2(09:30)" << endl
         << "3. S3(13:30)" << endl
         << "4. S4(15:30)" << endl << endl;
    while(checkInvalid){   
        cout << "=> Session for that day: "; cin >> session;
        switch(session){
            case 1: firstCour->thisCourseInfo.CourseDate.session = "S1(07:30)"; break;
            case 2: firstCour->thisCourseInfo.CourseDate.session = "S2(09:30)"; break;
            case 3: firstCour->thisCourseInfo.CourseDate.session = "S3(13:30)"; break;
            case 4: firstCour->thisCourseInfo.CourseDate.session = "S4(15:30)"; break;
            default: cout << "Session must be from 1 to 4\n";
        }
        if(session >= 1 && session <= 4) checkInvalid = false;
    }
    cout << "The system create a new course successfully!!!\n";
    system("pause");
}
void InitSemester(Semester* &Sem, int semester, string year)
{
    Semester* curSem = nullptr;
    if (Sem == nullptr) {
        Sem = new Semester;
        curSem = Sem;
    } else {
        curSem = Sem;
        while(curSem->nextSemester != nullptr)
        {
            curSem = curSem->nextSemester;
        }
        curSem->nextSemester = new Semester;
        curSem = curSem->nextSemester;
    }
    curSem->semester = semester;
    curSem->year = year;

    cout << "\nThe system created semester " << curSem->semester << " in year " <<curSem->year << endl;
    cin.ignore(1000,'\n');
    cout<<"Enter starting date for semester "<< curSem->semester <<": ";
    getline(cin, curSem->start);
    cout<<"Enter ending date for semester "<< curSem->semester <<": ";
    getline(cin,curSem->end);
}
void addStudentToCourse(Course* curCourse, Schoolyear* curYear)
{
    if(curCourse->numCurStudents >= curCourse->thisCourseInfo.maxStudent ){
        cout << "The course is having maximum student!!! You cannot add student to this course.\n";
        return;
    }
    int numYears;
    string  studentID, nameStudyClass, year;
    // DisplayYearList(curYear, numYears);
    cin.ignore(1000,'\n');
    cout << "Enter the year number when a student start in system: ";
    getline(cin, year);
    cout << "Enter the student ID you want to add: ";
    getline(cin, studentID);
    cout << "Enter the name of study class of student you want to add: ";
    getline(cin, nameStudyClass);

    CourseStudent* newStudent = findStudentInCourse(curCourse->listStudent, studentID);
        
    if(newStudent != nullptr){
        cout << "This student has enrolled to this course!\n";
        system("pause");
        return;
    }
    newStudent = new CourseStudent;
    if(!FindStudentIndex(curYear, newStudent, year ,nameStudyClass, studentID, curCourse)){
        delete newStudent;
        return;
    }


    newStudent->nextStudent = curCourse->listStudent;
    if(curCourse->listStudent){
        curCourse->listStudent-> prevStudent= newStudent;
    }
    curCourse->listStudent = newStudent;
    curCourse->numCurStudents++;

}

void removeEnrollCourse(Student* removedStudent, Course* pCourse)
{
    EnrolledCourse* tmp = removedStudent->CourseList;
    while(tmp){
        if(tmp->ptoCourse == pCourse) break;
        tmp = tmp->nextCourse;
    }
    if(!tmp->nextCourse)
        removedStudent->lastEnrolledCourse = tmp->prevCourse;
    if(tmp->prevCourse) {
       tmp->prevCourse->nextCourse = tmp->nextCourse;
    }
    else {
        removedStudent->CourseList = tmp->nextCourse;
        removedStudent->CourseList->prevCourse = nullptr;
    }
    if (tmp->nextCourse) {
        tmp->nextCourse->prevCourse = tmp->prevCourse; 
    }
    delete tmp;

}
void removeStudentFromCourse(Course* curCourse, Schoolyear* curYear)
{
    string studentName, studentID, nameStudyClass;
    cin.ignore(1000,'\n');
    // cout << "Enter the student name you want to remove: ";
    // getline(cin, studentName);
    cout << "Enter the student ID you want to remove: ";
    getline(cin, studentID);

    CourseStudent* removedStudent = findStudentInCourse(curCourse->listStudent, studentID);

    if(removedStudent == nullptr){
        cout << "The student hasn't enrolled to this course\n";
        system("pause");
        return;
    }

    removeEnrollCourse(removedStudent->ptoStudent, curCourse);
    
    if(removedStudent->prevStudent){
        removedStudent->prevStudent->nextStudent = removedStudent->nextStudent;
        removedStudent->nextStudent->prevStudent = removedStudent->prevStudent;
    }
    else {
        curCourse->listStudent = removedStudent->nextStudent;
        curCourse->listStudent->prevStudent = nullptr;
    }
    delete removedStudent;
}
void removeCourse(Semester* curSemester)
{
    string courseName, courseID, className;
    cin.ignore(1000,'\n');

    cout << "Enter the course ID you want to remove: ";
    getline(cin, courseID);
    cout << "Enter the course name you want to remove: ";
    getline(cin, courseName);
    cout << "Enter the class name of course you want to remove: ";
    getline(cin, className);

    Course* pCourse = findTheCourse(curSemester,curSemester->year, curSemester->semester, courseName, courseID, className);
    if(!pCourse) {
        cout << "This course doesn't exist!\n";
        system("pause");
    }

    if(pCourse == curSemester->CourseList){
        curSemester->CourseList = curSemester->CourseList->nextCourse;
        if(curSemester->CourseList) curSemester->CourseList->prevCourse = nullptr;
    }
    else {
        pCourse->prevCourse->nextCourse = pCourse->nextCourse;
        pCourse->nextCourse->prevCourse = pCourse->prevCourse;
    }

    while(pCourse->listStudent){
        CourseStudent* tmp = pCourse->listStudent;
        pCourse->listStudent = pCourse->listStudent->nextStudent;
        removeEnrollCourse(tmp->ptoStudent, pCourse);
        delete tmp;
    }
    string filename = "Data\\" + pCourse->thisCourseInfo.courseID + '_' + pCourse->thisCourseInfo.className + ".txt";
    remove(filename.c_str());

    delete pCourse;
    cout << "The program removed this course.\n";
    system("pause");
}

void ExportCourseStudent(Course* curCourse){
    if (curCourse->listStudent == nullptr) {
        cout << "No students found in this Course" << endl;
        system("pause");
        return;
    }
    ofstream out;
    out.open("StudentOf_" + curCourse->thisCourseInfo.courseID + '_' + curCourse->thisCourseInfo.className + ".csv");
    CourseStudent* curStudent = curCourse->listStudent;
    Scoreboard thisCourseBoard;
    Student* temp = nullptr;
    bool successflag = false;
    while (curStudent != nullptr) {
        successflag = true;
        temp = curStudent->ptoStudent;
        thisCourseBoard = curStudent->savedScore;
        out << curStudent->no << ',';
        out << temp->dInfo.StudentID << ',';
        out << temp->dInfo.FirstName + " " + temp->dInfo.LastName<< ',';
        out << thisCourseBoard.midtermMark << ',';
        out << thisCourseBoard.finalMark << ',';
        out << thisCourseBoard.otherMark << ',';
        out << thisCourseBoard.totalMark << endl;
        curStudent = curStudent->nextStudent;
    }
    out.close();
    if (successflag == true) {
        cout << "Students list exported successfully" << endl;
    } else {
        cout << "Error occurred while exporting" << endl;
    }
    system("pause");
}
bool importCourseScore(Course* &curCourse){
    if(!curCourse->listStudent) {
        cout << "No students found in this Course" << endl;
        system("pause");
        return false;
    }
    
    ifstream in;
    CourseStudent* temp = curCourse->listStudent;
    Student* StudTemp = nullptr;
    string No, ID, Name, TotalMark, FinalMark, MidtermMark, OtherMark;
    string filepath;
    cin.ignore(1000,'\n');
    cout << "Enter filepath: ";
    getline(cin,filepath);
    in.open(filepath);
    if(!in.is_open()) return false;
    while(temp != nullptr && in.eof() == false){
        StudTemp = temp->ptoStudent;
        getline(in,No,',');
        getline(in,ID,',');
        getline(in,Name,',');
        getline(in,MidtermMark,',');
        getline(in,FinalMark,',');
        getline(in,OtherMark,',');
        getline(in,TotalMark,'\n');
        if(temp->no == stoi(No) && StudTemp->dInfo.StudentID == ID && StudTemp->dInfo.LastName + " " + StudTemp->dInfo.FirstName == Name){
            temp->savedScore.midtermMark = stod(MidtermMark);
            temp->savedScore.finalMark = stod(FinalMark);
            temp->savedScore.otherMark = stod(OtherMark);
            temp->savedScore.totalMark = stod(TotalMark);
        }
        temp = temp->nextStudent;
    }
    in.close();
    return true;
}

void ChangeStudentScore(CourseStudent* listCourseStudent)
{
    if(listCourseStudent == nullptr) {
        cout << "No students found in this Course" << endl;
        system("pause");
        return;
    }
    string StudentID;
    cin.ignore();
    cout << "Enter the ID of the student: ";
    cin >> StudentID;
    CourseStudent* curStudent = findStudentInCourse(listCourseStudent,StudentID);
        int choice;
    do{
        cout << "Which of Score Updating: " << endl;
        cout << "1. Current Midterm Score: " << curStudent->savedScore.midtermMark << endl;
        cout << "2. Current Final Score: " << curStudent->savedScore.finalMark << endl;
        cout << "3. Current Other Score: " << curStudent->savedScore.otherMark << endl;
        cout << "4. Current Total Score: " << curStudent->savedScore.totalMark << endl;
        cout << "5. Exit" << endl;
        cout << "Enter the selection: "; cin >> choice;
        switch(choice){
            case 1:
                do{
                    cout << "Total Score: ";
                    cin >> curStudent->savedScore.totalMark;
                }while(curStudent->savedScore.totalMark < 0 || curStudent->savedScore.totalMark > 10);
                break;
            case 2:    
                do{
                    cout << "Other Score: ";
                    cin >> curStudent->savedScore.otherMark;
                }while(curStudent->savedScore.otherMark < 0 || curStudent->savedScore.otherMark > 10);
                break;
            case 3:
                do{
                    cout << "Midterm Score: ";
                    cin >> curStudent->savedScore.midtermMark;
                }while(curStudent->savedScore.midtermMark < 0 || curStudent->savedScore.midtermMark > 10);
                break;
            case 4:
                do{
                    cout << "Final Score: ";
                    cin >> curStudent->savedScore.finalMark;
                }while(curStudent->savedScore.finalMark < 0 || curStudent->savedScore.finalMark > 10);
                break;
        }
    }while(choice != 5);
}