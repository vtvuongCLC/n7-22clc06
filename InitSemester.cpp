#include "InitSemester.h"

Semester* isInit(Schoolyear* year){
    
}
// chưa check xem hk trong năm đó này tạo r chưa, phần nào trong hk đó chưa tạo
bool UploadListofStud(Course* &curCour, string CoursName){
    if(curCour->StudentList)
    {
        cout<<"List of students has already been added for this course.";
        return false;
    }
    Student* temp = nullptr;
    string str;
    ifstream in;
    int i = 1;
    in.open(CoursName+".csv");
    if(!in.is_open()){
        cout<<"Unable to find list"<<endl;
        return false;
    }
    while (i <= curCour->maxStudent && !in.eof())
    {
        if(!curCour->StudentList)
        {
            curCour->StudentList = new Student;
            temp = curCour->StudentList;
        }
        else
        {
            temp->nextStudent = new Student;
            temp->nextStudent->prevStudent = temp;
            temp = temp->nextStudent;
        }
        getline(in,str,',');
        temp->className = str;
        getline(in,str,',');
        temp->dInfo.No = stoi(str);
        getline(in,str,',');
        temp->dInfo.StudentID = str;
        getline(in,str,',');
        temp->dInfo.LastName = str;
        getline(in,str);
        temp->dInfo.FirstName = str;
        i++;
    }
    if(i <= curCour->maxStudent) 
        cout<<"No student left to add.";
    else 
        cout<<"Maximum number of students added.";
    in.close();
    return true;
}

void EnterCourseData(Course* &firstCour)
{
    string str;
    int n;
    cin.ignore();
    cout<<"Enter course ID: ";
    getline(cin,str);
    firstCour->courseID = str;
    cout<<"Enter course name: ";
    getline(cin,str);
    firstCour->courseName = str;
    cout<<"Enter class name: ";
    getline(cin,str);
    firstCour->className = str;
    cout<<"Enter teacher name: ";
    getline(cin,str);
    firstCour->Teacher = str;
    cout<<"Enter number of credits: ";
    cin>>n;
    firstCour->credit = n;
    cout<<"Enter max number of students: ";
    cin>>n;
    firstCour->maxStudent = n;
    cin.ignore();
    cout<<"Enter session for course"<<endl;
    cout<<"=> Day of the week: ";
    getline(cin,str);
    firstCour->CourseDate.day = str;
    cout<<"=> Session for that day: ";
    getline(cin,str);
    firstCour->CourseDate.session = str;
}

void InitSemester(Semester* &Sem,int i)
{
    Sem->semesterIndex = i;
    string date;
    cout<<"Enter starting date for semester "<< Sem->semesterIndex <<": ";
    cin.ignore();
    getline(cin,date);
    Sem->start = date;
    cout<<"Enter ending date for semester "<< Sem->semesterIndex <<": ";
    getline(cin,date);
    Sem->end = date;
}

void LinkAndInit(Schoolyear* &Year)
{
    if(!Year) {
        cout<<"Unable to find year.";
        return;
    }
    int i = 1,n = 1;
    Semester* curSem = nullptr;
    Course* curCour = nullptr;
    while(n)
    {
        cout<<"School year "<<Year->year<<endl<<endl;
        if(!Year->firstSem)
        {
            cout<<"Initiate Semester "<<i<<" ?"<<endl;
            cout<<"Enter "<<1<<" to continue."<<endl;
            cout<<"Enter "<<0<<" to stop."<<endl;
            cin>>n;
            if(!n) return;
            Year->firstSem = new Semester;
            curSem = Year->firstSem;
        }
        else
        {
            curSem->nextSem = new Semester;
            curSem = curSem->nextSem;
        }
        InitSemester(curSem,i);
        cout<<"\n--------------------------------------------\n";
        cout<<"Initiate courses for semester "<<i<<" ?"<<endl;
        cout<<"Enter "<<1<<" to continue."<<endl;
        cout<<"Enter "<<0<<" to stop."<<endl;
        cin>>n;
        while(n)
        {
            if(!curSem->Courselist)
            {
                curSem->Courselist = new Course;
                curCour = curSem->Courselist;
            }
            else
            {
                curCour->nextCourse = new Course;
                curCour->nextCourse->prevCourse = curCour;
                curCour = curCour->nextCourse;
            }
            EnterCourseData(curCour);
            while(!UploadListofStud(curCour,curCour->courseName))
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
