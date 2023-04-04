#include "header/structlist.h"
#include "header/datafunction.h"
#include "header/loginfunction.h"
#include "header/displayfunction.h"

int main()
{
    int usertype;
    cout << "You are :" << endl;
    cout << "1. Student" << endl;
    cout << "2. Staff" << endl;
    cout << "Enter another number to exit" << endl;
    cout << ">> ";
    cin >> usertype;
    string YearFile = "Listyear";
    DataBase DB;
    LoadSchoolData(DB);
    int key = login(DB.YearList);
    // if (key == 1)
    // {
        
    // }
 
    if (key == 2)
    {    
        StaffGUI(DB);
    }
    SaveData(DB);
    ClearData(DB);
}