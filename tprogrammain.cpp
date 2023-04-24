#include "header/datafunction.h"
#include "header/loginfunction.h"
#include "header/staffui.h"
#include "header/studentui.h"

int main()
{
    string YearFile = "Listyear";
    DataBase DB;
    LoadSchoolData(DB);
    LoadSemesterSector(DB);
    Student* toStudent;
    StudyClass* toStudyClass;
    int key;
    do {
        key = login(DB.YearList,toStudent, toStudyClass);
        if (key != 1 && key != 2)
            break;
        if (key == 1) {
            StudentUI(toStudent, toStudyClass, DB);
        }
        if (key == 2) {    
            StaffUI(DB);
        }
    } while (true);

    cout << "Closing program..." << endl;
    ClearData(DB);
}