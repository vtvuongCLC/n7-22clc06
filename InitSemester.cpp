#include "InitSemester.h"

Semester* FindUninitSem(Schoolyear* year){
    if(!year->SemesterList) return nullptr;
    Semester* temp = year->SemesterList;
    while(temp->nextSemester && temp->CourseList) temp = temp->nextSemester;
    return temp;
}

void LinkEnrolledCourse(Student *&curStudent, Course *curCourse)
{
    EnrolledCourse* temp = curStudent->CourseList;
    curStudent->CourseList = new EnrolledCourse;
    curStudent->CourseList->nextCourse = temp;
    if(temp) temp->prevCourse = curStudent->CourseList;
    curStudent->CourseList->thisCourse = curCourse;

}

bool FindStudentIndex(StudyClass* firstClass,CourseStudentList* &CourseStud, string className, string StudID,Course* curCourse){
    StudyClass* curClass = firstClass;
    Student* curStudent = nullptr;
    int x = 0,y = 0;
    while(curClass && curClass->className != className){
        curClass = curClass->nextClass;
        x++;
    }
    if(curClass == nullptr) return false;
    curStudent = curClass->listStudent;
    while(curStudent->dInfo.StudentID != StudID){
        curStudent = curStudent->nextStudent;
        y++;
    }
    if(curStudent == nullptr) return false;
    CourseStud->classIndex = x;
    CourseStud->studentIndex = y;
    LinkEnrolledCourse(curStudent,curCourse);
    return true;
}

bool UploadListofStud(Course* &curCourse,StudyClass* firstClass){
    if(curCourse->listStudent)
    {
        cout<<"List of students has already been added for this course.";
        return false;
    }
    CourseStudentList* temp = nullptr;
    string className, StudID;
    ifstream in;
    int i = 0;
    in.open(curCourse->infoThisCourse.courseID+".csv");
    if(!in.is_open()){
        cout<<"Unable to find list"<<endl;
        return false;
    }
    while (i < curCourse->infoThisCourse.maxStudent && !in.eof())
    {
        getline(in,className,',');
        getline(in,StudID);
        if(!curCourse->listStudent){
            curCourse->listStudent = new CourseStudentList;
            temp = curCourse->listStudent;
        }
        else{
            temp->nextStudent = new CourseStudentList;
            temp->nextStudent->prevStudent = temp;
            temp = temp->nextStudent;
        }
        while(!FindStudentIndex(firstClass,temp,className,StudID,curCourse)){
             getline(in,className,',');
             getline(in,StudID);
        }
        i++;
    }
    if(i <= curCourse->infoThisCourse.maxStudent) 
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
    cin>>firstCour->infoThisCourse.maxStudent;
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
            cout<<"Enter 1 to continue."<<endl;
            cout<<"Enter 0 to stop."<<endl;
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
        cout<<"Enter 1 to continue."<<endl;
        cout<<"Enter 0 to stop."<<endl;
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
                cout<<"Cant find list of student file or course ID is incorrect."<<endl<<endl;
                cout<<"Enter 1 to re add the course with the correct infotmation."<<endl;
                cout<<"Enter 0 to upload student list later";
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
        i++;
        if(i == 4)
        {
            cout<<"All 3 semesters have been added.";
            return;
        }
        cout<<"\n--------------------------------------------\n";
        cout<<"Initiate Semester "<<i<<" ?"<<endl;
        cout<<"Enter 1 to continue."<<endl;
        cout<<"Enter 0 to stop Initialization."<<endl;
        cin>>n;
        cout<<"\n--------------------------------------------\n";
    }
}

int main(){
    Schoolyear* a = new Schoolyear;
    LinkAndInit(a);//chỉ dùng hàm này để init hk và môn, chưa check trường hợp tạo hk rồi mà chưa tạo môn
}