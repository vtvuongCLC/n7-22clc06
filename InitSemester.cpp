#include "header/InitSemester.h"

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
    if(temp) temp->prevCourse = curStudent->CourseList;
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
    if (curYear == nullptr)
        return false;

    StudyClass* curClass = curYear->listClass;
    int y = 0;
    while(curClass && curClass->className != className) {
        curClass = curClass->nextClass;
        y++;
    }
    if(curClass == nullptr)
        return false;

    Student* curStudent = curClass->listStudent;
    int z = 0;
    while(curStudent->dInfo.StudentID != StudID) {
        curStudent = curStudent->nextStudent;
        z++;
    }
    if(curStudent == nullptr)
        return false;
        
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
    cin.ignore();
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

void InitSemester(Semester* &Sem,int index)
{
    Sem->index = index;
    cout<<"Enter schoolyear for this semester: ";
    cin.ignore();
    getline(cin,Sem->year);
    cout<<"Enter semester number: ";
    cin >> Sem->semester;
    cout<<"Enter starting date for semester "<< Sem->semester <<": ";
    getline(cin, Sem->start);
    cout<<"Enter ending date for semester "<< Sem->semester <<": ";
    getline(cin,Sem->end );
}

void LinkAndInit(Semester* &curSemester, Schoolyear* listYear)
{
    Semester* temp = curSemester ;
    while(temp && temp->CourseList) temp = temp->nextSemester;
    Course* curCour = nullptr;
    int i = 1, n =1;
    if(temp && temp->CourseList) i += temp->index;
    else if(temp && !temp->CourseList){ 
        i = temp->index;
        cout<<"Courses for semester "<<i<<" have not been added." << endl;
        cout<<"Initiate courses for semester "<<i<<" ?"<<endl;
        cout<<"Enter 1 to continue."<<endl;
        cout<<"Enter 0 to stop."<<endl;
        cin>>n;
        while(n)
        {
            if(!temp->CourseList)
            {
                temp->CourseList = new Course;
                curCour = temp->CourseList;
            }
            else
            {
                curCour->nextCourse = new Course;
                curCour->nextCourse->prevCourse = curCour;
                curCour = curCour->nextCourse;
            }
            EnterCourseData(curCour);
            while(!UploadListofStud(curCour, listYear))
            {
                cout<<"Cant find list of student file or course ID is incorrect."<<endl;
                cout<<"Enter 1 to re add the course with the correct infotmation."<<endl;
                cout<<"Enter 0 to upload student list later."<<endl;
                cin>>n;
                if(n == 0) break;
                EnterCourseData(curCour);
            }
            cout<<"\n--------------------------------------------\n";
            cout<<"Add new course ?"<<endl;
            cout<<"Enter 1 to continue."<<endl;
            cout<<"Enter 0 to stop."<<endl;
            cin>>n;
        }
    }
    if(n && i < 4)
    {
        if(!temp)
        {
            cout<<"Initiate first semester ?"<<endl;
            cout<<"Enter 1 to continue."<<endl;
            cout<<"Enter 0 to stop."<<endl;
            cin>>n;
            if(!n) return;
            curSemester = new Semester;
            temp = curSemester;
        }
        else
        {
            cout<<"Initiate Semester "<<i<<" ?"<<endl;
            cout<<"Enter 1 to continue."<<endl;
            cout<<"Enter 0 to stop."<<endl;
            cin>>n;
            if(!n) return;
            temp->nextSemester = new Semester;
            temp = temp->nextSemester;
        }
        InitSemester(temp,i);
        cout<<"\n--------------------------------------------\n";
        cout<<"Initiate courses for semester "<<i<<" ?"<<endl;
        cout<<"Enter 1 to continue."<<endl;
        cout<<"Enter 0 to stop."<<endl;
        cin>>n;
        while(n)
        {
            if(!temp->CourseList)
            {
                temp->CourseList = new Course;
                curCour = temp->CourseList;
            }
            else
            {
                curCour->nextCourse = new Course;
                curCour->nextCourse->prevCourse = curCour;
                curCour = curCour->nextCourse;
            }
            EnterCourseData(curCour);
            while(!UploadListofStud(curCour,listYear))
            {
                cout<<"Cant find list of student file or course ID is incorrect."<<endl;
                cout<<"Enter 1 to re add the course with the correct infotmation."<<endl;
                cout<<"Enter 0 to upload student list later."<<endl;
                cin>>n;
                if(n == 0) break;
                EnterCourseData(curCour);
            }
            cout<<"\n--------------------------------------------\n";
            cout<<"Add new course ?"<<endl;
            cout<<"Enter 1 to continue."<<endl;
            cout<<"Enter 0 to stop."<<endl;
            cin>>n;
        }
        cout<<"Semester "<<temp->semester<<" has been added."<<endl;
        i++;
    }
    if(i == 4) cout<<"All 3 semesters have been added."<<endl;
}

