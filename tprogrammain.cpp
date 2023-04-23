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
    int key;
    do {
        key = login(DB.YearList,toStudent);
        if (key != 1 && key != 2)
            break;
        if (key == 1) {
            StudentUI(toStudent,DB);
        }
        if (key == 2) {    
            StaffUI(DB);
        }
    } while (true);

    cout << "Closing program..." << endl;
    ClearData(DB);
}