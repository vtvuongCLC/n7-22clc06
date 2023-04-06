#include "header/structlist.h"
#include "header/datafunction.h"
#include "header/loginfunction.h"
#include "header/displayfunction.h"

int main()
{
    string YearFile = "Listyear";
    DataBase DB;
    LoadSchoolData(DB);
    LoadSemesterSector(DB);
    int key = login(DB.YearList);
    // if (key == 1)
    // {
        
    // }
 
    if (key == 2)
    {    
        StaffGUI(DB);
    }
    cout << "Closing program..." << endl;
    //SaveData(DB);
    ClearData(DB);
}