#include "InitSemester.h"

Semester* FindUninitSem(Schoolyear* year){
    if(!year->SemesterList) return nullptr;
    Semester* temp = year->SemesterList;
    while(temp->nextSemester && temp->CourseList) temp = temp->nextSemester;
    return temp;
}

void FindStudentIndex(StudyClass* firstClass,CourseStudentList* &curCourse, string className, string StudID){
    StudyClass* curClass = firstClass;
    Student* curStudent = nullptr;
    int x = 0,y = 0;
    while(curClass && curClass->className != className){
        curClass = curClass->nextClass;
        x++;
    }
    if(curClass == nullptr) return;
    curStudent = curClass->listStudent;
    while(curStudent->dInfo.StudentID != StudID){
        curStudent = curStudent->nextStudent;
        y++;
    }
    if(curStudent == nullptr) return;
        curCourse->classIndex = x;
        curCourse->studentIndex = y;
}

bool UploadListofStud(Course* &curCourse,StudyClass* curClass){
    if(curCourse->listStudent)
    {
        cout<<"List of students has already been added for this course.";
        return false;
    }
    CourseStudentList* temp = nullptr;
    string className, StudID;
    ifstream in;
    int i = 1;
    in.open(curCourse->infoThisCourse.courseName+".csv");
    if(!in.is_open()){
        cout<<"Unable to find list"<<endl;
        return false;
    }
    while (i <= curCourse->maxStudent && !in.eof())
    {
        getline(in,className,',');
        getline(in,StudID);
        if(!curCourse->listStudent){
            curCourse->listStudent = new CourseStudentList;
            temp = curCourse->listStudent;
        }
        else{
            temp->nextStudent = new CourseStudentList;
            temp = temp->nextStudent;
        }
        FindStudentIndex(curClass,temp,className,StudID);
        i++;
    }
    if(i <= curCourse->maxStudent) 
        cout<<"No student left to add.";
    else 
        cout<<"Maximum number of students added.";
    in.close();
    return true;
}

void EnterCourseData(Course* &firstCour)
{
    cin.ignore();
    cout<<"Enter course ID: ";
    getline(cin,firstCour->infoThisCourse.courseID);
    cout<<"Enter course name: ";
    getline(cin,firstCour->infoThisCourse.courseName);
    cout<<"Enter class name: ";
    getline(cin,firstCour->infoThisCourse.className);
    cout<<"Enter teacher name: ";
    getline(cin,firstCour->infoThisCourse.Teacher);
    cout<<"Enter number of credits: ";
    cin>>firstCour->infoThisCourse.credit;
    cout<<"Enter max number of students: ";
    cin>>firstCour->maxStudent;
    cin.ignore();
    cout<<"Enter session for course"<<endl;
    cout<<"=> Day of the week: ";
    getline(cin,firstCour->infoThisCourse.CourseDate.day);
    cout<<"=> Session for that day: ";
    getline(cin,firstCour->infoThisCourse.CourseDate.session);
}

void InitSemester(Semester* &Sem,int i)
{
    Sem->semesterIndex = i;
    cout<<"Enter starting date for semester "<< Sem->semesterIndex <<": ";
    cin.ignore();
    getline(cin, Sem->start);
    cout<<"Enter ending date for semester "<< Sem->semesterIndex <<": ";
    getline(cin,Sem->end );
}

void LinkAndInit(Schoolyear* &Year)
{
    if(!Year){
        cout<<"Can not find year.";
        return;
    }
    int i = 1,n = 1;
    Semester* curSem = nullptr;
    Course* curCour = nullptr;
    while(n)
    {
        cout<<"School year "<<Year->year<<endl<<endl;
        if(!Year->SemesterList)
        {
            cout<<"Initiate Semester "<<i<<" ?"<<endl;
            cout<<"Enter "<<1<<" to continue."<<endl;
            cout<<"Enter "<<0<<" to stop."<<endl;
            cin>>n;
            if(!n) return;
            Year->SemesterList = new Semester;
            curSem = Year->SemesterList;
        }
        else
        {
            curSem->nextSemester = new Semester;
            curSem = curSem->nextSemester;
        }
        InitSemester(curSem,i);
        cout<<"\n--------------------------------------------\n";
        cout<<"Initiate courses for semester "<<i<<" ?"<<endl;
        cout<<"Enter "<<1<<" to continue."<<endl;
        cout<<"Enter "<<0<<" to stop."<<endl;
        cin>>n;
        while(n)
        {
            if(!curSem->CourseList)
            {
                curSem->CourseList = new Course;
                curCour = curSem->CourseList;
            }
            else
            {
                curCour->nextCourse = new Course;
                curCour->nextCourse->prevCourse = curCour;
                curCour = curCour->nextCourse;
            }
            EnterCourseData(curCour);
            while(!UploadListofStud(curCour,Year->listClass))
            {
                cout<<"Please re add the course with the correct infotmation.";
                EnterCourseData(curCour);
            }
            cout<<"\n--------------------------------------------\n";
            cout<<"Add new course ?"<<endl;
            cout<<"Enter "<<1<<" to continue."<<endl;
            cout<<"Enter "<<0<<" to stop."<<endl;
            cin>>n;
        }
        i++;
        if(i == 4)
        {
            cout<<"All 3 semesters have been added.";
            return;
        }
        cout<<"\n--------------------------------------------\n";
        cout<<"Initiate Semester "<<i<<" ?"<<endl;
        cout<<"Enter "<<1<<" to continue."<<endl;
        cout<<"Enter "<<0<<" to stop Initialization."<<endl;
        cin>>n;
        cout<<"\n--------------------------------------------\n";
    }
}