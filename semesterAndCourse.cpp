#include "header/semesterAndCourse.h"


// Semester* FindUninitSem(Semester* curSem){
//     if(!year->SemesterList) return nullptr;
//     Semester* temp = year->SemesterList;
//     while(temp->nextSemester) temp = temp->nextSemester;
//     return temp;
// }

void LinkEnrolledCourse(Student *&curStudent, Course *curCourse, CourseStudent* curCourseStudent)
{
    EnrolledCourse* temp = curStudent->CourseList;
    curStudent->CourseList = new EnrolledCourse;
    curStudent->CourseList->nextCourse = temp;
    curStudent->CourseList->Score = &(curCourseStudent->savedScore);
    if(temp) temp->prevCourse = curStudent->CourseList;
    else curStudent->lastEnrolledCourse = curStudent->CourseList;
    curStudent->CourseList->ptoCourse = curCourse;
    curStudent->CourseList->Score = &curCourseStudent->savedScore;
}

bool FindStudentIndex(Schoolyear* listYear,CourseStudent* &CourseStud, string yearName,string className, string StudID,Course* curCourse)
{
    Schoolyear* curYear = listYear;
    int x = 0;
    while (listYear && listYear->year != yearName) {
        curYear = curYear->nextYear;
        x++;
    }
    if (curYear == nullptr){
        cout << "This year hasn't existed in the system\n";
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
        return false;
    }
    CourseStud->ptoStudent = curStudent;
    CourseStud->yearIndex = x;
    CourseStud->classIndex = y;
    CourseStud->studentIndex = z;
    LinkEnrolledCourse(curStudent,curCourse, CourseStud);
    return true;
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

void EnterCourseData(Course* &firstCour)
{
    system("cls");
    Course* tmp = firstCour;
    firstCour = new Course;
    firstCour->nextCourse = tmp;
    if(tmp) tmp->prevCourse = firstCour;
    cout<<"Enter course ID: ";
    getline(cin,firstCour->thisCourseInfo.courseID);
    cout<<"Enter course name: ";
    getline(cin,firstCour->thisCourseInfo.courseName);
    cout<<"Enter class name: ";
    getline(cin,firstCour->thisCourseInfo.className);
    cout<<"Enter teacher name: ";
    getline(cin,firstCour->thisCourseInfo.Teacher);
    cout<<"Enter number of credits: ";
    cin>>firstCour->thisCourseInfo.credit;
    cout<<"Enter max number of students: ";
    cin>>firstCour->thisCourseInfo.maxStudent;
    cin.ignore();
    cout<<"Enter session for course"<<endl;
    cout<<"=> Day of the week: ";
    getline(cin,firstCour->thisCourseInfo.CourseDate.day);
    cout<<"=> Session for that day: ";
    getline(cin,firstCour->thisCourseInfo.CourseDate.session);
}

void InitSemester(Semester* &Sem, int semester, string year)
{
    Semester* tmp = Sem;
    Sem = new Semester;
    Sem->nextSemester = tmp;
    Sem->semester = semester;
    Sem->year = year;
    cout << "\nThe system created semester " << Sem->semester << " in year " <<Sem->year << endl;
    cout<<"Enter starting date for semester "<< Sem->semester <<": ";
    getline(cin, Sem->start);
    cout<<"Enter ending date for semester "<< Sem->semester <<": ";
    getline(cin,Sem->end );
}

// void LinkAndInit(Semester* &curSemester, Schoolyear* listYear)
// {
//     Semester* temp = curSemester ;
//     while(temp && temp->CourseList) temp = temp->nextSemester;
//     Course* curCour = nullptr;
//     int i = 1, n =1;
//     if(temp && temp->CourseList) i += temp->index;
//     else if(temp && !temp->CourseList){ 
//         i = temp->index;
//         cout<<"Courses for semester "<<i<<" have not been added." << endl;
//         cout<<"Initiate courses for semester "<<i<<" ?"<<endl;
//         cout<<"Enter 1 to continue."<<endl;
//         cout<<"Enter 0 to stop."<<endl;
//         cin>>n;
//         while(n)
//         {
//             if(!temp->CourseList)
//             {
//                 temp->CourseList = new Course;
//                 curCour = temp->CourseList;
//             }
//             else
//             {
//                 curCour->nextCourse = new Course;
//                 curCour->nextCourse->prevCourse = curCour;
//                 curCour = curCour->nextCourse;
//             }
//             EnterCourseData(curCour);
//             while(!UploadListofStud(curCour, listYear))
//             {
//                 cout<<"Cant find list of student file or course ID is incorrect."<<endl;
//                 cout<<"Enter 1 to re add the course with the correct infotmation."<<endl;
//                 cout<<"Enter 0 to upload student list later."<<endl;
//                 cin>>n;
//                 if(n == 0) break;
//                 EnterCourseData(curCour);
//             }
//             cout<<"\n--------------------------------------------\n";
//             cout<<"Add new course ?"<<endl;
//             cout<<"Enter 1 to continue."<<endl;
//             cout<<"Enter 0 to stop."<<endl;
//             cin>>n;
//         }
//     }
//     if(n && i < 4)
//     {
//         if(!temp)
//         {
//             cout<<"Initiate first semester ?"<<endl;
//             cout<<"Enter 1 to continue."<<endl;
//             cout<<"Enter 0 to stop."<<endl;
//             cin>>n;
//             if(!n) return;
//             curSemester = new Semester;
//             temp = curSemester;
//         }
//         else
//         {
//             cout<<"Initiate Semester "<<i<<" ?"<<endl;
//             cout<<"Enter 1 to continue."<<endl;
//             cout<<"Enter 0 to stop."<<endl;
//             cin>>n;
//             if(!n) return;
//             temp->nextSemester = new Semester;
//             temp = temp->nextSemester;
//         }
//         InitSemester(temp,i);
//         cout<<"\n--------------------------------------------\n";
//         cout<<"Initiate courses for semester "<<i<<" ?"<<endl;
//         cout<<"Enter 1 to continue."<<endl;
//         cout<<"Enter 0 to stop."<<endl;
//         cin>>n;
//         while(n)
//         {
//             if(!temp->CourseList)
//             {
//                 temp->CourseList = new Course;
//                 curCour = temp->CourseList;
//             }
//             else
//             {
//                 curCour->nextCourse = new Course;
//                 curCour->nextCourse->prevCourse = curCour;
//                 curCour = curCour->nextCourse;
//             }
//             EnterCourseData(curCour);
//             while(!UploadListofStud(curCour,listYear))
//             {
//                 cout<<"Cant find list of student file or course ID is incorrect."<<endl;
//                 cout<<"Enter 1 to re add the course with the correct infotmation."<<endl;
//                 cout<<"Enter 0 to upload student list later."<<endl;
//                 cin>>n;
//                 if(n == 0) break;
//                 EnterCourseData(curCour);
//             }
//             cout<<"\n--------------------------------------------\n";
//             cout<<"Add new course ?"<<endl;
//             cout<<"Enter 1 to continue."<<endl;
//             cout<<"Enter 0 to stop."<<endl;
//             cin>>n;
//         }
//         cout<<"Semester "<<temp->semester<<" has been added."<<endl;
//         i++;
//     }
//     if(i == 4) cout<<"All 3 semesters have been added."<<endl;
// }



void viewInfoOfCourse(CourseInfo infoThisCourse){

    cout    << left << setw(15) << infoThisCourse.courseID 
            << left << setw(20) << infoThisCourse.courseName 
            << left << setw(15) << infoThisCourse.className
            << left << setw(15) << infoThisCourse.Teacher
            << left << setw(8)  << infoThisCourse.credit
            << left << setw(15) << infoThisCourse.maxStudent  
            << infoThisCourse.CourseDate.day
            << ", " << infoThisCourse.CourseDate.session << "   ";                                 
}

void viewListOfCoursesIn1Semester(Semester* curSemester){
    system("cls"); 
    Course* pCourse = curSemester->CourseList;
    if(!pCourse){
        cout << "This semester hasn't yet been added course!!! First, please add the course to this semester";
        return;
    }
    cout << "----------------------------------------------------------------------\n";
    cout << "The courses list in semester " << curSemester->semester << " year " << curSemester->year << endl << endl;
    while(pCourse){
        cout << left << setw(15) << "Course ID" 
             << left << setw(20) << "Course Name" 
             << left << setw(15) << "Class Name"
             << left << setw(15) << "Teacher"
             << left << setw(8)  << "Credit"
             << left << setw(15) << "Max Students"  
             << left << setw(15) << "Day, Session" 
             << left << setw(25) << "Number Current Students" << endl;

        viewInfoOfCourse(pCourse->thisCourseInfo);
        cout << pCourse->numCurStudents << endl;
        pCourse = pCourse->nextCourse;
    }
}

void viewAllListOfCourses(Semester* curSemester){
    while(curSemester){

        while(curSemester){
            Course* pCourse = curSemester->CourseList;
            if(!pCourse){
                cout << "This semester hasn't yet been added course!!! First, please add the course to this semester";
                return;
            }
            cout << "The courses list in semester " << curSemester->semester << " year " << curSemester->year << endl << endl;
            while(pCourse){
                cout << "------------------------------------------------------------------------------\n";
                cout << "The courses list of semester " << curSemester->semester << " year " << curSemester->year << endl;
                cout << left << setw(15) << "Course ID" 
                     << left << setw(25) << "Course Name" 
                     << left << setw(15) << "Class Name"
                     << left << setw(25) << "Teacher"
                     << left << setw(3)  << "Credit"
                     << left << setw(5)  << "Max Students"  
                     << left << setw(3)  << "Day, Session" << endl;
                viewInfoOfCourse(pCourse->thisCourseInfo);
                pCourse = pCourse->nextCourse;
            }
        }
    }
}

Course* findTheCourse(Semester* pSemester, string year, int semester, string NameCourse, string IDCourse, string NameClass){
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

void updateCourseInformation(Semester* curSemester){

    string courseName, courseID, className;
    cout << "Enter the course name you want to add student: ";
    getline(cin, courseName);

    cout << "Enter the course ID you want to add student: ";
    getline(cin, courseID);

    cout << "Enter the class name of course you want to add student: ";
    getline(cin, className);

    Course* thisCourse = findTheCourse(curSemester, curSemester->year, curSemester->semester, courseName, courseID, className);

    if(thisCourse){
        while(true){

            cout << left << setw(15) << "Course ID" 
                 << left << setw(25) << "Course Name" 
                 << left << setw(15) << "Class Name"
                 << left << setw(25) << "Teacher"
                 << left << setw(3)  << "Credit"
                 << left << setw(4)  << "Max Students"   
                 << left << setw(3)  << "Day, Session" << endl;
             
            viewInfoOfCourse(thisCourse->thisCourseInfo);
            
            cout << endl;
            cout << "The current course name is " << thisCourse->thisCourseInfo.courseName << endl;
            cout << "The current course ID is " << thisCourse->thisCourseInfo.courseID << endl;
            cout << "The current class name is " << thisCourse->thisCourseInfo.className << endl;
            cout << "The teacher name is " << thisCourse->thisCourseInfo.Teacher << endl;
            cout << "The number of credits is " << thisCourse->thisCourseInfo.credit << endl;
            cout << "The maximum number of students in the course is " << thisCourse->thisCourseInfo.maxStudent << endl;
            cout << "The day of week and the session that the course will be performed are " << thisCourse->thisCourseInfo.CourseDate.day << ", "
                                                                                             << thisCourse->thisCourseInfo.CourseDate.session << endl; 
            cout << "0.Update finish\n1.Course name\n2.Course ID\n3.Class name\n4.Credits\n5.Max Students\n6.Day and session\nEnter the choice number to edit: ";
            
            int choice; cin >> choice;
            cin.ignore();

            switch(choice){
                
                case 1: 
                    cout << "Enter the new course name: ";
                    getline(cin, thisCourse->thisCourseInfo.courseName);
                    break;

                case 2:
                    cout << "Enter the new course ID: ";
                    getline(cin, thisCourse->thisCourseInfo.courseID);
                    break;

                case 3:
                    cout << "Enter the new class name: ";
                    getline(cin, thisCourse->thisCourseInfo.className);
                    break;

                case 4:
                    cout << "Enter the new credit: ";
                    do{
                        cin >> thisCourse->thisCourseInfo.credit;
                        if(thisCourse->thisCourseInfo.credit <= 0) cout << "The number of credits must > 0\n";
                    }while(thisCourse->thisCourseInfo.credit <= 0);
                    cin.ignore();
                    break;

                case 5:
                    int numMaxStudents;
                    cout << "Enter the number of max students (must bigger than current): ";
                    do{
                        cin >> numMaxStudents;
                    } while(numMaxStudents < thisCourse->thisCourseInfo.maxStudent);

                    thisCourse->thisCourseInfo.maxStudent = numMaxStudents;
                    cin.ignore();
                    break;

                case 6:
                    cout << "< 2 or > 7. Go back"   << endl
                         << "2. Monday"    << endl
                         << "3. Tueday"    << endl
                         << "4. Wednesday" << endl
                         << "5. Thursday"  << endl
                         << "6. Friday"    << endl
                         << "7. Saturday"  << endl
                         << "Enter the selection of day of the week: ";

                         int day; cin >> day;

                         switch(day){
                            case 2: thisCourse->thisCourseInfo.CourseDate.day = "MON"; break;
                            case 3: thisCourse->thisCourseInfo.CourseDate.day = "TUE"; break;
                            case 4: thisCourse->thisCourseInfo.CourseDate.day = "WED"; break;
                            case 5: thisCourse->thisCourseInfo.CourseDate.day = "THU"; break;
                            case 6: thisCourse->thisCourseInfo.CourseDate.day = "FRI"; break;
                            case 7: thisCourse->thisCourseInfo.CourseDate.day = "SAT"; break;
                            default: break;
                         }

                    cout << "< 1 or > 4. Go back" << endl
                         << "1. S1 (07:30)" << endl
                         << "2. S2 (09:30)" << endl
                         << "3. S3 (13:30)" << endl
                         << "4. S4 (15:30)" << endl
                         << "Enter the selection of the session: ";
                         
                         int session; cin >> session;

                         switch(day){
                            case 1: thisCourse->thisCourseInfo.CourseDate.session = "S1 (07:30)"; break;
                            case 2: thisCourse->thisCourseInfo.CourseDate.session = "S2 (09:30)"; break;
                            case 3: thisCourse->thisCourseInfo.CourseDate.session = "S3 (13:30)"; break;
                            case 4: thisCourse->thisCourseInfo.CourseDate.session = "S4 (15:30)"; break;
                            default: break;
                         }
                         cin.ignore();
                    break;

                default: return;
            }
            cout << "\nThe new update course information\n";
        }
    }
    else cout << "This course doesn't exist.\n";
}

CourseStudent* findStudentInCourse(CourseStudent* listStudent, string studID){
    while(listStudent){
        if(listStudent->ptoStudent->dInfo.StudentID == studID) break;
        listStudent = listStudent->nextStudent;
    }
    return listStudent;
}

void addStudentToCourse(Semester* curSemester, Schoolyear* curYear){
    string courseName, courseID, className;
    cout << "Enter the course name you want to add student: ";
    getline(cin, courseName);
    cout << "Enter the course ID you want to add student: ";
    getline(cin, courseID);
    cout << "Enter the class name of course you want to add student: ";
    getline(cin, className);

    Course* pCourse = findTheCourse(curSemester, curSemester->year, curSemester->semester, courseName, courseID, className);
    if(!pCourse) {
        cout << "This course doesn't exist!\n";
        return;
    }

    if(pCourse->numCurStudents >= pCourse->thisCourseInfo.maxStudent ){
        cout << "The course is having maximum student!!! You cannot add student to this course.\n";
        return;
    }
    int numYears;
    string studentName, studentID, nameStudyClass, year;
    // DisplayYearList(curYear, numYears);

    cout << "Enter the year number when a student start in system: ";
    getline(cin, year);
    cout << "Enter the student name you want to add: ";
    getline(cin, studentName);
    cout << "Enter the student ID you want to add: ";
    getline(cin, studentID);
    cout << "Enter the name of study class of student you want to add: ";
    getline(cin, nameStudyClass);

    CourseStudent* newStudent = findStudentInCourse(pCourse->listStudent, studentID);
        
    if(newStudent != nullptr){
        cout << "This student has enrolled to this course!\n";
        return;
    }
    newStudent = new CourseStudent;
    if(!FindStudentIndex(curYear, newStudent, year ,nameStudyClass, studentID, pCourse)){
        delete newStudent;
        return;
    }

    cout << "Enter the no number of the student in this course: ";
    cin >> newStudent->no;
    cin.ignore();
    newStudent->nextStudent = pCourse->listStudent;
    if(pCourse->listStudent){
        pCourse->listStudent-> prevStudent= newStudent;
    }
    pCourse->listStudent = newStudent;
    pCourse->numCurStudents++;
}

void displayStudentInCourse(Course* thisCourse){
    cout << "----------------------------------------------\nThe list student in this course\n";
    CourseStudent* pStudent = thisCourse->listStudent;
    cout << left << setw(5)  << "No"
             << left << setw(10) << "StudentID"
             << left << setw(15) << "LastName"
             << left << setw(10) << "FirstName" 
             << left << setw(15) << "SocialID"
             << left << setw(15) << "Gender"
                                 << "Day"   << "/" 
                                 << "Month" << "/" 
                                 << "Year"  << endl;
    while(pStudent){
        cout << left << setw(5)  << pStudent->no
             << left << setw(10) << pStudent->ptoStudent->dInfo.StudentID
             << left << setw(15) << pStudent->ptoStudent->dInfo.LastName
             << left << setw(10) << pStudent->ptoStudent->dInfo.FirstName 
             << left << setw(15) << pStudent->ptoStudent->dInfo.SocialID
             << left << setw(15) << pStudent->ptoStudent->dInfo.Gender
             << pStudent->ptoStudent->dInfo.Birth.day << "/"
             << pStudent->ptoStudent->dInfo.Birth.month << "/"
             << pStudent->ptoStudent->dInfo.Birth.year << endl;
        pStudent = pStudent->nextStudent;
    }
}

void removeEnrollCourse(Student* removedStudent, Course* pCourse){
    EnrolledCourse* tmp = removedStudent->CourseList;
    while(tmp){
        if(tmp->ptoCourse == pCourse) break;
        tmp = tmp->nextCourse;
    }
    if(!tmp->nextCourse) removedStudent->lastEnrolledCourse = tmp->prevCourse;
    if(tmp->prevCourse){
       tmp->prevCourse->nextCourse = tmp->nextCourse;
       tmp->nextCourse->prevCourse = tmp->prevCourse; 
    }
    else {
        removedStudent->CourseList = tmp->nextCourse;
        removedStudent->CourseList->prevCourse = nullptr;
    }
    delete tmp;

}
void removeStudentFromCourse(Semester* curSemester, Schoolyear* curYear){
    string courseName, courseID, className;
    cout << "Enter the course name you want to remove a student: ";
    getline(cin, courseName);
    cout << "Enter the course ID you want to remove a student: ";
    getline(cin, courseID);
    cout << "Enter the class name of course you want to add student: ";
    getline(cin, className);

    Course* pCourse = findTheCourse(curSemester, curSemester->year, curSemester->semester, courseName, courseID, className);
    if(!pCourse) {
        cout << "This course doesn't exist!\n";
        return;
    }

    displayStudentInCourse(pCourse);

    string studentName, studentID, nameStudyClass;
    cout << "Enter the student name you want to remove: ";
    getline(cin, studentName);
    cout << "Enter the student ID you want to remove: ";
    getline(cin, studentID);

    CourseStudent* removedStudent = findStudentInCourse(pCourse->listStudent, studentID);

    if(removedStudent == nullptr){
        cout << "The student hasn't enrolled to this course\n";
        return;
    }

    removeEnrollCourse(removedStudent->ptoStudent, pCourse);
    
    if(removedStudent->prevStudent){
        removedStudent->prevStudent->nextStudent = removedStudent->nextStudent;
        removedStudent->nextStudent->prevStudent = removedStudent->prevStudent;
    }
    else {
        pCourse->listStudent = removedStudent->nextStudent;
        pCourse->listStudent->prevStudent = nullptr;
    }
    delete removedStudent;
}

void removeCourse(Semester* curSemester){
    string courseName, courseID, className;
    cout << "Enter the course name you want to remove: ";
    getline(cin, courseName);
    cout << "Enter the course ID you want to remove: ";
    getline(cin, courseID);
    cout << "Enter the class name of course you want to remove: ";
    getline(cin, className);

    Course* pCourse = findTheCourse(curSemester,curSemester->year, curSemester->semester, courseName, courseID, className);
    if(!pCourse) {
        cout << "This course doesn't exist!\n";
        return;
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
    
    delete pCourse;
    cout << "The program removed this course.\n";
}

void printListCoursesOfAStudent(Student* thisStudent, string semester, string year){
    EnrolledCourse* firstCourse = thisStudent->CourseList;
    cout << "The list of Courses you will study in this semester\n";
    while(firstCourse){
        if(firstCourse->ptoCourse->semester == semester && firstCourse->ptoCourse->year == year) break;
        firstCourse = firstCourse->nextCourse;
    }
    while(firstCourse->ptoCourse->semester == semester && firstCourse->ptoCourse->year == year){
        viewInfoOfCourse(firstCourse->ptoCourse->thisCourseInfo);
        firstCourse = firstCourse->nextCourse;
    }
}